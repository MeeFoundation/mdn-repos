use super::{
    idm::user_auth::{MdnUserAccountManager, MdnUserAccountManagerDefault},
    mdn_node::mdn_node_manager::{MdnUserNodesManager, MdnUserNodesManagerDefault},
    storage::{local_kvdb::LocalKvDbRedb, user_local_db::MdnUserLocalDbDefault},
};
use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::{
        mdn_nodes::api_client::MdnNodesApiClientDefault,
        user_account::api_client::MdnUserAccountApiClientDefault,
    },
};
// use mee_data_sync::willow::peer::WillowPeer;
use std::sync::Arc;
use url::Url;

pub struct MdnAgentNodeConfig {
    pub local_db_file_path: String,
    pub mdn_api_base_url: Url,
}

pub struct MdnAgentNode {
    // willow_peer: WillowPeer,
    pub mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    pub mdn_user_nodes_manager: Arc<dyn MdnUserNodesManager + Send + Sync>,
}

impl MdnAgentNode {
    pub async fn try_new(
        MdnAgentNodeConfig {
            local_db_file_path,
            mdn_api_base_url,
        }: MdnAgentNodeConfig,
    ) -> MdnIdentityAgentResult<Self> {
        let local_db = Arc::new(LocalKvDbRedb::try_new(local_db_file_path).await?);

        let mdn_user_account_manager = Arc::new(MdnUserAccountManagerDefault::new(
            Arc::new(MdnUserLocalDbDefault::new(local_db)),
            Arc::new(MdnUserAccountApiClientDefault::try_new(
                mdn_api_base_url.clone(),
            )?),
        ));

        let mdn_user_nodes_manager = Arc::new(MdnUserNodesManagerDefault::new(
            Arc::new(MdnNodesApiClientDefault::try_new(mdn_api_base_url)?),
            mdn_user_account_manager.clone(),
        ));

        Ok(Self {
            // willow_peer: WillowPeer::new(mdn_user_account_manager.get_iroh_node_key().await?).await?,
            mdn_user_account_manager,
            mdn_user_nodes_manager,
        })
    }
}
