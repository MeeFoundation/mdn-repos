use axum::{http::StatusCode, response::IntoResponse};
use mee_ql::error::Error as MeeQlError;
pub type Result<T = (), E = Error> = std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub enum Error {
    #[error("HTTP parsing error: {0}")]
    HttpParsing(#[from] axum::http::Error),

    #[error("std::io error: {0}")]
    StdIo(#[from] std::io::Error),

    #[error("{0}")]
    MeeQlError(#[from] MeeQlError),
}

impl IntoResponse for Error {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        match self {
            Error::MeeQlError(
                e @ MeeQlError::SyntaxError(_, _)
                | e @ MeeQlError::RuntimeError(_, _)
                | e @ MeeQlError::ValidationError(_, _),
            ) => (StatusCode::BAD_REQUEST, e.to_string()).into_response(),
            Error::HttpParsing(e) => (StatusCode::BAD_REQUEST, e.to_string()).into_response(),
            _ => (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response(),
        }
    }
}
