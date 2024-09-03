use super::{
    delegation::VirtualAgentDelegationManager, namespace::VirtualAgentNamespaceStoreManager,
};
use crate::{
    mdn::common::{network::MdnAgentDataNodeNetworkOps, user::MdnAgentDataNodeUserOps},
    willow::peer::WillowPeer,
};
use async_trait::async_trait;

#[derive(Clone)]
pub struct VirtualAgentWillowNodeImpl {
    pub(crate) willow_peer: WillowPeer,
    pub virtual_agent_delegation_manager: VirtualAgentDelegationManager,
}

impl VirtualAgentWillowNodeImpl {
    pub fn new(willow_peer: WillowPeer) -> Self {
        let virtual_agent_namespace_store_manager =
            VirtualAgentNamespaceStoreManager::new_in_memory();

        Self {
            virtual_agent_delegation_manager: VirtualAgentDelegationManager::new(
                willow_peer.clone(),
                virtual_agent_namespace_store_manager.clone(),
            ),
            willow_peer,
        }
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
