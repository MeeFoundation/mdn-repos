use crate::kv_store::{KVIteratorListener, KVStore};

use super::range_iterator::*;
use super::JsonStore;
use crate::error::Result;
use crate::kv_store::PATH_SEPARATOR;
use serde_json::Value;
use std::collections::BTreeMap;
use std::sync::{Arc, Mutex};

use tracing::{debug, trace};

pub struct KVBasedJsonStoreImpl {
    db: Arc<dyn KVStore + Send + Sync>,
}

impl KVBasedJsonStoreImpl {
    #[allow(unused)]
    pub fn new(db: Arc<dyn KVStore + Send + Sync>) -> Self {
        Self { db }
    }

    fn inner_set(db: Arc<dyn KVStore + Send + Sync>, key: String, value: &Value) -> Result<()> {
        debug!("Inserting key: {}, value: {}", key, value);
        match value {
            Value::Object(obj) => {
                for (k, v) in obj {
                    let sub_key = format!("{key}{PATH_SEPARATOR}{k}");
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
                        let sub_key = format!("{key}{PATH_SEPARATOR}{i}");
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
    fn set(&self, key: String, value: &Value) -> Result<()> {
        Self::inner_set(self.db.clone(), key, &value)?;
        Ok(())
    }

    fn get(&self, key: String) -> Result<Option<Value>> {
        debug!("Getting value for key: {key}");
        let map = BTreeMap::new();
        let result = Arc::new(Mutex::new(map));
        let listener: KVIteratorListenerImpl =
            KVIteratorListenerImpl::new(None, None, None, None, 0, result.clone());
        let mut listener: Box<dyn KVIteratorListener> = Box::new(listener);
        self.db.range(key.clone(), &mut listener)?;
        let x = result.lock().unwrap().iter().next().map(|(_, v)| v.clone());
        Ok(x)
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
    use assert_json_diff::assert_json_eq;
    use serde_json::json;
    fn setup() -> KVBasedJsonStoreImpl {
        let kv = kv_store::new_btree_map_based();
        KVBasedJsonStoreImpl::new(kv)
    }

    #[test]
    fn read_write_single_value() {
        let storage = setup();
        storage.set("key/id".to_string(), &json!("value")).unwrap();
        let value = storage.get("key/id".to_string()).unwrap();
        assert_json_eq!(value, Some(json!("value")));
    }

    #[test]
    fn read_write_array() {
        let storage = setup();
        let array = json!([1, 2, 3]);
        storage.set("key/id".to_string(), &array).unwrap();
        let expected = Some(array);
        let value = storage.get("key/id".to_string()).unwrap();
        assert_json_eq!(value, expected);
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

        storage.set("key/id".to_string(), &first).unwrap();

        let key = "key/id/field1/embedded_field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(json!("embedded_value1"));
        assert_json_eq!(value, expected);
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

        storage.set("key/id".to_string(), &first).unwrap();

        let key = "key/id/field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_json_eq!(value, expected);
    }

    #[test]
    fn read_embedded_arrays() {
        let storage = setup();

        let first = json!({
            "field1": ["item1", "item2"]
        });

        storage.set("key/id".to_string(), &first).unwrap();

        let key = "key/id/field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = Some(first.get("field1").unwrap().clone());
        assert_json_eq!(value, expected);
    }

    #[test]
    fn read_embedded_arrays_with_objects() {
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

        storage.set("key/id".to_string(), &obj).unwrap();

        let key = "key/id/field1".to_string();
        let value = storage.get(key).unwrap();
        let expected = obj.get("field1");
        assert_json_eq!(value, expected);
    }
}
