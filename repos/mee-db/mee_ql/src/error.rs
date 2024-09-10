use axum::{http::StatusCode, response::IntoResponse};
pub type Result<T = (), E = Error> = std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub enum Error {
    #[error("HTTP parsing error: {0}")]
    HttpParsing(#[from] axum::http::Error),

    #[error("UTF-8 parsing error: {0}")]
    Utf8Parsing(#[from] std::string::FromUtf8Error),

    #[error("Enum parsing error: {0}")]
    EnumParsing(#[from] strum::ParseError),

    #[error("std::io error: {0}")]
    StdIo(#[from] std::io::Error),

    #[error("serde_json::Error: {0}")]
    JsonError(#[from] serde_json::Error),

    #[error("DB error: {0}")]
    DbError(#[from] sled::Error),
    // #[error("Anyhow error: {0}")]
    // AnyhowError(#[from] anyhow::Error),
}

impl IntoResponse for Error {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}
