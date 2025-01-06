pub mod b_tree_map_store;

pub(crate) use crate::json_kv_store::binary_store::*;

use std::sync::Arc;

pub fn new_btree_map_based() -> KVStore {
    let store = b_tree_map_store::BTreeMapStore::new();
    Arc::new(store)
}
