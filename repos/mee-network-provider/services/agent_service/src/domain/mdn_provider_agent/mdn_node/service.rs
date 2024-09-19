use super::api_types::{
    DelPersonaAttributesRequest, DelegateReadAccessToProviderRequest,
    DelegatedCap, GetPersonaAttributesRequest, GetPersonaAttributesResponse,
    ImportedCapability, SetPersonaAttributesRequest,
};
use crate::error::AgentServiceResult;
use futures::{StreamExt, TryStreamExt};
use mee_data_sync::{
    iroh::iroh_net::key::SecretKey,
    mdn::{
        common::{
            network::MdnAgentDataNodeNetworkOps, node::MdnAgentProviderNode,
            store::ReadDataRecord,
        },
        provider_agent::{
            delegation::manager::{
                ImportCapabilitiesFromProvider,
                ImportCapabilitiesFromVirtualAgent,
            },
            node::MdnAgentProviderNodeWillowImpl,
        },
    },
    willow::{
        debug::progress_session_intents,
        peer::WillowPeer,
        session::{SessionInit, SessionMode},
    },
};
use std::{ops::Deref, sync::Arc, time::Duration};
use tokio::{sync::Mutex, task::JoinHandle, time::sleep};

#[derive(Clone)]
pub struct MdnProviderAgentNodeService {
    node: Arc<dyn MdnAgentProviderNode + Send + Sync>,
    sync_intent_handles: Arc<Mutex<Vec<JoinHandle<()>>>>,
}

impl MdnProviderAgentNodeService {
    pub async fn new(
        iroh_node_secret_key: SecretKey,
    ) -> AgentServiceResult<Self> {
        let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

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
        let willow_id = self.node.user_id().await?;
        let mdn_delegation_manager = self.node.mdn_delegation_manager();
        let willow_peer =
            MdnAgentDataNodeNetworkOps::willow_peer(self.node.deref());

        let intent_handle_task = tokio::spawn(async move {
            let res = async {
                let (intent_handle, intent_config) = mdn_delegation_manager
                    .import_capabilities_from_provider(caps)
                    .await?;

                let mut intent = Some(intent_handle);

                loop {
                    match intent.take() {
                        Some(int) => {
                            progress_session_intents(
                                int,
                                &format!("[{willow_id}] "),
                            )
                            .await;
                        }
                        None => {
                            let init = SessionInit::new(
                                intent_config.caps_interests.clone(),
                                SessionMode::Continuous,
                            );

                            let sync_intent = willow_peer
                                .willow_session_manager
                                .sync_with_peer(
                                    intent_config
                                        .delegated_from_ticket
                                        .node_addr()
                                        .node_id,
                                    init,
                                )
                                .await;

                            // TODO hack?
                            if sync_intent.is_err() {
                                break sync_intent;
                            }

                            intent.replace(sync_intent?);
                        }
                    };

                    sleep(Duration::from_secs(5)).await;
                }

                // AgentServiceResult::Ok(())
            };

            if let Err(e) = res.await {
                tracing::error!("{e}");
            }
        });

        let mut intents = self.sync_intent_handles.lock().await;

        intents.push(intent_handle_task);

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
