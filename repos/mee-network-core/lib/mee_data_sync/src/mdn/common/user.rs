use crate::{error::MeeDataSyncResult, willow::peer::WillowPeer};
use async_trait::async_trait;
use iroh_willow::proto::keys::UserId;

#[async_trait]
pub trait MdnAgentDataNodeUserOps {
    fn willow_peer(&self) -> WillowPeer;

    async fn user_id(&self) -> MeeDataSyncResult<UserId> {
        self.willow_peer()
            .willow_user_manager
            .get_active_user_profile()
            .await
    }
}
