use crate::error::MeeDataSyncResult;
use async_trait::async_trait;
use iroh_net::{ticket::NodeTicket, NodeAddr};

#[async_trait]
pub trait MdnAgentDataNodeNetworkOps {
    async fn network_node_ticket(&self) -> MeeDataSyncResult<NodeTicket>;
    async fn network_node_addr(&self) -> MeeDataSyncResult<NodeAddr>;
    fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult;
}
