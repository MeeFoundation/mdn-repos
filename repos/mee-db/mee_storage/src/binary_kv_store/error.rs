use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Write error: failed to set key '{0}': {1}")]
    WriteError(String, String),
    #[error("Read error: failed to get key '{0}': {1}")]
    ReadError(String, String),
}

pub type Result<T> = std::result::Result<T, Error>;
