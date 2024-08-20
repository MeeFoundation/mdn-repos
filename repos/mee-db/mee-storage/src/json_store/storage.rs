use super::range_iterator::*;
use super::support::JsonExt;
use super::JsonStore;
use crate::error::Result;
use crate::kv_store::KVStore;
//issue with format!
#[allow(unused)]
use crate::kv_store::PATH_SEPARATOR;
use serde_json::Value;
use std::sync::Arc;

use tracing::debug;

pub struct KVBasedJsonStoreImpl {
    db: Arc<dyn KVStore + Send + Sync>,
}

impl KVBasedJsonStoreImpl {
    #[allow(unused)]
    pub fn new(db: Arc<dyn KVStore + Send + Sync>) -> Self {
        Self { db }
    }
}

#[async_trait::async_trait]
impl JsonStore for KVBasedJsonStoreImpl {
    async fn set(&self, key: String, value: Value) -> Result<()> {
        let flatten = value.x_to_flatten_map(key);
        let mut batch = vec![];
        for (k, v) in flatten {
            let bytes = serde_json::to_vec(&v)?;
            batch.push((k, bytes));
        }

        self.db.insert_many(batch).await?;

        Ok(())
    }

    async fn get(&self, key: String) -> Result<Option<Value>> {
        debug!("Getting value for key: {key}");
        let s = self.db.range(key.clone()).await?;
        let mut ri = KVIteratorListenerImpl::new(None, None, None, None, 0);

        let r = ri.collect(s).await?;

        Ok(r.first().cloned())
    }

    async fn delete(&self, key: String) -> Result<()> {
        let db = self.db.clone();
        db.delete(&key).await?;
        Ok(())
    }

    async fn generate_id(&self) -> Result<String> {
        Ok(uuid::Uuid::now_v7().to_string())
    }
}

#[cfg(test)]
mod test {

    use super::*;
    use crate::kv_store;
    use assert_json_diff::assert_json_eq;
    use serde_json::json;

    fn setup() -> KVBasedJsonStoreImpl {
        let kv = kv_store::new_btree_map_based();
        KVBasedJsonStoreImpl::new(kv)
    }

    #[tokio::test]
    async fn read_write_single_value() {
        let storage = setup();
        storage
            .set(format!("key{PATH_SEPARATOR}id"), json!("value"))
            .await
            .unwrap();
        let value = storage.get(format!("key{PATH_SEPARATOR}id")).await.unwrap();
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
        let value = storage.get(format!("key{PATH_SEPARATOR}id")).await.unwrap();
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
        let value = storage.get(key).await.unwrap();
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
        let value = storage.get(key).await.unwrap();
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
        let value = storage.get(key).await.unwrap();
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
        let value = storage.get(key).await.unwrap();
        let expected = obj.get("field1");
        assert_json_eq!(value, expected);
    }
}
