use iroh_net::endpoint::ConnectionError;
use iroh_willow::proto::willow::InvalidPath;
use tokio::task::JoinError;

pub type MeeDataSyncResult<T = ()> = Result<T, MeeDataSyncErr>;

#[derive(Debug, thiserror::Error)]
pub enum MeeDataSyncErr {
    // internal errors
    #[error("Anyhow error: {0}")]
    Anyhow(#[from] anyhow::Error),

    #[error("iroh-quinn protocol error: {0}")]
    IrohQuinnProtocol(#[from] ConnectionError),

    #[error("iroh-base ticket error: {0}")]
    IrohBaseTicket(#[from] iroh_base::ticket::Error),

    #[error("tokio task join error: {0}")]
    TokioJoinError(#[from] JoinError),

    #[error("willow invalid path error: {0}")]
    WillowInvalidPath(#[from] InvalidPath),

    #[error("std::sync::Mutex error: {0}")]
    StdMutex(String),

    // domain errors
    #[error("Error during synced KV-storage operation: {0}")]
    SyncedKvStorage(String),

    #[error("Willow namespace handler error: {0}")]
    WillowNamespaceHandler(String),

    #[error("Willow delegation handler error: {0}")]
    WillowDelegationHandler(String),
}
