use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_identity_context::{
        api_client::MdnIdentityContextApiClient,
        api_types::{CreateMdnIdentityContextRequest, MdnIdentityContextResponse},
    },
    native_agent::{
        idm::user_auth::MdnUserAccountManager, mdn_capabilities::manager::MdnCapabilitiesManager,
    },
};
use async_trait::async_trait;
use std::sync::Arc;

/// Internal context manager with low-level details knowledge
#[async_trait]
pub trait MdnIdentityContextManager {
    async fn create_context(
        &self,
        custodian_uid: String,
        willow_namespace_id: String,
        context_description: String,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse>;
    async fn list_contexts(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityContextResponse>>;
}

pub struct MdnIdentityContextManagerDefault {
    mdn_identity_context_api_client: Arc<dyn MdnIdentityContextApiClient + Send + Sync>,
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    mdn_capabilities_manager: Arc<dyn MdnCapabilitiesManager + Send + Sync>,
}

impl MdnIdentityContextManagerDefault {
    pub fn new(
        mdn_identity_context_api_client: Arc<dyn MdnIdentityContextApiClient + Send + Sync>,
        mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
        mdn_capabilities_manager: Arc<dyn MdnCapabilitiesManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_capabilities_manager,
            mdn_identity_context_api_client,
            mdn_user_account_manager,
        }
    }
}

#[async_trait]
impl MdnIdentityContextManager for MdnIdentityContextManagerDefault {
    async fn create_context(
        &self,
        custodian_uid: String,
        willow_namespace_id: String,
        context_description: String,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse> {
        let auth_token = self
            .mdn_user_account_manager
            .get_user_auth_token_required()
            .await?;

        let context_ops_cap_token = self
            .mdn_capabilities_manager
            .context_ops_cap_local()
            .await?;

        let res = self
            .mdn_identity_context_api_client
            .create_context(
                CreateMdnIdentityContextRequest {
                    // TODO provide real willow ns
                    willow_namespace_id,
                    custodian_uid,
                    context_ops_cap_token,
                    context_description,
                },
                &auth_token,
            )
            .await?;

        Ok(res)
    }
    async fn list_contexts(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityContextResponse>> {
        let auth_token = self
            .mdn_user_account_manager
            .get_user_auth_token_required()
            .await?;

        self.mdn_identity_context_api_client
            .list_contexts(&auth_token)
            .await
    }
}
