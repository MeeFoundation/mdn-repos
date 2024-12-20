use crate::error::MeeDirectoryServiceResult;
use futures::StreamExt;
use mee_data_sync::{
    iroh::key::SecretKey,
    mdn::{
        common::{node::MdnVirtualAgentNode, store::ReadDataRecord},
        provider_agent::delegation::manager::ImportCapabilitiesFromVirtualAgent,
        virtual_agent::node::VirtualAgentWillowNodeImpl,
    },
    willow::{peer::WillowPeer, proto::keys::UserId},
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
    pub async fn search_schemas(
        &self,
    ) -> MeeDirectoryServiceResult<Vec<ReadDataRecord>> {
        let res = self
            .node
            .search_schemas_store()
            .get_all_values_stream()
            .await?
            .collect()
            .await;

        Ok(res)
    }
    pub async fn share_search_schemas_ns_with_provider(
        &self,
        provider_id: UserId,
    ) -> MeeDirectoryServiceResult<ImportCapabilitiesFromVirtualAgent> {
        let caps = self
            .node
            .mdn_delegation_manager()
            .share_search_schemas_ns_with_provider(provider_id)
            .await?;

        let res = ImportCapabilitiesFromVirtualAgent {
            virtual_agent_node_ticket: self.iroh_net_ticket().await?,
            caps,
        };

        Ok(res)
    }
}
