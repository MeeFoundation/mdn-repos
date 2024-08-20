use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("JSON parsing error: {0}")]
    JsonParsing(#[from] serde_json::Error),
    #[error("Send error: {0}")]
    SyncError(#[from] tokio::sync::mpsc::error::SendError<()>),

    #[error(transparent)]
    Other(#[from] anyhow::Error),
}

pub type Result<T> = std::result::Result<T, Error>;
