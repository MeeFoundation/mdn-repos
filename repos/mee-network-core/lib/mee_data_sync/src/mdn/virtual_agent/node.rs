use super::{
    delegation::VirtualAgentDelegationManager, namespace::VirtualAgentNamespaceStoreManager,
    store::VirtualAgentSearchSchemasStore,
};
use crate::{
    error::MeeDataSyncResult,
    mdn::common::{
        network::MdnAgentDataNodeNetworkOps, node::MdnVirtualAgentNode,
        store::MdnAgentDataNodeKvStore, user::MdnAgentDataNodeUserOps,
    },
    willow::peer::WillowPeer,
};
use async_trait::async_trait;
use std::sync::Arc;

#[derive(Clone)]
pub struct VirtualAgentWillowNodeImpl {
    pub(crate) willow_peer: WillowPeer,
    pub virtual_agent_delegation_manager: VirtualAgentDelegationManager,
    search_schemas_store: VirtualAgentSearchSchemasStore,
}

impl VirtualAgentWillowNodeImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let virtual_agent_ns_store_manager = VirtualAgentNamespaceStoreManager::new_in_memory(
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        Ok(Self {
            virtual_agent_delegation_manager: VirtualAgentDelegationManager::new(
                willow_peer.clone(),
                virtual_agent_ns_store_manager.clone(),
            ),
            search_schemas_store: VirtualAgentSearchSchemasStore::new(
                willow_peer.clone(),
                virtual_agent_ns_store_manager.clone(),
            )
            .await?,
            willow_peer,
        })
    }
}

#[async_trait]
impl MdnAgentDataNodeNetworkOps for VirtualAgentWillowNodeImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}

#[async_trait]
impl MdnAgentDataNodeUserOps for VirtualAgentWillowNodeImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}

impl MdnVirtualAgentNode for VirtualAgentWillowNodeImpl {
    fn mdn_delegation_manager(&self) -> VirtualAgentDelegationManager {
        self.virtual_agent_delegation_manager.clone()
    }

    fn search_schemas_store(&self) -> std::sync::Arc<dyn MdnAgentDataNodeKvStore + Send + Sync> {
        Arc::new(self.search_schemas_store.clone())
    }
}
