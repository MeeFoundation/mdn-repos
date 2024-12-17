use super::support::{object_key, property_key, remove_object_id_prefix};
use super::*;
use crate::binary_kv_store::KVStore;
use crate::binary_kv_store::PATH_SEPARATOR;
use crate::json_utils::*;
use futures::stream::StreamExt;
use serde_json::Value;
use std::collections::BTreeMap;
use std::ops::Bound::{Excluded, Included};
use tokio::sync::Mutex;
use tracing::{error, trace};

//TODO: use optional external cache
pub struct JsonStoreRecord {
    store: KVStore,

    id: String,

    object: Mutex<Value>,
    fetched_paths: Mutex<Vec<String>>,
    uncommited_paths: Mutex<Vec<String>>,
    appended_values: Mutex<BTreeMap<String, Vec<Value>>>,
    is_deleted: Mutex<bool>,
}

impl JsonStoreRecord {
    pub fn new(store: KVStore, id: String) -> Self {
        let mut value = Value::Object(Map::new());
        value.x_set_id(&id);
        Self {
            store,
            id,
            object: Mutex::new(value),
            fetched_paths: Mutex::new(vec![]),
            uncommited_paths: Mutex::new(vec![]),
            appended_values: Mutex::new(BTreeMap::new()),
            is_deleted: Mutex::new(false),
        }
    }

    fn title(&self) -> String {
        format!("User(id={})", self.id)
    }

    async fn get_from_appended_values(&self, property_name: &str) -> Result<Value> {
        let appended_values = self.appended_values.lock().await;

        let mut value = Value::Null;

        let excluded = Excluded(format!("{property_name}{}", char::MAX));
        let range = appended_values.range((Included(property_name.to_string()), excluded));
        for (k, v) in range {
            let k = match k[property_name.len()..].to_string() {
                k if k.starts_with(PATH_SEPARATOR) => k[1..].to_string(),
                k => k,
            };
            value.x_set_property(&k, Value::Array(v.clone()));
        }
        Ok(value)
    }

    async fn fetch(&self, property_name: &str) -> Result<Option<Value>> {
        let mut property = Value::Null;
        let mut kv_byte_stream = self
            .store
            .range(property_key(&self.id, &property_name))
            .await?;

        let mut is_empty = true;
        while let Some((key, value)) = kv_byte_stream.next().await {
            is_empty = false;
            let key = remove_object_id_prefix(key);
            if let Ok(v) = serde_json::from_slice(&value) {
                property.x_set_property(&key, v);
            } else {
                error!(
                    "{}: Failed to parse value: {key} => {:?}",
                    self.title(),
                    &value
                );
                return Err(Error::Store(format!(
                    "{}: Failed to parse value: {key} => {:?}",
                    self.title(),
                    &value
                )));
            }
        }

        if is_empty {
            trace!(
                "{}: Property not found in store: {}",
                self.title(),
                property_name
            );
            return Ok(None);
        } else {
            trace!(
                "{}: Fetch from store property: {} => {:?}",
                self.title(),
                property_name,
                &property
            );
            Ok(Some(property))
        }
    }

    async fn save(&self, property_name: String, value: Value) -> Result<()> {
        trace!(
            "{}: Save property: {} => {:?}",
            self.title(),
            property_name,
            &value
        );
        let flatten = value.x_to_flatten_map(property_name);
        let mut batch = vec![];
        for (k, v) in flatten {
            let bytes = serde_json::to_vec(&v)?;
            batch.push((k, bytes));
        }
        self.store.insert_many(batch).await?;

        Ok(())
    }
}

fn push_property_to_cache(property_name: &str, marked_properties: &mut Vec<String>) {
    if marked_properties
        .iter()
        .any(|path| path.starts_with(property_name))
    {
        return;
    }
    for i in 1..=marked_properties.len() {
        if marked_properties[marked_properties.len() - i].starts_with(property_name) {
            marked_properties.remove(marked_properties.len() - i);
        }
    }
    marked_properties.push(property_name.to_string());
}

#[async_trait::async_trait]
impl Record for JsonStoreRecord {
    fn id(&self) -> &str {
        &self.id
    }

    async fn get(&self, property_name: &str) -> Result<Option<Value>> {
        let mut object = self.object.lock().await;
        let uncommited_paths = self.uncommited_paths.lock().await;
        let mut fetched_paths = self.fetched_paths.lock().await;

        if (*uncommited_paths).iter().any(|path| {
            path.starts_with(property_name)
                || (*fetched_paths)
                    .iter()
                    .any(|path| path.starts_with(property_name))
        }) {
            let property = (*object).x_get_property(property_name).cloned();
            if let Some(mut property) = property {
                property.x_merge(self.get_from_appended_values(property_name).await?);
                trace!(
                    "{}: Get from cache property: {property_name} => {:?}",
                    self.title(),
                    &property
                );
                return Ok(Some(property));
            }
            return Ok(None);
        }

        if let Some(property) = self.fetch(property_name).await? {
            (*object).x_set_property(property_name, property);
        };
        push_property_to_cache(property_name, &mut fetched_paths);

        Ok(object.x_get_property(property_name).cloned())
    }

    async fn set(&self, property_name: String, value: Value) -> Result<()> {
        let mut object = self.object.lock().await;
        let mut uncommited_paths = self.uncommited_paths.lock().await;

        trace!(
            "{}: Set uncommited property: {} => {:?}",
            self.title(),
            property_name,
            &value
        );
        (*object).x_set_property(&property_name, value);

        uncommited_paths.push(property_name);

        Ok(())
    }

    async fn append(&self, collection_property_name: String, value: Value) -> Result<()> {
        trace!(
            "{}: Mark value for addind to collection property: {} => + {:?}",
            self.title(),
            &collection_property_name,
            &value
        );
        self.appended_values
            .lock()
            .await
            .entry(collection_property_name)
            .or_insert(vec![])
            .push(value);

        Ok(())
    }

    async fn delete_property(&self, property_name: String) -> Result<()> {
        let mut object = self.object.lock().await;
        let mut uncommited_paths = self.uncommited_paths.lock().await;

        (*object).x_delete_property(&property_name);
        trace!(
            "{}: Mark uncommited property for deletion: {}",
            self.title(),
            &property_name
        );
        uncommited_paths.push(property_name);

        Ok(())
    }

    async fn delete(&self) -> Result<()> {
        let _ = self.object.lock().await;
        let mut is_deleted = self.is_deleted.lock().await;
        *is_deleted = true;
        trace!("{}: Mark record for deletion", self.title());
        Ok(())
    }

    async fn is_deleted(&self) -> Result<bool> {
        Ok(*self.is_deleted.lock().await)
    }

    async fn commit(&self) -> Result<()> {
        let mut object = self.object.lock().await;
        let mut fetched_paths = self.fetched_paths.lock().await;
        let mut uncommited_paths = self.uncommited_paths.lock().await;
        let is_deleted = self.is_deleted.lock().await;
        let mut append_values = self.appended_values.lock().await;

        if *is_deleted {
            self.store.delete(&object_key(&self.id)).await?;
            trace!("{}: Deleted from store", self.title());
        } else {
            for property_name in uncommited_paths.iter_mut() {
                if let Some(value) = object.x_get_property(property_name).cloned() {
                    self.save(property_key(&self.id, property_name), value)
                        .await?;
                } else {
                    self.store
                        .delete(&property_key(&self.id, property_name))
                        .await?;
                    trace!(
                        "{}: Delete property: {} from store",
                        self.title(),
                        property_name
                    );
                }
            }
            for (property_name, values) in append_values.iter_mut() {
                let count = self
                    .store
                    .max_index(property_key(&self.id, property_name))
                    .await?;
                for (i, v) in values.into_iter().enumerate() {
                    let new_key = format!(
                        "{}{}{}",
                        property_key(&self.id, property_name),
                        PATH_SEPARATOR,
                        count + i + 1
                    );
                    self.save(new_key, v.clone()).await?;
                }
                trace!(
                    "{}: Append values to collection property: {} => {:?}",
                    self.title(),
                    property_name,
                    &values
                );
            }
        }

        *object = Value::Object(Map::new());
        (*object).x_set_id(&self.id);
        uncommited_paths.clear();
        append_values.clear();
        fetched_paths.clear();
        trace!("{}: Committed, cache cleared", self.title());

        Ok(())
    }

    async fn snapshot(&self, property_names: Option<Vec<String>>) -> Result<Value> {
        let mut object = self.object.lock().await;
        let mut fetched_paths = self.fetched_paths.lock().await;
        let appended_values = self.appended_values.lock().await;

        if let Some(property_names) = property_names {
            let mut new_fetched_paths = vec![];
            for property_name in property_names
                .iter()
                .filter(|p| !fetched_paths.iter().any(|path| p.starts_with(path)))
            {
                if let Some(property) = self.fetch(property_name).await? {
                    (*object).x_set_property(property_name, property);
                };
                new_fetched_paths.push(property_name.to_string());
            }
            for path in new_fetched_paths {
                push_property_to_cache(&path, &mut fetched_paths);
            }

            let mut result = Value::Null;
            for property_name in property_names.iter() {
                result.x_set_property(
                    property_name,
                    object
                        .x_get_property(property_name)
                        .cloned()
                        .unwrap_or(Value::Null),
                );
            }

            for (k, v) in appended_values
                .iter()
                .filter(|(k, _)| property_names.iter().any(|p| k.starts_with(p)))
            {
                let mut arr = result
                    .x_get_property(k)
                    .cloned()
                    .unwrap_or(Value::Array(vec![]));
                arr.x_merge(Value::Array(v.clone()));
                result.x_set_property(k, arr);
            }
            Ok(result)
        } else {
            let db_value = self.store.get(&object_key(&self.id)).await?;
            if let Some(db_value) = db_value {
                trace!("{}: Fetch from store", self.title());
                let mut db_value: Value = serde_json::from_slice(&db_value)?;
                db_value.x_merge(object.take());
                let mut result = db_value;

                for (k, v) in appended_values.iter() {
                    let mut arr = result
                        .x_get_property(k)
                        .cloned()
                        .unwrap_or(Value::Array(vec![]));
                    arr.x_merge(Value::Array(v.clone()));
                    result.x_set_property(k, arr);
                }

                fetched_paths.clear();
                fetched_paths.push("".to_string());

                Ok(result)
            } else {
                Err(Error::Store(format!(
                    "{}: Record not found in store",
                    self.title()
                )))?
            }
        }
    }
}
