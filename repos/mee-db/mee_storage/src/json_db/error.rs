use thiserror::Error;

use crate::{json_kv_store, query_el};

#[derive(Error, Debug)]
pub enum Error {
    #[error("Write error: failed to set key '{0}': {1}")]
    WriteError(String, String),
    #[error("Read error: failed to get key '{0}': {1}")]
    ReadError(String, String),

    #[error("Json KV Store error: {0}")]
    JsonKVStoreError(#[from] json_kv_store::Error),

    #[error("Query error: {0}")]
    QueryError(#[from] query_el::Error),

    #[error("JSON parsing error: {0}")]
    JsonParsing(#[from] serde_json::Error),
}

pub type Result<T> = std::result::Result<T, Error>;
