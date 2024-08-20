// #![feature(return_position_impl_trait_in_trait)]
// #![feature(type_alias_impl_trait)]

mod error;
mod json_store;
mod kv_store;
// mod schema;

// use error::{Error, Result};
// use serde_json::Value;
// use storage::Storage;
// use storage::StorageBTreeMapImpl;

use futures::{pin_mut, stream::StreamExt};
use kv_store::KVStore;
// use tokio_stream::StreamExt;

#[tokio::main]
async fn main() {
    let store = kv_store::b_tree_map_store::BTreeMapStore::new();

    let stream = store.range("example_path".to_string()).await.unwrap();
    pin_mut!(stream);
    while let Some((key, value)) = stream.next().await {
        //     Ok(
        println!("Key: {}, Value: {:?}", key, value);
        // Err(e) => eprintln!("Error: {:?}", e),
    }
}
