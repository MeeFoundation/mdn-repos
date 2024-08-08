use crate::{
    error::MeeDataSyncResult, willow::peer::delegation_manager::ImportCapabilitiesFromRemotePeer,
};
use async_trait::async_trait;
use iroh_net::{ticket::NodeTicket, NodeAddr};
use iroh_willow::{
    auth::{CapabilityPack, DelegateTo},
    proto::{keys::UserId, meadowcap::AccessMode, willow::Path},
    session::intents::IntentHandle,
};

#[derive(Debug)]
pub struct GetUserDataRecord {
    pub key: Path,
    pub value: Vec<u8>,
}

#[async_trait]
pub trait MdnAgentDataNodeStore {
    /// Path/key to user's data root in KV-like storage
    fn user_data_root_path(&self, user_id: &str) -> String;

    async fn get_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
    ) -> MeeDataSyncResult<Vec<GetUserDataRecord>>;

    async fn set_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
        value: Vec<u8>,
    ) -> MeeDataSyncResult;
}

#[async_trait]
pub trait MdnAgentDataNodeUser {
    async fn user_id(&self) -> MeeDataSyncResult<UserId>;
}

#[async_trait]
pub trait MdnAgentDataNodeDelegation {
    async fn import_capabilities_from_remote_peer(
        &self,
        caps: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle>;
    async fn delegate_capabilities(
        &self,
        access_mode: AccessMode,
        to: DelegateTo,
    ) -> MeeDataSyncResult<Vec<CapabilityPack>>;
}

#[async_trait]
pub trait MdnAgentDataNodeNetwork {
    async fn network_node_ticket(&self) -> MeeDataSyncResult<NodeTicket>;
    async fn network_node_addr(&self) -> MeeDataSyncResult<NodeAddr>;
    fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult;
}
