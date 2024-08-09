mod b_tree_map_store;

use super::error::Result;
use std::sync::Arc;

pub trait KVStore {
    fn insert(&self, path: String, value: Vec<u8>) -> Result<()>;
    #[allow(unused)]
    fn get(&self, path: &str) -> Result<Option<Vec<u8>>>;
    fn range(&self, path: String) -> Result<Vec<(String, Vec<u8>)>>;
    fn delete(&self, path: &str) -> Result<()>;
}

pub(super) fn new_btree_map_based() -> Arc<dyn KVStore + Send + Sync> {
    let store = b_tree_map_store::BTreeMapStore::new();
    Arc::new(store)
}
