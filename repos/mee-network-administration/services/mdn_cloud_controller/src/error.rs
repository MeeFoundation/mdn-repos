use axum::{http::StatusCode, response::IntoResponse};
use mdn_identity_agent::error::MdnIdentityAgentErr;
use mee_crypto::error::MeeCryptoErr;
use mee_did::error::MeeDidErr;
use sea_orm::TransactionError;

pub type MdnCloudControllerResult<T = ()> = Result<T, MdnCloudControllerErr>;

#[derive(Debug, thiserror::Error)]
pub enum MdnCloudControllerErr {
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

    #[error("Password hashing error: {0}")]
    PasswordHashing(argon2::password_hash::Error),

    // domain errors
    #[error("Missing database entity: {0}")]
    MissingDbEntity(String),

    #[error("User management error: user {0} is not found")]
    MdnUserAccountNotFound(String),

    #[error("User management error: user {0} is already exists")]
    MdnUserAccountAlreadyExists(String),

    #[error("User management error: user password is invalid")]
    MdnUserAccountInvalidPassword,

    #[error("MDN Cloud Controller authority signature is missing")]
    MissingMdnCentralAuthoritySignature,

    #[error("MDN Cloud Controller DID identifier is missing")]
    MissingMdnCentralAuthorityDid,

    #[error("Mee crypto utils error: {0}")]
    MeeCryptoUtils(#[from] MeeCryptoErr),

    #[error("Mee DID utils error: {0}")]
    MeeDidUtils(#[from] MeeDidErr),

    #[error("MDN identity agent module error: {0}")]
    MdnIdentityAgent(#[from] MdnIdentityAgentErr),

    #[error(
        "User management error: cloud user authorization token is missing"
    )]
    MissingMdnUserAuthToken,

    #[error("User account management error: {0}")]
    MdnUserAccountManagement(String),

    #[error("User node auth token error: {0}")]
    InvalidMdnCustodianStorageUserAuthToken(String),

    #[error("MDN capabilities error: {0}")]
    MdnCapabilities(String),
}

impl From<TransactionError<MdnCloudControllerErr>> for MdnCloudControllerErr {
    fn from(value: TransactionError<MdnCloudControllerErr>) -> Self {
        match value {
            TransactionError::Connection(e) => e.into(),
            TransactionError::Transaction(e) => e,
        }
    }
}

impl IntoResponse for MdnCloudControllerErr {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}
