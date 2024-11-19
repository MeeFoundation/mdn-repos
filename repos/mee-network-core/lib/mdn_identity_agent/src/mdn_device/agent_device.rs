use super::{
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
};
use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::user_account::api_client::MdnUserAccountApiClientDefault,
};
use mee_data_sync::willow::peer::WillowPeer;
use std::sync::Arc;

pub struct MdnAgentDevice {
    willow_peer: WillowPeer,
    pub mdn_user_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
}

impl MdnAgentDevice {
    pub async fn try_new() -> MdnIdentityAgentResult<Self> {
        let local_db = Arc::new(LocalKvDbRedb::new(todo!()));

        let mdn_user_manager = Arc::new(MdnUserAccountManagerDefault::new(
            Arc::new(MdnUserLocalDbDefault::new(local_db)),
            Arc::new(MdnUserAccountApiClientDefault::try_new(todo!())?),
        ));

        Ok(Self {
            willow_peer: WillowPeer::new(mdn_user_manager.get_iroh_node_key().await?).await?,
            mdn_user_manager,
        })
    }
}
