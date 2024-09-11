use super::api_types::{
    DelegateReadAccessToProviderRequest, GetPersonaAttributesRequest,
    GetPersonaAttributesResponse, SetPersonaAttributesRequest,
};
use crate::error::AgentServiceResult;
use futures::StreamExt;
use mee_data_sync::{
    iroh::iroh_net::key::SecretKey,
    mdn::{
        common::node::MdnAgentProviderNode,
        provider_agent::{
            delegation::manager::{
                ImportCapabilitiesFromProvider,
                ImportCapabilitiesFromVirtualAgent, MdnProviderCapabilityPack,
            },
            node::MdnAgentProviderNodeWillowImpl,
        },
    },
    willow::peer::WillowPeer,
};
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnProviderAgentNodeService {
    node: Arc<dyn MdnAgentProviderNode + Send + Sync>,
}

impl MdnProviderAgentNodeService {
    pub async fn new(
        iroh_node_secret_key: SecretKey,
    ) -> AgentServiceResult<Self> {
        let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

        let provider_mdn_node =
            Arc::new(MdnAgentProviderNodeWillowImpl::new(willow_peer).await?);

        Ok(Self {
            node: provider_mdn_node,
        })
    }
    pub async fn set_persona_attributes(
        &self,
        SetPersonaAttributesRequest { key, value }: SetPersonaAttributesRequest,
    ) -> AgentServiceResult {
        self.node
            .mdn_data_store()
            .set_value(&key, value.as_bytes().to_vec())
            .await?;

        Ok(())
    }
    pub async fn get_persona_attributes(
        &self,
        GetPersonaAttributesRequest { key }: GetPersonaAttributesRequest,
    ) -> AgentServiceResult<Option<GetPersonaAttributesResponse>> {
        let mut res: Vec<_> = self
            .node
            .mdn_data_store()
            .get_all_values_stream()
            .await?
            .filter_map(|v| async {
                if v.key == key {
                    Some(v)
                } else {
                    None
                }
            })
            .collect()
            .await;

        let res = match res.pop() {
            Some(r) => Some(r.try_into()?),
            None => None,
        };

        Ok(res)
    }
    pub async fn import_search_schemas_ns_from_virtual_agent(
        &self,
        caps: ImportCapabilitiesFromVirtualAgent,
    ) -> AgentServiceResult {
        let mut intent_handle = self
            .node
            .mdn_delegation_manager()
            .import_search_schemas_ns_from_virtual_agent(caps)
            .await?;

        // TODO handle properly
        tokio::spawn(async move {
            if let Err(e) = intent_handle.complete().await {
                tracing::error!("Error processing sync intent: {e}");
            }
        });

        Ok(())
    }
    pub async fn import_capabilities_from_provider(
        &self,
        caps: ImportCapabilitiesFromProvider,
    ) -> AgentServiceResult {
        let mut intent_handle = self
            .node
            .mdn_delegation_manager()
            .import_capabilities_from_provider(caps)
            .await?;

        // TODO handle properly
        tokio::spawn(async move {
            if let Err(e) = intent_handle.complete().await {
                tracing::error!("Error processing sync intent: {e}");
            }
        });

        Ok(())
    }
    pub async fn delegate_read_access_to_provider(
        &self,
        DelegateReadAccessToProviderRequest {
            data_path,
            provider_id,
        }: DelegateReadAccessToProviderRequest,
    ) -> AgentServiceResult<MdnProviderCapabilityPack> {
        let res = self
            .node
            .mdn_delegation_manager()
            .delegate_read_access_to_provider(&data_path, provider_id.parse()?)
            .await?;

        Ok(res)
    }
    pub async fn iroh_net_ticket(&self) -> AgentServiceResult<String> {
        let ticket = self.node.network_node_ticket().await?;

        Ok(ticket.to_string())
    }
    pub async fn willow_id(&self) -> AgentServiceResult<String> {
        let ticket = self.node.user_id().await?;

        Ok(ticket.to_string())
    }
}
