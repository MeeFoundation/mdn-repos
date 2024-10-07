use std::string::FromUtf8Error;

use axum::{http::StatusCode, response::IntoResponse};
use mee_crypto::error::MeeCryptoErr;
use mee_data_sync::error::MeeDataSyncErr;
use sea_orm::TransactionError;

pub type AgentServiceResult<T = ()> = Result<T, AgentServiceErr>;

#[derive(Debug, thiserror::Error)]
pub enum AgentServiceErr {
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

    #[error("std::string FromUtf8Error error: {0}")]
    StdStringFromUtf8Error(#[from] FromUtf8Error),

    #[error("Boxed std::error::Error: {0}")]
    BoxedStdError(#[from] Box<dyn std::error::Error + Send + Sync>),

    #[error("Biscuit auth token error: {0}")]
    AuthToken(#[from] biscuit_auth::error::Token),

    // domain errors
    #[error("MDN provider secrets management error: {0}")]
    ProviderSecretsManagement(String),

    #[error("Mee crypto utils error: {0}")]
    MeeCryptoUtils(#[from] MeeCryptoErr),

    #[error("Mee data sync module error: {0}")]
    MeeDataSync(#[from] MeeDataSyncErr),
}

impl From<TransactionError<AgentServiceErr>> for AgentServiceErr {
    fn from(value: TransactionError<AgentServiceErr>) -> Self {
        match value {
            TransactionError::Connection(e) => e.into(),
            TransactionError::Transaction(e) => e,
        }
    }
}

impl IntoResponse for AgentServiceErr {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}
