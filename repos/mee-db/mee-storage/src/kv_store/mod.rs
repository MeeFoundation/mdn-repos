mod b_tree_map_store;

use crate::error::Result;
use std::sync::Arc;

pub trait KVStore {
    fn insert(&self, path: String, value: Vec<u8>) -> Result<()>;
    #[allow(unused)]
    fn get(&self, path: &str) -> Result<Option<Vec<u8>>>;
    fn range(&self, path: String, listener: &mut Box<dyn KVIteratorListener>) -> Result<()>;
    fn delete(&self, path: &str) -> Result<()>;
}

pub const PATH_SEPARATOR: char = '/';
pub const ID_PREFIX: &str = "id:";

pub enum KVIteratorControl {
    #[allow(unused)]
    SkipPrefix(String),
    Next,
    Stop,
}

pub trait KVIteratorListener {
    fn on_kv(&mut self, key: String, value: &Vec<u8>) -> Result<KVIteratorControl>;
    fn flush(&mut self) -> Result<()>;
}

pub(super) fn new_btree_map_based() -> Arc<dyn KVStore + Send + Sync> {
    let store = b_tree_map_store::BTreeMapStore::new();
    Arc::new(store)
}
