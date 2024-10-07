use super::mdn_node::service::MdnProviderAgentNodeService;
use crate::error::{AgentServiceErr, AgentServiceResult};
use mee_secrets_manager::signatures_service::SignaturesService;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnProviderAgentCtl {
    pub(crate) mdn_provider_agent_node_service: MdnProviderAgentNodeService,
}

impl MdnProviderAgentCtl {
    pub(crate) async fn new(
        provider_authority_signatures: Arc<dyn SignaturesService + Sync + Send>,
    ) -> AgentServiceResult<Self> {
        Ok(Self {
            mdn_provider_agent_node_service: MdnProviderAgentNodeService::new(
                provider_authority_signatures
                    .get_iroh_signature()
                    .await?
                    .ok_or_else(|| {
                        AgentServiceErr::ProviderSecretsManagement(
                            "Missing iroh secret key".to_string(),
                        )
                    })?,
            )
            .await?,
        })
    }
}
