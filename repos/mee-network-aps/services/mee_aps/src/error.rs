use axum::{http::StatusCode, response::IntoResponse};
use mee_crypto::error::MeeCryptoErr;
use sea_orm::TransactionError;

pub type ApsServiceResult<T = ()> = Result<T, ApsServiceErr>;

#[derive(Debug, thiserror::Error)]
pub enum ApsServiceErr {
    #[error("CLI parsing error: {0}")]
    CliParsing(#[from] clap::Error),

    #[error("URL parsing error: {0}")]
    UrlParsing(#[from] url::ParseError),

    #[error("Strum parsing error: {0}")]
    StrumParsing(#[from] strum::ParseError),

    #[error(transparent)]
    OrmOperation(#[from] sea_orm::error::DbErr),

    #[error(transparent)]
    OrmRuntime(#[from] sea_orm::error::RuntimeErr),

    #[error("Anyhow error: {0}")]
    AnyhowError(#[from] anyhow::Error),

    #[error("std::io error: {0}")]
    StdIo(#[from] std::io::Error),

    #[error("Boxed std::error::Error: {0}")]
    BoxedStdError(#[from] Box<dyn std::error::Error + Send + Sync>),

    #[error("Biscuit auth token error: {0}")]
    AuthToken(#[from] biscuit_auth::error::Token),

    // domain errors
    #[error("Mee crypto utils error: {0}")]
    MeeCryptoUtils(#[from] MeeCryptoErr),
}

impl From<TransactionError<ApsServiceErr>> for ApsServiceErr {
    fn from(value: TransactionError<ApsServiceErr>) -> Self {
        match value {
            TransactionError::Connection(e) => e.into(),
            TransactionError::Transaction(e) => e,
        }
    }
}

impl IntoResponse for ApsServiceErr {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}