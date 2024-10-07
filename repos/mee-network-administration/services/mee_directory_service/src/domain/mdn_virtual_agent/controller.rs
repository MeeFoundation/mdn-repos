use super::mdn_node::service::MdnVirtualAgentNodeService;
use crate::error::{MeeDirectoryServiceErr, MeeDirectoryServiceResult};
use mee_secrets_manager::signatures_service::SignaturesService;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnVirtualAgentCtl {
    pub(crate) mdn_virtual_agent_node_service: MdnVirtualAgentNodeService,
}

impl MdnVirtualAgentCtl {
    pub(crate) async fn new(
        signatures_service: Arc<dyn SignaturesService + Sync + Send>,
    ) -> MeeDirectoryServiceResult<Self> {
        Ok(Self {
            mdn_virtual_agent_node_service: MdnVirtualAgentNodeService::new(
                signatures_service.get_iroh_signature().await?.ok_or_else(
                    || {
                        MeeDirectoryServiceErr::VirtualAgentSecretsManagement(
                            "Missing iroh secret key".to_string(),
                        )
                    },
                )?,
            )
            .await?,
        })
    }
}
