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
            let user_id = self.willow_node.engine.create_user().await?;

            log::info!("Willow user has created: {user_id}");

            user_id
        };

        Ok(profile)
    }
}
