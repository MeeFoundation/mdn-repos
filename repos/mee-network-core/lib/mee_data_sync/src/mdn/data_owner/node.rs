use super::{
    delegation::MdnDataOwnerDelegationManager,
    namespace::{MdnDataOwnerNamespaceStoreInMemory, MdnDataOwnerNamespaceStoreManager},
};
use crate::{
    error::MeeDataSyncResult,
    mdn::traits::{network::MdnAgentDataNodeNetworkOps, user::MdnAgentDataNodeUserOps},
    willow::peer::WillowPeer,
};
use async_trait::async_trait;
use std::sync::Arc;

pub struct MdnAgentDataOwnerNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub mdn_delegation_manager: MdnDataOwnerDelegationManager,
}

impl MdnAgentDataOwnerNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let mdn_ns_store_manager = MdnDataOwnerNamespaceStoreManager::new(
            Arc::new(MdnDataOwnerNamespaceStoreInMemory::new()),
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        Ok(Self {
            mdn_delegation_manager: MdnDataOwnerDelegationManager::new(
                willow_peer.clone(),
                mdn_ns_store_manager,
            ),
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
