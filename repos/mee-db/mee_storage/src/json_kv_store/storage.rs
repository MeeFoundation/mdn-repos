use super::json_store_record::JsonStoreRecord;
use super::JsonStore;
use super::Record;
use super::RecordStream;
use super::Result;
use crate::binary_kv_store::BinaryKVStore;
#[allow(unused_imports)]
use crate::binary_kv_store::PATH_SEPARATOR;
use crate::json_kv_store::support::{generate_id, get_id, object_key, property_key};
use crate::json_utils::JsonExt;
use async_stream::stream;
use futures::stream::StreamExt;
use serde_json::Map;
use serde_json::Value;
use std::sync::Arc;

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

#[async_trait::async_trait]
impl JsonStore for KVBasedJsonStoreImpl {
    async fn insert(&self, value: Value) -> Result<String> {
        let id = generate_id();
        let prefix = object_key(&id);
        for (k, v) in value.x_to_flatten_map(prefix).into_iter() {
            let bytes = serde_json::to_vec(&v)?;
            self.db.insert(k, bytes).await?;
        }
        Ok(id)
    }

    async fn update(&self, id: String, properties: Map<String, Value>) -> Result<()> {
        let record = JsonStoreRecord::new(self.db.clone(), id);
        for (k, v) in properties.into_iter() {
            record.set(k, v).await?;
        }
        record.commit().await
    }

    async fn get(&self, id: String, properties: Option<Vec<String>>) -> Result<Option<Value>> {
        let record = JsonStoreRecord::new(self.db.clone(), id);
        let r = record.snapshot(properties).await?;
        Ok(Some(r))
    }

    async fn delete(&self, id: String) -> Result<()> {
        let record = JsonStoreRecord::new(self.db.clone(), id);
        record.delete().await?;
        record.commit().await
    }

    async fn stream(&self) -> Result<RecordStream> {
        let db = self.db.clone();

        let s = stream! {
            let mut prev_id = "-".to_string();

            while let Ok(Some(k)) = db.next_key(prev_id.clone()).await {
                let id = get_id(&k).unwrap();
                prev_id = property_key(&id, &char::MAX.to_string());
                let record = JsonStoreRecord::new(db.clone(), id);
                yield record;
            }
        }
        .boxed();

        Ok(s)
    }
}

#[cfg(test)]
mod test {

    // use super::*;
    // use crate::binary_kv_store;

    // use serde_json::json;

    // async fn setup() -> (String, KVBasedJsonStoreImpl) {
    //     let kv = binary_kv_store::new_btree_map_based();
    //     let store = KVBasedJsonStoreImpl::new(kv);
    //     let id = store.insert(json!({})).await.unwrap();
    //     (id, store)
    // }

    // #[tokio::test]
    // async fn read_write_single_value() {
    //     let (id, storage) = setup().await;
    //     storage
    //         .update(id, json!(Object::from([("field1", "value")])))
    //         .await
    //         .unwrap();
    //     let value = storage.get("field1", None).await.unwrap();
    //     assert_json_eq!(value, Some(json!("value")));
    // }

    // #[tokio::test]
    // async fn read_write_array() {
    //     let storage = setup();
    //     let array = json!([1, 2, 3]);
    //     storage
    //         .set(format!("key{PATH_SEPARATOR}id"), array.clone())
    //         .await
    //         .unwrap();
    //     let expected = Some(array);
    //     let value = storage
    //         .get(format!("key{PATH_SEPARATOR}id"), FieldFilter::All)
    //         .await
    //         .unwrap();
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn read_props_of_embedded_objects() {
    //     let storage = setup();

    //     let first = json!({
    //         "field1": {
    //             "embedded_field1": "embedded_value1",
    //             "embedded_field2": "embedded_value2",
    //         }
    //     });

    //     storage
    //         .set(format!("key{PATH_SEPARATOR}id"), first)
    //         .await
    //         .unwrap();

    //     let key =
    //         format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1{PATH_SEPARATOR}embedded_field1");
    //     let value = storage.get(key, FieldFilter::All).await.unwrap();
    //     let expected = Some(json!("embedded_value1"));
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn read_embedded_objects() {
    //     let storage = setup();

    //     let first = json!({
    //         "field1": {
    //             "embedded_field1": "embedded_value1",
    //             "embedded_field2": "embedded_value2",
    //         }
    //     });

    //     storage
    //         .set(format!("key{PATH_SEPARATOR}id"), first.clone())
    //         .await
    //         .unwrap();

    //     let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
    //     let value = storage.get(key, FieldFilter::All).await.unwrap();
    //     let expected = Some(first.get("field1").unwrap().clone());
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn read_embedded_arrays() {
    //     let storage = setup();

    //     let first = json!({
    //         "field1": ["item1", "item2"]
    //     });

    //     storage
    //         .set(format!("key{PATH_SEPARATOR}id"), first.clone())
    //         .await
    //         .unwrap();

    //     let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
    //     let value = storage.get(key, FieldFilter::All).await.unwrap();
    //     let expected = Some(first.get("field1").unwrap().clone());
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn read_embedded_arrays_with_objects() {
    //     let storage = setup();

    //     let obj = json!({
    //             "field1":[
    //                 {"ff": []},
    //                 {
    //                     "field1": "value1",
    //                     "field2": "value2",
    //                 },
    //                 {
    //                     "field1": "value3",
    //                     "field2": "value4",
    //                     "feild3": ["value5", "value", {"field4": ["fd"]} ],
    //                 },
    //         ]
    //     });

    //     storage
    //         .set(format!("key{PATH_SEPARATOR}id"), obj.clone())
    //         .await
    //         .unwrap();

    //     let key = format!("key{PATH_SEPARATOR}id{PATH_SEPARATOR}field1");
    //     let value = storage.get(key, FieldFilter::All).await.unwrap();
    //     let expected = obj.get("field1");
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn range_selected_fields() {
    //     let storage = setup();

    //     let obj1 = json!({
    //         "field1": "value11",
    //         "field2": "value12",
    //         "field3": "value13",
    //     });

    //     let obj2 = json!({
    //         "field1": "value21",
    //         "field2": "value22",
    //         "field3": "value23",
    //     });

    //     let obj3 = json!({
    //         "field1": "value31",
    //     });

    //     for (i, obj) in vec![obj1, obj2, obj3].into_iter().enumerate() {
    //         storage
    //             .set(format!("key{PATH_SEPARATOR}id:{}", i), obj)
    //             .await
    //             .unwrap();
    //     }

    //     let key = "key".to_string();
    //     let field_filter =
    //         FieldFilter::try_from_patterns(vec!["field1".to_string(), "field3".to_string()])
    //             .unwrap();

    //     let value = storage.range(key, field_filter).await.unwrap();

    //     let value: Vec<Value> = value.collect().await;

    //     let expected = Some(json!(
    //         [
    //             {
    //                 "field1": "value11",
    //                 "field3": "value13"
    //             },
    //             {
    //                 "field1": "value21",
    //                 "field3": "value23"
    //             },
    //             {
    //                 "field1": "value31"
    //             }
    //         ]
    //     ));
    //     assert_json_eq!(value, expected);
    // }

    // #[tokio::test]
    // async fn range_all_fields() {
    //     let storage = setup();

    //     let obj1 = json!({
    //         "field1": "value11",
    //         "field2": "value12",
    //         "field3": "value13",
    //     });

    //     let obj2 = json!({
    //         "field1": "value21",
    //         "field2": "value22",
    //         "field3": "value23",
    //     });

    //     let obj3 = json!({
    //         "field1": "value31",
    //     });

    //     for (i, obj) in vec![obj1, obj2, obj3].into_iter().enumerate() {
    //         storage
    //             .set(format!("key{PATH_SEPARATOR}id:{}", i), obj)
    //             .await
    //             .unwrap();
    //     }

    //     let key = "key".to_string();
    //     let field_filter = FieldFilter::All;

    //     let value = storage.range(key, field_filter).await.unwrap();

    //     let value: Vec<Value> = value.collect().await;

    //     let expected = Some(json!(
    //         [
    //             {
    //                 "@id": "0",
    //                 "field1": "value11",
    //                 "field2": "value12",
    //                 "field3": "value13",
    //             },
    //             {
    //                 "@id": "1",
    //                 "field1": "value21",
    //                 "field2": "value22",
    //                 "field3": "value23",
    //             },
    //             {
    //                 "@id": "2",
    //                 "field1": "value31",
    //             }
    //         ]
    //     ));
    //     assert_json_eq!(value, expected);
    // }
}
