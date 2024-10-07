use super::namespace::VirtualAgentNamespaceStoreManager;
use crate::{
    error::MeeDataSyncResult, mdn::common::store::MdnAgentDataNodeKvStore, willow::peer::WillowPeer,
};
use async_trait::async_trait;
use futures::{stream::BoxStream, StreamExt};
use iroh_willow::proto::{
    data_model::{Entry, NamespaceId},
    grouping::Range3d,
};

#[async_trait]
impl MdnAgentDataNodeKvStore for VirtualAgentSearchSchemasStore {
    fn willow_peer(&self) -> crate::willow::peer::WillowPeer {
        self.willow_peer.clone()
    }
    async fn data_ns(&self) -> MeeDataSyncResult<NamespaceId> {
        Ok(self
            .virtual_agent_ns_store_manager
            .get_schemas_ns()
            .await?
            .0)
    }

    async fn data_entries(
        &self,
        range: Range3d,
    ) -> MeeDataSyncResult<BoxStream<'_, MeeDataSyncResult<Entry>>> {
        let ns = self.data_ns().await?;

        let result = self
            .willow_peer
            .willow_data_manager
            .get_entries_stream(ns, range)
            .await?;

        Ok(result.boxed())
    }

    async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        self.remove_entries(key).await
    }
}

#[derive(Clone)]
pub struct VirtualAgentSearchSchemasStore {
    willow_peer: WillowPeer,
    virtual_agent_ns_store_manager: VirtualAgentNamespaceStoreManager,
}

impl VirtualAgentSearchSchemasStore {
    pub async fn new(
        willow_peer: WillowPeer,
        virtual_agent_ns_store_manager: VirtualAgentNamespaceStoreManager,
    ) -> MeeDataSyncResult<Self> {
        Ok(Self {
            virtual_agent_ns_store_manager,
            willow_peer,
        })
    }
}
