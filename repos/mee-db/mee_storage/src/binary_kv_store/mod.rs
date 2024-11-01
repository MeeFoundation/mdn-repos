pub mod b_tree_map_store;
mod error;

use std::sync::Arc;
pub type KV = (String, Vec<u8>);
pub type KVStream = futures::stream::BoxStream<'static, KV>;
use core::fmt::Debug;
pub use error::*;

#[async_trait::async_trait]
pub trait BinaryKVStore: Debug {
    #[allow(unused)]
    async fn insert(&self, path: String, value: Vec<u8>) -> Result<()>;
    async fn insert_many(&self, batch: Vec<KV>) -> Result<()>;
    async fn range(&self, path: String) -> Result<KVStream>;
    async fn delete(&self, path: &str) -> Result<()>;
    #[allow(unused)]
    async fn get(&self, path: &str) -> Result<Option<Vec<u8>>>;
}

pub const PATH_SEPARATOR: char = '/';
pub const PATH_PREFIX: char = '@';

pub fn new_btree_map_based() -> Arc<dyn BinaryKVStore + Send + Sync + 'static> {
    let store = b_tree_map_store::BTreeMapStore::new();
    Arc::new(store)
}