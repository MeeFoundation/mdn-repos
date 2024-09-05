use super::{
    delegation::MdnDataOwnerDelegationManager, namespace::MdnDataOwnerNamespaceStoreManager,
};
use crate::{
    error::MeeDataSyncResult,
    mdn::common::{network::MdnAgentDataNodeNetworkOps, user::MdnAgentDataNodeUserOps},
    willow::peer::WillowPeer,
};
use async_trait::async_trait;
use std::sync::Arc;
use tokio::task::JoinHandle;

pub struct MdnAgentDataOwnerNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub mdn_delegation_manager: MdnDataOwnerDelegationManager,
    _background_jobs: Arc<Vec<JoinHandle<()>>>,
}

impl MdnAgentDataOwnerNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let mdn_ns_store_manager = MdnDataOwnerNamespaceStoreManager::new_in_memory(
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        let mdn_delegation_manager =
            MdnDataOwnerDelegationManager::new(willow_peer.clone(), mdn_ns_store_manager)?;

        let background_jobs = mdn_delegation_manager.clone().run_background_jobs();

        Ok(Self {
            _background_jobs: Arc::new(background_jobs),
            mdn_delegation_manager,
            willow_peer,
        })
    }
}

#[async_trait]
impl MdnAgentDataNodeNetworkOps for MdnAgentDataOwnerNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}

#[async_trait]
impl MdnAgentDataNodeUserOps for MdnAgentDataOwnerNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}
