use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh_net::{ticket::NodeTicket, NodeAddr};

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
    pub async fn iroh_node_ticket(&self) -> MeeDataSyncResult<NodeTicket> {
        let node_ticket = NodeTicket::new(self.willow_node.endpoint.node_addr().await?)?;

        Ok(node_ticket)
    }
    pub async fn iroh_node_addr(&self) -> MeeDataSyncResult<NodeAddr> {
        let node_addr = self.willow_node.endpoint.node_addr().await?;

        Ok(node_addr)
    }
}
