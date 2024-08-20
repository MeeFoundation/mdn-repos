mod db;
mod query;
mod range_iterator;
mod storage;
mod support;

use crate::{error::Result, kv_store};
use serde_json::Value;
use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

const ID_PROPERTY: &str = "@id";
const ID_PREFIX: &str = "id:";

#[allow(unused)]
#[async_trait::async_trait]
pub trait JsonStore {
    async fn set(&self, key: String, value: Value) -> Result<()>;
    async fn get(&self, key: String) -> Result<Option<Value>>;
    async fn delete(&self, key: String) -> Result<()>;
    async fn generate_id(&self) -> Result<String>;

    // async fn select(&self, query: query::SelectQuery) -> Result<Vec<Value>>;
    // async fn execute_update(&self, query: query::UpdateQuery) -> Result<u128>;
    // async fn execute_delete(&self, query: query::DeleteQuery) -> Result<u128>;
}

#[allow(dead_code)]
#[async_trait::async_trait]
pub trait JsonDB {
    async fn insert(&self, value: Value) -> Result<String>;
    async fn find_by_id(
        &self,
        id: String,
        selecting_properties: Vec<String>,
    ) -> Result<Option<Value>>;
    async fn find_by_id_full(&self, id: String) -> Result<Option<Value>>;
    async fn delete(&self, id: String) -> Result<()>;

    // ///
    // fn select(&self, query: query::SelectQuery) -> Result<Vec<Value>>;
    // fn execute_update(&self, query: query::UpdateQuery) -> Result<u128>;
    // fn execute_delete(&self, query: query::DeleteQuery) -> Result<u128>;
}
#[allow(dead_code)]
pub(crate) fn new_btree_map_based() -> Arc<dyn JsonDB + Send + Sync> {
    let store = kv_store::new_btree_map_based();
    let json_store = Arc::new(KVBasedJsonStoreImpl::new(store));
    Arc::new(db::JsonDBImpl::new(json_store))
}
