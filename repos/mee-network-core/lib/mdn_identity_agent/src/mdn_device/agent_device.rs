use super::{
    device::device_manager::{MdnUserDevicesManager, MdnUserDevicesManagerDefault},
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
};
use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::{
        user_account::api_client::MdnUserAccountApiClientDefault,
        user_devices::api_client::MdnUserDevicesApiClientDefault,
    },
};
// use mee_data_sync::willow::peer::WillowPeer;
use std::sync::Arc;
use url::Url;

pub struct MdnAgentDeviceConfig {
    pub local_db_file_path: String,
    pub mdn_api_base_url: Url,
}

pub struct MdnAgentDevice {
    // willow_peer: WillowPeer,
    pub mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    pub mdn_user_devices_manager: Arc<dyn MdnUserDevicesManager + Send + Sync>,
}

impl MdnAgentDevice {
    pub async fn try_new(
        MdnAgentDeviceConfig {
            local_db_file_path,
            mdn_api_base_url,
        }: MdnAgentDeviceConfig,
    ) -> MdnIdentityAgentResult<Self> {
        let local_db = Arc::new(LocalKvDbRedb::try_new(local_db_file_path).await?);

        let mdn_user_account_manager = Arc::new(MdnUserAccountManagerDefault::new(
            Arc::new(MdnUserLocalDbDefault::new(local_db)),
            Arc::new(MdnUserAccountApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
        ));

        let mdn_user_devices_manager = Arc::new(MdnUserDevicesManagerDefault::new(
            Arc::new(MdnUserDevicesApiClientDefault::try_new(mdn_api_base_url)?),
            mdn_user_account_manager.clone(),
        ));

        Ok(Self {
            // willow_peer: WillowPeer::new(mdn_user_account_manager.get_iroh_node_key().await?).await?,
            mdn_user_account_manager,
            mdn_user_devices_manager,
        })
    }
}
