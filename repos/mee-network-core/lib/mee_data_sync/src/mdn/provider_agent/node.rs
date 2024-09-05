use super::{
    caps::MdnProviderCapabilityManager,
    delegation::{manager::MdnProviderDelegationManager, MdnProviderDelegationManagerImpl},
    namespace::MdnProviderNamespaceStoreManager,
};
use crate::{
    error::MeeDataSyncResult,
    mdn::common::{
        network::MdnAgentDataNodeNetworkOps,
        node::MdnAgentProviderNode,
        store::{KeyComponents, MdnAgentDataNodeKvStore},
        user::MdnAgentDataNodeUserOps,
    },
    willow::peer::WillowPeer,
};
use async_trait::async_trait;
use std::sync::Arc;
use tokio::task::JoinHandle;

#[derive(Clone)]
pub struct MdnAgentProviderNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub(crate) mdn_ns_store_manager: MdnProviderNamespaceStoreManager,
    mdn_delegation_manager: Arc<MdnProviderDelegationManagerImpl>,
    _background_jobs: Arc<Vec<JoinHandle<()>>>,
}

impl MdnAgentProviderNode for MdnAgentProviderNodeWillowImpl {
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnProviderDelegationManager + Send + Sync> {
        self.mdn_delegation_manager.clone()
    }
    fn mdn_data_store(
        &self,
    ) -> Arc<dyn MdnAgentDataNodeKvStore<KeyComps = KeyComponents> + Send + Sync> {
        Arc::new(self.clone())
    }
}

impl MdnAgentProviderNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let mdn_ns_store_manager = MdnProviderNamespaceStoreManager::new_in_memory(
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        let mdn_provider_capability_manager = MdnProviderCapabilityManager::new_in_memory();

        let mdn_delegation_manager = MdnProviderDelegationManagerImpl::new(
            willow_peer.clone(),
            mdn_ns_store_manager.clone(),
            mdn_provider_capability_manager,
        )
        .await?;

        let background_jobs = mdn_delegation_manager.clone().run_background_jobs();

        Ok(Self {
            _background_jobs: Arc::new(background_jobs),
            mdn_delegation_manager: Arc::new(mdn_delegation_manager),
            mdn_ns_store_manager,
            willow_peer,
        })
    }
}

#[async_trait]
impl MdnAgentDataNodeNetworkOps for MdnAgentProviderNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}

#[async_trait]
impl MdnAgentDataNodeUserOps for MdnAgentProviderNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}
