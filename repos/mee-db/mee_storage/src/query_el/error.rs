use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Query error: {0}")]
    QueryError(String),

    #[error("JSON parsing error: {0}")]
    JsonParsing(#[from] serde_json::Error),

    #[error("Regex error: {0}")]
    Regex(#[from] regex::Error),
}

pub type Result<T> = std::result::Result<T, Error>;
