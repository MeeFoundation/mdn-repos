use crate::kv_store::KVStore;

use super::support::JsonExt;
use super::JsonStore;
use crate::error::{Error::KVStoreError, Result};
use serde_json::{Map, Value};
use std::sync::Arc;
use tracing::{debug, error, trace};

pub struct KVBasedJsonStoreImpl {
    db: Arc<dyn KVStore + Send + Sync>,
}

impl KVBasedJsonStoreImpl {
    #[allow(unused)]
    pub fn new(db: Arc<dyn KVStore + Send + Sync>) -> Self {
        Self { db }
    }

    fn inner_set(db: Arc<dyn KVStore + Send + Sync>, key: String, value: Value) -> Result<()> {
        debug!("Inserting key: {}, value: {}", key, value);
        match value {
            Value::Object(obj) => {
                for (k, v) in obj {
                    let sub_key = format!("{}.{}", key, k);
                    trace!("Inserting sub_key: {}, value: {}", &sub_key, v);
                    Self::inner_set(db.clone(), sub_key, v)?;
                }
            }
            Value::Array(arr) => {
                if arr.is_empty() {
                    let value_bytes = serde_json::to_vec(&arr)?;
                    db.insert(key, value_bytes)?;
                } else {
                    for (i, v) in arr.into_iter().enumerate() {
                        let sub_key = format!("{}.{}", key, i);
                        trace!("Inserting sub_key: {}, value: {}", &sub_key, v);
                        Self::inner_set(db.clone(), sub_key, v)?;
                    }
                }
            }
            _ => {
                trace!("Inserting sub_key: {}, value: {}", &key, value);
                let value_bytes = serde_json::to_vec(&value)?;
                db.insert(key, value_bytes)?;
            }
        }
        Ok(())
    }
}

impl JsonStore for KVBasedJsonStoreImpl {
    fn set(&self, key: String, value: Value) -> Result<()> {
        Self::inner_set(self.db.clone(), key, value)?;
        Ok(())
    }

    fn get(&self, key: String) -> Result<Option<Value>> {
        debug!("Getting value for key: {key}");
        let range = self.db.range(key.clone())?;
        let mut obj: Value = Value::Null;
        let prefix_len = key.len() + 1;
        for (k, v) in range {
            let v: Value = serde_json::from_slice(&v)?;
            if k.len() == key.len() {
                return Ok(Some(v.clone()));
            }

            let parts = k[prefix_len..].split('.').collect::<Vec<&str>>();

            if parts.len() > 0 {
                if obj.is_null() {
                    obj = if parts[0].parse::<usize>().is_ok() {
                        Value::Array(vec![])
                    } else {
                        Value::Object(Map::new())
                    }
                }

                let mut current_obj = &mut obj;

                for i in 0..parts.len() {
                    let next_obj: Value = if i == parts.len() - 1 {
                        v.clone()
                    } else {
                        let next_is_array = parts[i + 1].parse::<usize>().is_ok();
                        if next_is_array {
                            Value::Array(vec![])
                        } else {
                            Value::Object(Map::new())
                        }
                    };

                    match parts[i].parse::<usize>() {
                        Ok(index) if current_obj.is_array() => {
                            let array = current_obj.as_array_mut().unwrap();
                            if array.len() <= index {
                                array.resize(index + 1, Value::Null);
                            }
                            array[index].merge(next_obj);
                            current_obj = &mut array[index];
                        }
                        _ if current_obj.is_object() => {
                            current_obj = current_obj
                                .as_object_mut()
                                .unwrap()
                                .entry(parts[i].to_string())
                                .or_insert(Value::Null);
                            current_obj.merge(next_obj);
                        }
                        _ => {
                            error!("Unexpected KV store state for key: {}. Collected object: {:#?}, inserting path: {}, inserting value: {}", &key, &obj, &k, &v);
                            return Err(KVStoreError(
                                "Unexpected KV store state for key: {key}. ".to_string(),
                            ));
                        }
                    }
                }
            }
        }

        if obj.is_null() {
            Ok(None)
        } else {
            Ok(Some(obj))
        }
    }

    fn delete(&self, key: String) -> Result<()> {
        let db = self.db.clone();
        db.delete(&key)?;
        Ok(())
    }

    fn generate_id(&self) -> Result<String> {
        Ok(uuid::Uuid::now_v7().to_string())
    }
}

#[cfg(test)]
mod test {

    use crate::kv_store;

    use super::*;
    use serde_json::json;
    fn setup() -> KVBasedJsonStoreImpl {
        let kv = kv_store::new_btree_map_based();
        KVBasedJsonStoreImpl::new(kv)
    }

    #[test]
    fn read_write_single_value() {
        let storage = setup();
        storage.set("key".to_string(), json!("value")).unwrap();
        let value = storage.get("key".to_string()).unwrap();
        assert_eq!(value, Some(json!("value")));
    }

    #[test]
    fn read_write_array() {
        let storage = setup();
        let array = json!([1, 2, 3]);
        storage.set("key".to_string(), array.clone()).unwrap();
        let expected = Some(array);
        let value = storage.get("key".to_string()).unwrap();
        assert_eq!(value, expected);
    }

    #[test]
    fn read_props_of_embedded_objects() {
        let storage = setup();

        let first = json!({
            "field1": {
                "embedded_field1": "embedded_value1",
                "embedded_field2": "embedded_value2",
            }
        });

        storage.set("key".to_string(), first).unwrap();

        let key = "key.field1.embedded_field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(json!("embedded_value1"));
        assert_eq!(value, expected);
    }

    #[test]
    fn read_embedded_objects() {
        let storage = setup();

        let first = json!({
            "field1": {
                "embedded_field1": "embedded_value1",
                "embedded_field2": "embedded_value2",
            }
        });

        storage.set("key".to_string(), first.clone()).unwrap();

        let key = "key.field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_eq!(value, expected);
    }

    #[test]
    fn read_embedded_arrays() {
        let storage = setup();

        let first = json!({
            "field1": ["item1", "item2"]
        });

        storage.set("key".to_string(), first.clone()).unwrap();

        let key = "key.field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_eq!(value, expected);
    }

    #[test]
    fn read_embedded_arrays_with_objects() {
        let storage = setup();

        let _embedded = json!([
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
        ]);

        let mut obj = Map::new();
        obj.insert("field1".to_string(), _embedded.clone());
        let obj = Value::Object(obj);

        storage.set("key".to_string(), obj).unwrap();

        let key = "key.field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(_embedded);
        assert_eq!(value, expected);
    }
}
