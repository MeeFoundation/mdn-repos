use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh_net::NodeAddr;

#[derive(Clone)]
pub struct WillowNetworkManager {
    willow_node: WillowNode,
}

impl WillowNetworkManager {
    pub fn new(willow_node: WillowNode) -> Self {
        Self { willow_node }
    }
    pub fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult {
        self.willow_node.endpoint.add_node_addr(node_addr)?;

        Ok(())
    }
}
