use super::{
    device_storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    mdn_capabilities::manager::{MdnCapabilitiesManager, MdnCapabilitiesManagerDefault},
    mdn_custodian_storage::manager::{
        MdnCustodianStorageManager, MdnCustodianStorageManagerDefault,
    },
    mdn_identity_context::manager::{MdnIdentityContextManager, MdnIdentityContextManagerDefault},
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
// use mee_data_sync::willow::peer::WillowPeer;
use std::sync::Arc;
use url::Url;

pub struct MdnIdentityAgentControllerConfig {
    pub local_db_file_path: String,
    pub mdn_api_base_url: Url,
}

pub struct MdnIdentityAgentController {
    // willow_peer: WillowPeer,
    pub mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    pub mdn_user_custodian_storage_manager: Arc<dyn MdnCustodianStorageManager + Send + Sync>,
    pub mdn_capabilities_manager: Arc<dyn MdnCapabilitiesManager + Send + Sync>,
    pub mdn_identity_context_manager: Arc<dyn MdnIdentityContextManager + Send + Sync>,
}

impl MdnIdentityAgentController {
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

        Ok(Self {
            // willow_peer: WillowPeer::new(mdn_user_account_manager.get_iroh_node_key().await?).await?,
            mdn_user_account_manager,
            mdn_user_custodian_storage_manager,
            mdn_capabilities_manager,
            mdn_identity_context_manager,
        })
    }
}
