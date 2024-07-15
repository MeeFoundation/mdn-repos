use axum::{http::StatusCode, response::IntoResponse};
use sea_orm::TransactionError;

pub type MdnLicenseManagerResult<T = (), E = MdnLicenseManagerErr> =
    std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub enum MdnLicenseManagerErr {
    #[error("HTTP parsing error: {0}")]
    HttpParsing(#[from] axum::http::Error),

    #[error("UTF-8 parsing error: {0}")]
    Utf8Parsing(#[from] std::string::FromUtf8Error),

    #[error("Enum parsing error: {0}")]
    EnumParsing(#[from] strum::ParseError),

    #[error("std::io error: {0}")]
    StdIo(#[from] std::io::Error),

    #[error("SQL driver error: {0}")]
    SqlError(#[from] sea_orm::error::DbErr),

    #[error("Anyhow error: {0}")]
    AnyhowError(#[from] anyhow::Error),

    #[error("Boxed std::error::Error: {0}")]
    BoxedStdError(#[from] Box<dyn std::error::Error + Send + Sync>),

    #[error("{0} with uid {1} is not found")]
    EntityNotFound(String, String),

    #[error("{0} with uid {1} for {2} with uid {3} is not found")]
    DependedEntityNotFound(String, String, String, String),

    #[error(
        "Mee data network license application error: Only HILs with status 'DRAFT' can be updated. But HIL with uuid ({0}) has ({1}) status"
    )]
    MdnLicenseApplicationUpdateNotDraftError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Draft' can be submitted to processing. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToProcessingError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Processing' can be rejected. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToRejectedError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Processing' can be approved. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToApprovedError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Processing' can be canceled. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToCanceledError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Canceled' can be moved to 'Draft' status. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToDraftError(String, String),

    #[error("Mee data network license application error: Only applications with status 'Approved' can be discontinued. HIL uid: ({0}) has status: {1}")]
    MdnLicenseApplicationToDiscontinuedError(String, String),

    #[error(
        "Mee provider cloud node DID ({0}) is not found for the provider ({1})"
    )]
    ProviderLinkDidNotFound(String, String),
}

impl From<TransactionError<MdnLicenseManagerErr>> for MdnLicenseManagerErr {
    fn from(value: TransactionError<MdnLicenseManagerErr>) -> Self {
        match value {
            TransactionError::Connection(e) => e.into(),
            TransactionError::Transaction(e) => e,
        }
    }
}

impl IntoResponse for MdnLicenseManagerErr {
    fn into_response(self) -> axum::response::Response {
        tracing::error!("RESTful API internal error: {self:#?}");
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}
