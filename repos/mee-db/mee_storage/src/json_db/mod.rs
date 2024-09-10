mod db;
mod error;

pub use error::*;

use crate::json_kv_store;
use crate::json_kv_store::JsonStream;
use crate::query_el::SelectQuery;
use serde_json::Value;
use std::sync::Arc;

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
    async fn stream(&self, path: &str, query: SelectQuery) -> Result<JsonStream>;
    // fn select(&self, query: query::SelectQuery) -> Result<Vec<Value>>;
    // fn execute_update(&self, query: query::UpdateQuery) -> Result<u128>;
    // fn execute_delete(&self, query: query::DeleteQuery) -> Result<u128>;
}

pub type DB = Arc<dyn JsonDB + Send + Sync>;

#[allow(dead_code)]
pub fn new_btree_map_based() -> Arc<dyn JsonDB + Send + Sync> {
    let json_store = json_kv_store::new_btree_map_based();
    Arc::new(db::JsonDBImpl::new(json_store))
}
