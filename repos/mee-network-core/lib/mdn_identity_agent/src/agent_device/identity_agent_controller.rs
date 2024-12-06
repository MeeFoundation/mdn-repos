use super::{
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    mdn_custodian_storage::storage_manager::{MdnCustodianStorageManager, MdnCustodianStorageManagerDefault},
    device_storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
};
use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::{
        mdn_custodian_storage::api_client::MdnCustodianStorageApiClientDefault,
        user_account::api_client::MdnUserAccountApiClientDefault,
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
    pub mdn_user_nodes_manager: Arc<dyn MdnCustodianStorageManager + Send + Sync>,
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
            Arc::new(MdnUserLocalDbDefault::new(local_db)),
            Arc::new(MdnUserAccountApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
        ));

        let mdn_user_nodes_manager = Arc::new(MdnCustodianStorageManagerDefault::new(
            Arc::new(MdnCustodianStorageApiClientDefault::try_new(mdn_api_base_url)?),
            mdn_user_account_manager.clone(),
        ));

        Ok(Self {
            // willow_peer: WillowPeer::new(mdn_user_account_manager.get_iroh_node_key().await?).await?,
            mdn_user_account_manager,
            mdn_user_nodes_manager,
        })
    }
}
