use crate::error::MeeDirectoryServiceResult;
use mee_data_sync::{
    iroh::iroh_net::key::SecretKey,
    mdn::{
        common::node::MdnVirtualAgentNode,
        virtual_agent::node::VirtualAgentWillowNodeImpl,
    },
    willow::{interest::CapabilityPack, keys::UserId, peer::WillowPeer},
};
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnVirtualAgentNodeService {
    node: Arc<dyn MdnVirtualAgentNode + Send + Sync>,
}

impl MdnVirtualAgentNodeService {
    pub async fn new(
        iroh_node_secret_key: SecretKey,
    ) -> MeeDirectoryServiceResult<Self> {
        let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

        let provider_mdn_node =
            Arc::new(VirtualAgentWillowNodeImpl::new(willow_peer).await?);

        Ok(Self {
            node: provider_mdn_node,
        })
    }
    pub async fn iroh_net_ticket(&self) -> MeeDirectoryServiceResult<String> {
        let ticket = self.node.network_node_ticket().await?;

        Ok(ticket.to_string())
    }
    pub async fn share_search_schemas_ns_with_provider(
        &self,
        provider_id: UserId,
    ) -> MeeDirectoryServiceResult<Vec<CapabilityPack>> {
        Ok(self
            .node
            .mdn_delegation_manager()
            .share_search_schemas_ns_with_provider(provider_id)
            .await?)
    }
}
