use crate::{error::MeeDataSyncResult, willow::peer::WillowPeer};
use async_trait::async_trait;
use iroh::{ticket::NodeTicket, NodeAddr};

#[async_trait]
pub trait MdnAgentDataNodeNetworkOps {
    fn willow_peer(&self) -> WillowPeer;

    async fn network_node_ticket(&self) -> MeeDataSyncResult<NodeTicket> {
        self.willow_peer()
            .willow_network_manager
            .iroh_node_ticket()
            .await
    }
    async fn network_node_addr(&self) -> MeeDataSyncResult<NodeAddr> {
        self.willow_peer()
            .willow_network_manager
            .iroh_node_addr()
            .await
    }
    fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult {
        self.willow_peer()
            .willow_network_manager
            .add_remote_peer(node_addr)
    }
}
