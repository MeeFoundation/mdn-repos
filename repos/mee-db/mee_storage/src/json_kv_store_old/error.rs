use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Binary KV Store error: {0}")]
    BinaryKVStoreError(#[from] crate::binary_kv_store::Error),

    #[error("JSON parsing error: {0}")]
    JsonParsingError(#[from] serde_json::Error),

    #[error("Regex error: {0}")]
    Regex(#[from] regex::Error),

    #[error("Invalid key format: {0}")]
    InvalidKeyFormat(String),
}

pub type Result<T> = std::result::Result<T, Error>;
