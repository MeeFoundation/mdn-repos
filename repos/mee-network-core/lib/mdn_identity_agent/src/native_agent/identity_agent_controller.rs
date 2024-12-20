use super::{
    device_storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    mdn_capabilities::manager::{MdnCapabilitiesManager, MdnCapabilitiesManagerDefault},
    mdn_custodian_storage::manager::{
        MdnCustodianStorageManager, MdnCustodianStorageManagerDefault,
    },
    mdn_identity_context::manager::MdnIdentityContextManagerDefault,
    mdn_node::manager::{MdnNodeManager, MdnNodeManagerUserAgentImpl},
};
use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::{
        mdn_capabilities::api_client::MdnCapabilitiesApiClientDefault,
        mdn_custodian_storage::api_client::MdnCustodianStorageApiClientDefault,
        mdn_identity_context::api_client::MdnIdentityContextApiClientDefault,
        mdn_user::api_client::MdnUserAccountApiClientDefault,
    },
};
use async_trait::async_trait;
use std::sync::Arc;
use url::Url;

pub struct MdnIdentityAgentControllerConfig {
    pub local_db_file_path: String,
    pub mdn_api_base_url: Url,
}

#[async_trait]
pub trait MdnIdentityAgentController {
    fn mdn_user_account_manager(&self) -> Arc<dyn MdnUserAccountManager + Send + Sync>;
    fn mdn_node_manager(&self) -> Arc<dyn MdnNodeManager + Send + Sync>;
    async fn init(&self) -> MdnIdentityAgentResult<MdnIdentityAgentControllerInitStatus>;
}

pub enum MdnIdentityAgentControllerInitStatus {
    LoginRequired,
    Initialized,
}

#[async_trait]
impl MdnIdentityAgentController for MdnIdentityAgentControllerImpl {
    fn mdn_user_account_manager(&self) -> Arc<dyn MdnUserAccountManager + Send + Sync> {
        self.mdn_user_account_manager.clone()
    }

    fn mdn_node_manager(&self) -> Arc<dyn MdnNodeManager + Send + Sync> {
        self.mdn_node_manager.clone()
    }
    async fn init(&self) -> MdnIdentityAgentResult<MdnIdentityAgentControllerInitStatus> {
        // TODO check auth token freshness
        let auth_token = self.mdn_user_account_manager.get_user_auth_token().await?;

        let status = if auth_token.is_some() {
            self.mdn_user_custodian_storage_manager
                .register_storage()
                .await?;

            self.mdn_capabilities_manager
                .issue_owner_context_ops_cap()
                .await?;

            MdnIdentityAgentControllerInitStatus::Initialized
        } else {
            MdnIdentityAgentControllerInitStatus::LoginRequired
        };

        Ok(status)
    }
}

pub struct MdnIdentityAgentControllerImpl {
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    mdn_user_custodian_storage_manager: Arc<dyn MdnCustodianStorageManager + Send + Sync>,
    mdn_capabilities_manager: Arc<dyn MdnCapabilitiesManager + Send + Sync>,
    mdn_node_manager: Arc<dyn MdnNodeManager + Send + Sync>,
}

impl MdnIdentityAgentControllerImpl {
    pub async fn try_new(
        MdnIdentityAgentControllerConfig {
            local_db_file_path,
            mdn_api_base_url,
        }: MdnIdentityAgentControllerConfig,
    ) -> MdnIdentityAgentResult<Self> {
        let local_db = Arc::new(LocalKvDbRedb::try_new(local_db_file_path).await?);

        let mdn_user_account_manager = Arc::new(MdnUserAccountManagerDefault::new(
            Arc::new(MdnUserLocalDbDefault::new(local_db.clone())),
            Arc::new(MdnUserAccountApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
        ));

        let mdn_user_custodian_storage_manager = Arc::new(MdnCustodianStorageManagerDefault::new(
            Arc::new(MdnCustodianStorageApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
            mdn_user_account_manager.clone(),
        ));

        let mdn_capabilities_manager = Arc::new(MdnCapabilitiesManagerDefault::new(
            Arc::new(MdnUserLocalDbDefault::new(local_db.clone())),
            Arc::new(MdnCapabilitiesApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
            mdn_user_account_manager.clone(),
        ));

        let mdn_identity_context_manager = Arc::new(MdnIdentityContextManagerDefault::new(
            Arc::new(MdnIdentityContextApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
            mdn_user_account_manager.clone(),
            mdn_capabilities_manager.clone(),
        ));

        let mdn_node_manager = Arc::new(MdnNodeManagerUserAgentImpl::new(
            mdn_identity_context_manager,
        ));

        Ok(Self {
            mdn_user_account_manager,
            mdn_user_custodian_storage_manager,
            mdn_capabilities_manager,
            mdn_node_manager,
        })
    }
}
