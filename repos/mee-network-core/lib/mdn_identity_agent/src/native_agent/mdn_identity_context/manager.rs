use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_identity_context::{
        api_client::MdnIdentityContextApiClient, api_types::MdnIdentityContextResponse,
    },
    native_agent::{
        idm::user_auth::MdnUserAccountManager, mdn_capabilities::manager::MdnCapabilitiesManager,
    },
};
use async_trait::async_trait;
use std::sync::Arc;

#[async_trait]
pub trait MdnIdentityContextManager {
    async fn create_context(
        &self,
        custodian_uid: &str,
        willow_namespace_id: &str,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse>;
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
        custodian_uid: &str,
        willow_namespace_id: &str,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse> {
        todo!()
    }
}
