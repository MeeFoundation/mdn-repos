use mee_crypto::{error::MeeCryptoErr, josekit};
use mee_data_sync::error::MeeDataSyncErr;
use mee_did::error::MeeDidErr;

pub type MdnIdentityAgentResult<T = ()> = Result<T, MdnIdentityAgentErr>;

#[derive(Debug, thiserror::Error)]
pub enum MdnIdentityAgentErr {
    // internal errors
    #[error("Anyhow error: {0}")]
    Anyhow(#[from] anyhow::Error),

    #[error("URL parsing error: {0}")]
    UrlParsing(#[from] url::ParseError),

    #[error("Serde JSON error: {0}")]
    SerdeJson(#[from] serde_json::Error),

    #[error("std::string UTF-8 parsing error: {0}")]
    StdFromUtf8Error(#[from] std::string::FromUtf8Error),

    #[error("tokio join error: {0}")]
    TokioJoinError(#[from] tokio::task::JoinError),

    #[error("redb database error: {0}")]
    RedbDatabase(#[from] redb::DatabaseError),

    #[error("redb transaction error: {0}")]
    RedbTransaction(#[from] redb::TransactionError),

    #[error("redb table error: {0}")]
    RedbTable(#[from] redb::TableError),

    #[error("redb storage error: {0}")]
    RedbStorage(#[from] redb::StorageError),

    #[error("redb commit error: {0}")]
    RedbCommit(#[from] redb::CommitError),

    #[error("HTTP client error: {0}")]
    HttpClient(#[from] reqwest::Error),

    #[error("josekit error: {0}")]
    JoseKit(#[from] josekit::JoseError),

    #[error("Mee crypto utils error: {0}")]
    MeeCryptoUtils(#[from] MeeCryptoErr),

    #[error("Mee DID utils error: {0}")]
    MeeDidUtils(#[from] MeeDidErr),

    #[error("Mee data sync module error: {0}")]
    MeeDataSync(#[from] MeeDataSyncErr),

    // domain error
    #[error("MDN user device identity sub-system error: {0}")]
    MdnDeviceIdm(String),
}
