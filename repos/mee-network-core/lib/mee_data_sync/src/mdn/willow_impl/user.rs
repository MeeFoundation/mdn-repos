use super::node::MdnAgentDataNodeWillowImpl;
use crate::{error::MeeDataSyncResult, mdn::node::MdnAgentDataNodeUser};
use async_trait::async_trait;
use iroh_willow::proto::keys::UserId;

#[async_trait]
impl MdnAgentDataNodeUser for MdnAgentDataNodeWillowImpl {
    async fn user_id(&self) -> MeeDataSyncResult<UserId> {
        self.willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await
    }
}
