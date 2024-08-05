use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh_willow::proto::keys::UserId;

#[derive(Clone)]
pub struct WillowUserManager {
    willow_node: WillowNode,
}

impl WillowUserManager {
    pub fn new(willow_node: WillowNode) -> Self {
        Self { willow_node }
    }

    // TODO make better user profile manager
    pub async fn get_active_user_profile(&self) -> MeeDataSyncResult<UserId> {
        let mut users = self.willow_node.engine.list_users().await?;

        let profile = if let Some(user) = users.pop() {
            user
        } else {
            self.willow_node.engine.create_user().await?
        };

        Ok(profile)
    }
}
