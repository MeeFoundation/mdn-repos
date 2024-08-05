use async_trait::async_trait;
use error::MeeDataSyncResult;

pub mod error;
pub mod mdn;
// TODO hide it
pub mod willow;

/// Low-level storage interface for MDN agents (excluding virtual ones)
#[async_trait]
pub trait SyncedKvStorage {
    async fn set_value(key: String, value: Vec<u8>) -> MeeDataSyncResult;
    async fn get_value_exact(key: String) -> MeeDataSyncResult<Vec<u8>>;
    async fn del_value_exact(key: String) -> MeeDataSyncResult;
    // async fn get_value_pattern(key: String) -> MeeDataSyncResult<Vec<u8>>;
    // async fn del_value_pattern(key: String) -> MeeDataSyncResult;
}
