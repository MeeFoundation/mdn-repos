mod db;
mod storage;
mod support;

use crate::{error::Result, kv_store};
use serde_json::Value;
use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

const ID_PROPERTY: &str = "@id";

#[allow(unused)]
pub trait JsonStore {
    fn set(&self, key: String, value: Value) -> Result<()>;
    fn get(&self, key: String) -> Result<Option<Value>>;
    fn delete(&self, key: String) -> Result<()>;
    fn generate_id(&self) -> Result<String>;
}

#[allow(dead_code)]
pub trait JsonDB {
    fn insert(&self, schema: String, value: Value) -> Result<String>;
    fn find_by_id(
        &self,
        schema: String,
        id: String,
        selecting_properties: Vec<String>,
    ) -> Result<Option<Value>>;
    fn find_by_id_full(&self, schema: String, id: String) -> Result<Option<Value>>;
    fn delete(&self, schema: String, id: String) -> Result<()>;

    fn find_by_properties_eq(
        &self,
        schema: String,
        filter: Value,
        selecting_properties: Vec<String>,
    ) -> Result<Vec<Value>>;
}
#[allow(dead_code)]
pub(crate) fn new_btree_map_based() -> Arc<dyn JsonDB + Send + Sync> {
    let store = kv_store::new_btree_map_based();
    let json_store = Arc::new(KVBasedJsonStoreImpl::new(store));
    Arc::new(db::JsonDBImpl::new(json_store))
}
