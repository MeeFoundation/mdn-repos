use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_data_sync::{
    error::MeeDataSyncErr,
    willow::{
        peer::WillowPeer,
        proto::{
            data_model::{NamespaceId, Path, PathExt},
            grouping::Range3d,
        },
    },
};

#[async_trait]
pub trait WillowDataStorageManager {
    async fn set_value(
        &self,
        ns: NamespaceId,
        path: &str,
        value: Vec<u8>,
    ) -> MdnIdentityAgentResult;
    async fn get_value(
        &self,
        ns: NamespaceId,
        path: &str,
    ) -> MdnIdentityAgentResult<Option<Vec<u8>>>;
}

pub struct WillowDataStorageManagerImpl {
    willow_peer: WillowPeer,
}

impl WillowDataStorageManagerImpl {
    pub fn new(willow_peer: WillowPeer) -> Self {
        Self { willow_peer }
    }
}

#[async_trait]
impl WillowDataStorageManager for WillowDataStorageManagerImpl {
    async fn set_value(
        &self,
        ns: NamespaceId,
        path: &str,
        value: Vec<u8>,
    ) -> MdnIdentityAgentResult {
        self.willow_peer
            .willow_data_manager
            .insert_entry(
                ns,
                Path::from_bytes(&[path.as_bytes()]).map_err(MeeDataSyncErr::from)?,
                value,
            )
            .await?;

        Ok(())
    }
    async fn get_value(
        &self,
        ns: NamespaceId,
        path: &str,
    ) -> MdnIdentityAgentResult<Option<Vec<u8>>> {
        if let Some(entry) = self
            .willow_peer
            .willow_data_manager
            .get_entries(ns, Range3d::new_full())
            .await?
            .pop()
        {
            if entry.path()
                == &Path::from_bytes(&[path.as_bytes()]).map_err(MeeDataSyncErr::from)?
            {
                if let Some(payload) = self
                    .willow_peer
                    .willow_data_manager
                    .read_entry_payload(entry)
                    .await?
                {
                    return Ok(Some(payload.to_vec()));
                }
            }
        }

        Ok(None)
    }
}
