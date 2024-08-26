use crate::error::MeeDataSyncResult;
use async_trait::async_trait;
use iroh_willow::proto::keys::UserId;

#[async_trait]
pub trait MdnAgentDataNodeUserOps {
    async fn user_id(&self) -> MeeDataSyncResult<UserId>;
}
