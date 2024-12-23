use iroh::{endpoint::ConnectionError, ticket};
use iroh_willow::proto::data_model::{InvalidPathError, InvalidPathError2};
use std::{
    array::TryFromSliceError, num::TryFromIntError, string::FromUtf8Error, sync::PoisonError,
};
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
    IrohBaseTicket(#[from] ticket::Error),

    #[error("tokio task join error: {0}")]
    TokioJoinError(#[from] JoinError),

    #[error("JSON codec error: {0}")]
    JsonCodec(#[from] serde_json::Error),

    #[error("willow invalid path original error: {0}")]
    WillowInvalidPathOriginal(#[from] InvalidPathError),

    #[error("willow invalid path wrapper error: {0}")]
    WillowInvalidPath(#[from] InvalidPathError2),

    #[error("std::sync::Mutex error: {0}")]
    StdMutex(String),

    #[error("std::array::TryFromSliceError: {0}")]
    StdTryFromSliceError(#[from] TryFromSliceError),

    #[error("std::num::TryFromIntError: {0}")]
    StdTryFromIntError(#[from] TryFromIntError),

    #[error("std FromUtf8Error: {0}")]
    StdFromUtf8Error(#[from] FromUtf8Error),

    #[error("std::io::Error : {0}")]
    StdIoError(#[from] std::io::Error),

    // domain errors
    #[error("Error during synced KV-storage operation: {0}")]
    SyncedKvStorage(String),

    #[error("Willow namespace handler error: {0}")]
    WillowNamespaceHandler(String),

    #[error("Willow path handler error: {0}")]
    WillowPathHandler(String),

    #[error("Willow delegation handler error: {0}")]
    WillowDelegationHandler(String),
}

impl<T> From<PoisonError<T>> for MeeDataSyncErr {
    fn from(v: PoisonError<T>) -> Self {
        Self::StdMutex(v.to_string())
    }
}
