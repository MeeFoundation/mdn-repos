pub mod error;
mod json_store_record;
mod storage;
mod support;

use crate::binary_kv_store;

use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

pub use error::*;
pub type Store = Arc<dyn JsonStore + Send + Sync + 'static>;
pub type JsonStream = futures::stream::BoxStream<'static, Value>;
pub type RecordStream = futures::stream::BoxStream<'static, Box<dyn Record>>;

use core::fmt::Debug;

use serde_json::{Map, Value};

#[async_trait::async_trait]
pub trait Record: Send + Sync {
    fn id(&self) -> &str;

    // /**
    //  *
    //  */
    // async fn keys(&self) -> Result<Vec<String>>;
    /*
     * 1. read from uncommited changes
     * 2. or else read from cache
     * 3. or else read from store
     */
    async fn get(&self, property_name: &str) -> Result<Option<Value>>;
    /*
     * 1. put to uncommited changes
     * 2. avoid to put to store if cache contains the same property (TODO)
     */
    async fn set(&self, property_name: String, value: Value) -> Result<()>;
    /*
     * 1. put to uncommited appendable values for collection property
     * 2. avoid to put to store if cache contains the same property (TODO)
     */
    async fn append(&self, collection_property_name: String, value: Value) -> Result<()>;
    /*
     * 1. put to uncommited changes
     * 2. avoid to put to store if cache contains the same property (TODO)
     */
    async fn delete_property(&self, property_name: String) -> Result<()>;

    /*
     * 1. put to uncommited changes
     * 2. avoid to put to store if cache contains the same property (TODO)
     */
    async fn delete(&self) -> Result<()>;

    async fn is_deleted(&self) -> Result<bool>;

    /*
     * 1. delete or commit uncommited changes to store
     * 2. clear uncommited changes and cache
     */
    async fn commit(&self) -> Result<()>;

    /*
     * 1. read from uncommited changes
     * 2. or else read from cache
     * 3. or else read from store
     */
    async fn snapshot(&self, properties: Option<Vec<String>>) -> Result<Value>;
}

#[allow(unused)]
#[async_trait::async_trait]
pub trait JsonStore: Debug {
    async fn insert(&self, value: Value) -> Result<String>;
    async fn update(&self, id: String, properties: Map<String, Value>) -> Result<()>;
    async fn get(&self, id: String, properties: Option<Vec<String>>) -> Result<Option<Value>>;
    async fn delete(&self, id: String) -> Result<()>;

    //main
    async fn stream(&self) -> Result<RecordStream>;
}

#[allow(dead_code)]
pub fn new_btree_map_based() -> Store {
    let store = binary_kv_store::new_btree_map_based();
    Arc::new(KVBasedJsonStoreImpl::new(store))
}
