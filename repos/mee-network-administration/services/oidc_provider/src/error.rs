use axum::{http::StatusCode, response::IntoResponse};
use mee_crypto::error::MeeCryptoErr;
use oxide_auth::primitives::scope::ParseScopeErr;
use oxide_auth_axum::WebError;
use sea_orm::TransactionError;

pub type MeeOidcProviderResult<T = ()> = Result<T, MeeOidcProviderErr>;

#[derive(Debug, thiserror::Error)]
pub enum MeeOidcProviderErr {
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

    #[error("Mee crypto utils error: {0}")]
    MeeCryptoUtils(#[from] MeeCryptoErr),

    #[error("OAuth2 scope parsing error: {0}")]
    OAuth2ScopeParsing(#[from] ParseScopeErr),

    #[error("OAuth2 library error: {0}")]
    OAuth2WebError(#[from] WebError),

    #[error("HTML template rendering error: {0}")]
    HtmlTemplateRendering(#[from] askama::Error),

    #[error("HTTP parsing error: {0}")]
    HttpParsing(#[from] axum::http::Error),

    #[error("UTF-8 parsing error: {0}")]
    Utf8Parsing(#[from] std::string::FromUtf8Error),

    #[error("base64 codec error: {0}")]
    Base64Codec(#[from] base64::DecodeError),

    #[error("URL encoding error: {0}")]
    UrlEncoding(#[from] serde_urlencoded::ser::Error),

    #[error("chrono parsing error: {0}")]
    ChronoParser(#[from] chrono::ParseError),

    #[error("jsonwebtoken lib error: {0}")]
    JsonWebTokenLib(#[from] jsonwebtoken::errors::Error),

    #[error("JSON parsing error: {0}")]
    JsonParsing(#[from] serde_json::Error),

    // domain errors
    #[error("OAuth2 error: client_id is missing")]
    OAuth2MissingClientId,

    #[error("OAuth2 error: client_id ({0}) is not registered")]
    OAuth2UnknownClientId(String),

    #[error("Mee authority signature is missing")]
    MissingMeeAuthoritySignature,
}

impl From<TransactionError<MeeOidcProviderErr>> for MeeOidcProviderErr {
    fn from(value: TransactionError<MeeOidcProviderErr>) -> Self {
        match value {
            TransactionError::Connection(e) => e.into(),
            TransactionError::Transaction(e) => e,
        }
    }
}

impl IntoResponse for MeeOidcProviderErr {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}
