use thiserror::Error;
use tokio::sync::TryLockError;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Binary KV Store error: {0}")]
    BinaryKVStoreError(#[from] super::binary_store::Error),

    #[error("JSON parsing error: {0}")]
    JsonParsingError(#[from] serde_json::Error),

    #[error("Regex error: {0}")]
    Regex(#[from] regex::Error),

    #[error("Store error: {0}")]
    Store(String),

    //remove to provide more information
    #[error("Lock error: {0}")]
    LockError(#[from] TryLockError),
}

pub type Result<T> = std::result::Result<T, Error>;
