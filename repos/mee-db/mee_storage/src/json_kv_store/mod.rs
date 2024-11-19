pub mod error;
mod field_filter;
mod storage;

use crate::binary_kv_store;

use serde_json::Value;
use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

use error::*;

pub type Store = Arc<dyn JsonStore + Send + Sync + 'static>;

pub type JsonStream = futures::stream::BoxStream<'static, Value>;
use core::fmt::Debug;
pub use field_filter::FieldFilter;

#[allow(unused)]
#[async_trait::async_trait]
pub trait JsonStore: Debug {
    async fn set(&self, key: String, value: Value) -> Result<()>;
    async fn get(&self, key: String, select_fields: FieldFilter) -> Result<Option<Value>>;
    async fn delete(&self, key: String) -> Result<()>;
    async fn range(&self, key: String, select_fields: FieldFilter) -> Result<JsonStream>;
}

#[allow(dead_code)]
pub fn new_btree_map_based() -> Store {
    let store = binary_kv_store::new_btree_map_based();
    Arc::new(KVBasedJsonStoreImpl::new(store))
}
