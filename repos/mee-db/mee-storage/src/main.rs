// #![feature(return_position_impl_trait_in_trait)]
// #![feature(type_alias_impl_trait)]

mod binary_kv_store;
mod error;
mod json_db;
mod json_kv_store;
mod json_utils;
mod query_el;
// mod schema;

// use error::{Error, Result};
// use serde_json::Value;
// use storage::Storage;
// use storage::StorageBTreeMapImpl;

use binary_kv_store::BinaryKVStore;
use futures::{pin_mut, stream::StreamExt};
// use tokio_stream::StreamExt;

#[tokio::main]
async fn main() {
    let store = binary_kv_store::b_tree_map_store::BTreeMapStore::new();

    let stream = store.range("example_path".to_string()).await.unwrap();
    pin_mut!(stream);
    while let Some((key, value)) = stream.next().await {
        //     Ok(
        println!("Key: {key}, Value: {value:?}");
        // Err(e) => eprintln!("Error: {:?}", e),
    }
}
