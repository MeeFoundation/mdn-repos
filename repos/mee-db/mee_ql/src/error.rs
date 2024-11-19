use crate::ast::Position;
use mee_storage::Error as StorageError;
use thiserror::Error;
use tree_sitter::LanguageError;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Language error: {0}")]
    LanguageError(#[from] LanguageError),

    #[error("Wrong query: {0}")]
    WrongQuery(String),

    #[error("Syntax error: {1}")]
    SyntaxError(Position, String),

    #[error("Validation error: {1}")]
    ValidationError(Position, String),

    #[error("Runtime error: {1}")]
    RuntimeError(Position, String),

    #[error("Storage error: {0}")]
    StorageError(#[from] StorageError),
}

fn make_error_msg(
    position: &Position,
    source_text: impl Into<String>,
    reason: impl Into<String>,
) -> String {
    let source_text = source_text.into();
    let reason = reason.into();
    let error_place = format!("<!{}!>", &source_text[position.0..position.1]);
    format!(
        "'{}' at position ({}, {}) (wrapped in '<!_!>') {}{}{}",
        reason,
        position.0,
        position.1,
        &source_text[..position.0],
        error_place,
        &source_text[position.1..],
    )
}

impl Error {
    pub fn syntax_error(
        position: Position,
        source_text: impl Into<String>,
        reason: impl Into<String>,
    ) -> Self {
        let msg = make_error_msg(&position, source_text, reason);
        Self::SyntaxError(position, msg)
    }

    pub fn validation_error(
        position: Position,
        source_text: impl Into<String>,
        reason: impl Into<String>,
    ) -> Self {
        let msg = make_error_msg(&position, source_text, reason);
        Self::ValidationError(position, msg)
    }

    pub fn runtime_error(
        position: Position,
        source_text: impl Into<String>,
        reason: impl Into<String>,
    ) -> Self {
        let msg = make_error_msg(&position, source_text, reason);
        Self::RuntimeError(position, msg)
    }
}
pub type Result<T> = std::result::Result<T, Error>;
