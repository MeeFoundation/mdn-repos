pub use super::json_store_record::JsonStoreRecord;

use super::error::*;
pub type RecordStream = futures::stream::BoxStream<'static, JsonStoreRecord>;

use core::fmt::Debug;

use serde_json::{Map, Value};
#[async_trait::async_trait]
pub trait JsonStore: Debug {
    async fn insert(&self, value: Value) -> Result<String>;
    async fn update(&self, id: String, properties: Map<String, Value>) -> Result<()>;
    async fn get(&self, id: String, properties: Option<Vec<String>>) -> Result<Option<Value>>;
    async fn delete(&self, id: String) -> Result<()>;
    async fn stream(&self) -> Result<RecordStream>;
}
