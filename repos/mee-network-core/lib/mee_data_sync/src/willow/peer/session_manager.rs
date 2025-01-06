use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh::NodeId;
use iroh_willow::session::{intents::IntentHandle, SessionInit};

#[derive(Clone)]
pub struct WillowSessionManager {
    willow_node: WillowNode,
}

impl WillowSessionManager {
    pub fn new(willow_node: WillowNode) -> Self {
        Self { willow_node }
    }
    pub async fn sync_with_peer(
        &self,
        peer: NodeId,
        init: SessionInit,
    ) -> MeeDataSyncResult<IntentHandle> {
        Ok(self.willow_node.engine.sync_with_peer(peer, init).await?)
    }
}
