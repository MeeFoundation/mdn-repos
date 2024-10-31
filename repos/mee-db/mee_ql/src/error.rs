use core::str::Utf8Error;
use thiserror::Error;
use tree_sitter::LanguageError;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Language error: {}", 0)]
    LangError(#[from] LanguageError),
    #[error("Missing node: {}", 0)]
    MissingNode(String),
    #[error("Parse error: {}", 0)]
    ParseError(String),
    #[error("Parse error: {}", 0)]
    Utf8Error(#[from] Utf8Error),
}

pub type Result<T> = std::result::Result<T, Error>;
