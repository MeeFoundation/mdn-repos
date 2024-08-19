use crate::{
    error::MeeDataSyncResult, willow::peer::delegation_manager::ImportCapabilitiesFromRemotePeer,
};
use async_trait::async_trait;
use iroh_net::{ticket::NodeTicket, NodeAddr};
use iroh_willow::{
    interest::CapabilityPack,
    proto::keys::{NamespaceId, UserId},
    session::intents::IntentHandle,
};
use serde::{Deserialize, Serialize};

#[async_trait]
pub trait MdnAgentDataNodeUser {
    async fn user_id(&self) -> MeeDataSyncResult<UserId>;
}

#[derive(Debug)]
pub enum MdnDataDelegationCapabilityRole {
    MdnDataSharing,
    RevocationListReceiver,
    RevocationListSender,
}

#[derive(Debug)]
pub struct MdnDataDelegationCapabilityPack {
    pub cap_pack: CapabilityPack,
    pub cap_role: MdnDataDelegationCapabilityRole,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnDataRevocationListRecord {
    pub shared_data_path: String,
    pub data_owner: UserId,
    pub data_owner_ns: NamespaceId,
}

impl MdnDataRevocationListRecord {
    pub fn encode(&self) -> MeeDataSyncResult<Vec<u8>> {
        Ok(serde_json::to_vec(self)?)
    }
    pub fn decode(bytes: &[u8]) -> MeeDataSyncResult<Self> {
        Ok(serde_json::from_slice(bytes)?)
    }
}

// TODO make abstract over willow specific details
#[async_trait]
pub trait MdnAgentDataNodeDelegation {
    async fn import_capabilities_from_remote_peer(
        &self,
        caps: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle>;
    async fn delegate_read_access(
        &self,
        data_subset_path: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<Vec<MdnDataDelegationCapabilityPack>>;
    async fn revoke_shared_access(
        &self,
        data_subset_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult;
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListRecord>>;
}

#[async_trait]
pub trait MdnAgentDataNodeNetwork {
    async fn network_node_ticket(&self) -> MeeDataSyncResult<NodeTicket>;
    async fn network_node_addr(&self) -> MeeDataSyncResult<NodeAddr>;
    fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult;
}
