pub mod binary_store;
mod error;
mod json_store;
mod json_store_record;
mod storage;
mod support;

use crate::binary_kv_store;

pub use json_store_record::JsonStoreRecord;
use std::sync::Arc;
use storage::KVBasedJsonStoreImpl;

pub use error::*;
pub use json_store::*;
pub type Store = Arc<dyn JsonStore + Send + Sync + 'static>;
pub type JsonStream = futures::stream::BoxStream<'static, Value>;
pub type RecordStream = futures::stream::BoxStream<'static, JsonStoreRecord>;

use core::fmt::Debug;

use serde_json::{Map, Value};

#[async_trait::async_trait]
pub trait Record: Send + Sync + Debug + Clone + 'static {
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

    async fn property_size(&self, property_name: &str) -> Result<Option<usize>>;
}

pub fn new_btree_map_based(binary_store: binary_store::BinaryStore) -> Store {
    Arc::new(KVBasedJsonStoreImpl::new(binary_store))
}
