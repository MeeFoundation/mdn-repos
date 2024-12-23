use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_identity_context::api_types::MdnIdentityContextResponse,
    mdn_common::mdn_custodian_willow_storage::MdnCustodianWillowStorage,
    native_agent::mdn_identity_context::manager::MdnIdentityContextManager,
};
use async_trait::async_trait;
use std::sync::Arc;

#[async_trait]
pub trait MdnIdentityContextController {
    async fn write_data(&self, key: String, value: String) -> MdnIdentityAgentResult;
    async fn read_data(&self, key: String) -> MdnIdentityAgentResult<Option<String>>;
}

// TODO create new type
// TODO impl MdnIdentityContextController for MdnIdentityContextMetadata
pub type MdnIdentityContextMetadata = MdnIdentityContextResponse;

#[async_trait]
/// High-level manager exposed to Agent SDK
pub trait MdnNodeManager {
    async fn create_context(
        &self,
        custodian_uid: String,
        context_description: String,
    ) -> MdnIdentityAgentResult<MdnIdentityContextMetadata>;
    async fn list_contexts(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityContextMetadata>>;
}

pub struct MdnNodeManagerIdentityAgentImpl {
    mdn_identity_context_manager: Arc<dyn MdnIdentityContextManager + Send + Sync>,
    mdn_custodian_willow_storage: Arc<dyn MdnCustodianWillowStorage + Send + Sync>,
}

impl MdnNodeManagerIdentityAgentImpl {
    pub fn new(
        mdn_identity_context_manager: Arc<dyn MdnIdentityContextManager + Send + Sync>,
        mdn_custodian_willow_storage: Arc<dyn MdnCustodianWillowStorage + Send + Sync>,
    ) -> Self {
        Self {
            mdn_custodian_willow_storage,
            mdn_identity_context_manager,
        }
    }
}

#[async_trait]
impl MdnNodeManager for MdnNodeManagerIdentityAgentImpl {
    async fn create_context(
        &self,
        custodian_uid: String,
        context_description: String,
    ) -> MdnIdentityAgentResult<MdnIdentityContextMetadata> {
        // TODO provide real willow ns
        let res = self
            .mdn_identity_context_manager
            .create_context(
                custodian_uid,
                "willow_namespace_id".to_string(),
                context_description,
            )
            .await?;

        Ok(res)
    }

    async fn list_contexts(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityContextMetadata>> {
        self.mdn_identity_context_manager.list_contexts().await
    }
}
