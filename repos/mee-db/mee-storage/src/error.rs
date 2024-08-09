use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("JSON parsing error: {0}")]
    JsonParsing(#[from] serde_json::Error),
    #[error("Lock error: {0}")]
    LockError(String),
    #[error(transparent)]
    Other(#[from] anyhow::Error),

    #[error("KV Store Error: {0}")]
    KVStoreError(String),
}

pub type Result<T> = std::result::Result<T, Error>;
