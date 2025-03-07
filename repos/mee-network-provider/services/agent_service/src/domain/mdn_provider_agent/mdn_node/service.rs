use super::api_types::{
    DelPersonaAttributesRequest, DelegateReadAccessToProviderRequest,
    DelegatedCap, GetPersonaAttributesRequest, GetPersonaAttributesResponse,
    ImportedCapability, SetPersonaAttributesRequest,
};
use crate::error::AgentServiceResult;
use futures::{StreamExt, TryStreamExt};
use mee_data_sync::{
    iroh::iroh_base::SecretKey,
    mdn_iiw38::{
        common::{node::MdnAgentProviderNode, store::ReadDataRecord},
        provider_agent::{
            delegation::manager::{
                ImportCapabilitiesFromProvider,
                ImportCapabilitiesFromVirtualAgent,
            },
            node::MdnAgentProviderNodeWillowImpl,
        },
    },
    willow::peer::WillowPeer,
};
use std::sync::Arc;
use tokio::{sync::Mutex, task::JoinHandle};

#[derive(Clone)]
pub struct MdnProviderAgentNodeService {
    node: Arc<dyn MdnAgentProviderNode + Send + Sync>,
    sync_intent_handles: Arc<Mutex<Vec<JoinHandle<()>>>>,
}

impl MdnProviderAgentNodeService {
    pub async fn new(
        iroh_node_secret_key: SecretKey,
    ) -> AgentServiceResult<Self> {
        let willow_peer = WillowPeer::try_new(iroh_node_secret_key).await?;

        let provider_mdn_node =
            Arc::new(MdnAgentProviderNodeWillowImpl::new(willow_peer).await?);

        Ok(Self {
            sync_intent_handles: Arc::new(Mutex::new(vec![])),
            node: provider_mdn_node,
        })
    }
    pub async fn delegated_caps(
        &self,
    ) -> AgentServiceResult<Vec<DelegatedCap>> {
        let res = self
            .node
            .mdn_delegation_manager()
            .delegated_caps()
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    pub async fn imported_caps(
        &self,
    ) -> AgentServiceResult<Vec<ImportedCapability>> {
        let res = self
            .node
            .mdn_delegation_manager()
            .imported_caps()
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    pub async fn revoke_shared_access_from_provider(
        &self,
        DelegatedCap {
            capability_id,
            shared_data_path,
            cap_receiver,
        }: DelegatedCap,
    ) -> AgentServiceResult {
        self.node
            .mdn_delegation_manager()
            .revoke_shared_access_from_provider(
                &capability_id,
                &shared_data_path,
                cap_receiver.parse()?,
            )
            .await?;

        Ok(())
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
    pub async fn del_persona_attributes(
        &self,
        DelPersonaAttributesRequest { key }: DelPersonaAttributesRequest,
    ) -> AgentServiceResult<Vec<bool>> {
        let res = self.node.mdn_data_store().del_value(&key).await?;

        Ok(res)
    }
    pub async fn get_persona_attributes(
        &self,
        GetPersonaAttributesRequest { key }: GetPersonaAttributesRequest,
    ) -> AgentServiceResult<Vec<GetPersonaAttributesResponse>> {
        let res: Vec<_> = self
            .node
            .mdn_data_store()
            .get_all_values_stream()
            .await?
            .map(AgentServiceResult::Ok)
            .try_filter_map(|v| async {
                Ok(if v.key.starts_with(&key) {
                    Some(v.try_into()?)
                } else {
                    None
                })
            })
            .try_collect()
            .await?;

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
        let res = self
            .node
            .mdn_delegation_manager()
            .import_capabilities_from_provider(caps)
            .await?;

        let mut intents = self.sync_intent_handles.lock().await;

        intents.push(res.sync_intent_task);

        Ok(())
    }
    pub async fn delegate_read_access_to_provider(
        &self,
        DelegateReadAccessToProviderRequest {
            data_path,
            provider_id,
        }: DelegateReadAccessToProviderRequest,
    ) -> AgentServiceResult<ImportCapabilitiesFromProvider> {
        let caps = self
            .node
            .mdn_delegation_manager()
            .delegate_read_access_to_provider(&data_path, provider_id.parse()?)
            .await?;

        let res = ImportCapabilitiesFromProvider {
            provider_node_ticket: self.iroh_net_ticket().await?,
            caps,
        };

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
    pub async fn virtual_agent_search_schemas(
        &self,
    ) -> AgentServiceResult<Vec<ReadDataRecord>> {
        Ok(self
            .node
            .mdn_delegation_manager()
            .virtual_agent_search_schemas()
            .await?)
    }
}
