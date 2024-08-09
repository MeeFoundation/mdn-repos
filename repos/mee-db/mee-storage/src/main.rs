mod error;
mod json_store;
mod kv_store;
mod schema;

// use error::{Error, Result};
// use serde_json::Value;
// use storage::Storage;
// use storage::StorageBTreeMapImpl;

fn main() {
    // let storage = storage::StorageBTreeMapImpl::new();
    // storage
    //     .set("key".to_string(), serde_json::json!("value"))
    //     .unwrap();
    // let value = storage.get("key".to_string()).unwrap();

    for i in 0..10 {
        println!("{}", i);
    }
}
