use super::JsonStore;
use super::Result;
use super::{FieldFilter, JsonStream};
use crate::binary_kv_store::BinaryKVStore;
#[allow(unused_imports)]
use crate::binary_kv_store::PATH_SEPARATOR;
use crate::json_utils::{JsonExt, ID_PREFIX};
use async_stream::stream;
use futures::pin_mut;
use futures::stream::StreamExt;
use serde_json::Value;
use std::sync::Arc;
use tracing::{debug, trace};

#[derive(Debug)]
pub struct KVBasedJsonStoreImpl {
    db: Arc<dyn BinaryKVStore + Send + Sync>,
}

impl KVBasedJsonStoreImpl {
    #[allow(unused)]
    pub fn new(db: Arc<dyn BinaryKVStore + Send + Sync>) -> Self {
        Self { db }
    }
}

// #region private methods

fn split_key(key: String) -> (String, String) {
    if key.starts_with(ID_PREFIX) {
        let mut split = key.splitn(2, PATH_SEPARATOR);
        let id = split
            .next()
            .unwrap_or("")
            .replace(ID_PREFIX, "")
            .to_string();
        let key = split.next().unwrap_or("").to_string();
        (id, key)
    } else {
        (String::new(), key)
    }
}

// #endregion

#[async_trait::async_trait]
impl JsonStore for KVBasedJsonStoreImpl {
    async fn set(&self, key: String, value: Value) -> Result<()> {
        let flatten = value.x_to_flatten_map(key);
        let mut batch = vec![];
        for (k, v) in flatten {
            trace!("Set key: '{k}', value : '{v}'");
            let bytes = serde_json::to_vec(&v)?;
            batch.push((k, bytes));
        }

        self.db.insert_many(batch).await?;

        Ok(())
    }

    async fn get(&self, key: String, select_fields: FieldFilter) -> Result<Option<Value>> {
        trace!("Ask value for key: '{key}'");
        let r = self.range(key, select_fields).await?;
        pin_mut!(r);

        Ok(r.next().await)
    }

    async fn delete(&self, key: String) -> Result<()> {
        trace!("Ask to delete value for key: '{key}'");
        let db = self.db.clone();
        db.delete(&key).await?;
        Ok(())
    }

    // str: enything
    async fn range(&self, key: String, select_fields: FieldFilter) -> Result<JsonStream> {
        let kv_byte_stream = self.db.range(key.clone()).await?;
        debug!("Ask range for key: '{key}' with field filter: '{select_fields}'");

        let s = stream! {
            let mut current_value = Value::Null;
            let mut current_id = String::new();
            for await kv in kv_byte_stream {
                let (key, value) = kv;
                let (id, key) = split_key(key);
                if !select_fields.matches(&key) {
                    trace!("Skipped key: {ID_PREFIX}{id}{PATH_SEPARATOR}{key}");
                    continue;
                }

                if let Ok(v) = serde_json::from_slice(&value){

                    if current_id.is_empty() && !id.is_empty() {
                        current_id = id;
                    } else if !current_id.is_empty() && current_id != id {
                        if !current_value.is_null(){
                            if select_fields.add_id() {
                                current_value.x_set_id(&current_id);
                            }
                            yield current_value.take();
                        }
                        current_id = id;
                    }

                    trace!("Selected key: '{ID_PREFIX}{current_id}{PATH_SEPARATOR}{key}', value: '{v}'");
                    current_value.x_set_property(&key, v);
                }
            }
            if !current_value.is_null() {
                if !current_id.is_empty() && select_fields.add_id() {
                    current_value.x_set_id(&current_id);
                }
                yield current_value.take();
            }
        }
        .boxed();

        Ok(s)
    }
}

#[cfg(test)]
mod test {

    use super::*;
    use crate::binary_kv_store;
    use assert_json_diff::assert_json_eq;
    use serde_json::json;

    fn setup() -> KVBasedJsonStoreImpl {
        let kv = binary_kv_store::new_btree_map_based();
        KVBasedJsonStoreImpl::new(kv)
    }

    #[tokio::test]
    async fn read_write_single_value() {
        let storage = setup();
        storage
            .set(format!("key{PATH_SEPARATOR}id"), json!("value"))
            .await
            .unwrap();
        let value = storage
            .get(format!("key{PATH_SEPARATOR}id"), FieldFilter::All)
            .await
            .unwrap();
        assert_json_eq!(value, Some(json!("value")));
    }

    #[tokio::test]
    async fn read_write_array() {
        let storage = setup();
        let array = json!([1, 2, 3]);
        storage
            .set(format!("key{PATH_SEPARATOR}id"), array.clone())
            .await
            .unwrap();
        let expected = Some(array);
        let value = storage
            .get(format!("key{PATH_SEPARATOR}id"), FieldFilter::All)
            .await
            .unwrap();
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn read_props_of_embedded_objects() {
        let storage = setup();

        let first = json!({
            "field1": {
                "embedded_field1": "embedded_value1",
                "embedded_field2": "embedded_value2",
            }
        });

        storage
            .set(format!("key{PATH_SEPARATOR}id"), first)
            .await
            .unwrap();

        let key =
            format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1{PATH_SEPARATOR}embedded_field1");
        let value = storage.get(key, FieldFilter::All).await.unwrap();
        let expected = Some(json!("embedded_value1"));
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn read_embedded_objects() {
        let storage = setup();

        let first = json!({
            "field1": {
                "embedded_field1": "embedded_value1",
                "embedded_field2": "embedded_value2",
            }
        });

        storage
            .set(format!("key{PATH_SEPARATOR}id"), first.clone())
            .await
            .unwrap();

        let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
        let value = storage.get(key, FieldFilter::All).await.unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn read_embedded_arrays() {
        let storage = setup();

        let first = json!({
            "field1": ["item1", "item2"]
        });

        storage
            .set(format!("key{PATH_SEPARATOR}id"), first.clone())
            .await
            .unwrap();

        let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
        let value = storage.get(key, FieldFilter::All).await.unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn read_embedded_arrays_with_objects() {
        let storage = setup();

        let obj = json!({
                "field1":[
                    {"ff": []},
                    {
                        "field1": "value1",
                        "field2": "value2",
                    },
                    {
                        "field1": "value3",
                        "field2": "value4",
                        "feild3": ["value5", "value", {"field4": ["fd"]} ],
                    },
            ]
        });

        storage
            .set(format!("key{PATH_SEPARATOR}id"), obj.clone())
            .await
            .unwrap();

        let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
        let value = storage.get(key, FieldFilter::All).await.unwrap();
        let expected = obj.get("field1");
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn range_selected_fields() {
        let storage = setup();

        let obj1 = json!({
            "field1": "value11",
            "field2": "value12",
            "field3": "value13",
        });

        let obj2 = json!({
            "field1": "value21",
            "field2": "value22",
            "field3": "value23",
        });

        let obj3 = json!({
            "field1": "value31",
        });

        for (i, obj) in vec![obj1, obj2, obj3].into_iter().enumerate() {
            storage
                .set(format!("key{PATH_SEPARATOR}id:{}", i), obj)
                .await
                .unwrap();
        }

        let key = "key".to_string();
        let field_filter =
            FieldFilter::try_from_patterns(vec!["field1".to_string(), "field3".to_string()])
                .unwrap();

        let value = storage.range(key, field_filter).await.unwrap();

        let value: Vec<Value> = value.collect().await;

        let expected = Some(json!(
            [
                {
                    "field1": "value11",
                    "field3": "value13"
                },
                {
                    "field1": "value21",
                    "field3": "value23"
                },
                {
                    "field1": "value31"
                }
            ]
        ));
        assert_json_eq!(value, expected);
    }

    #[tokio::test]
    async fn range_all_fields() {
        let storage = setup();

        let obj1 = json!({
            "field1": "value11",
            "field2": "value12",
            "field3": "value13",
        });

        let obj2 = json!({
            "field1": "value21",
            "field2": "value22",
            "field3": "value23",
        });

        let obj3 = json!({
            "field1": "value31",
        });

        for (i, obj) in vec![obj1, obj2, obj3].into_iter().enumerate() {
            storage
                .set(format!("key{PATH_SEPARATOR}id:{}", i), obj)
                .await
                .unwrap();
        }

        let key = "key".to_string();
        let field_filter = FieldFilter::All;

        let value = storage.range(key, field_filter).await.unwrap();

        let value: Vec<Value> = value.collect().await;

        let expected = Some(json!(
            [
                {
                    "@id": "0",
                    "field1": "value11",
                    "field2": "value12",
                    "field3": "value13",
                },
                {
                    "@id": "1",
                    "field1": "value21",
                    "field2": "value22",
                    "field3": "value23",
                },
                {
                    "@id": "2",
                    "field1": "value31",
                }
            ]
        ));
        assert_json_eq!(value, expected);
    }
}
