mod field_filter;
mod storage;

use crate::{binary_kv_store, error::Result};

use serde_json::Value;
use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

pub use field_filter::FieldFilter;

pub type JsonStream = futures::stream::BoxStream<'static, Value>;

#[allow(unused)]
#[async_trait::async_trait]
pub trait JsonStore {
    async fn set(&self, key: String, value: Value) -> Result<()>;
    async fn get(&self, key: String, select_fields: FieldFilter) -> Result<Option<Value>>;
    async fn delete(&self, key: String) -> Result<()>;
    async fn range(&self, key: String, select_fields: FieldFilter) -> Result<JsonStream>;
}

#[allow(dead_code)]
pub(crate) fn new_btree_map_based() -> Arc<dyn JsonStore + Send + Sync> {
    let store = binary_kv_store::new_btree_map_based();
    Arc::new(KVBasedJsonStoreImpl::new(store))
}
