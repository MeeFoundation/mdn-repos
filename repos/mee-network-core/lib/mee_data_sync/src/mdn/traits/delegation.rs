use crate::{
    error::MeeDataSyncResult, mdn::willow_impl::delegation::ImportCapabilitiesFromRemotePeer,
};
use async_trait::async_trait;
use iroh_willow::{
    interest::CapabilityPack,
    proto::{data_model::NamespaceId, keys::UserId},
    session::intents::IntentHandle,
};
use serde::{Deserialize, Serialize};

#[derive(Debug)]
pub struct MdnDataDelegationCapabilityPack {
    pub data_source_namespace: MdnDataDelegationCapabilityPackObject,
    pub revocation_list_receiver_namespace: MdnDataDelegationCapabilityPackObject,
    pub revocation_list_sender_namespace: MdnDataDelegationCapabilityPackObject,
}

#[derive(Debug)]
pub struct MdnDataDelegationCapabilityPackObject {
    pub cap_pack: Vec<CapabilityPack>,
    pub cap_issuer: UserId,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnDataRevocationListResponse {
    pub record: MdnDataRevocationListRecord,
    pub signal_revocation_ns: NamespaceId,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnDataRevocationListRecord {
    pub shared_data_path: String,
    pub data_owner: UserId,
    pub data_owner_ns: NamespaceId,
    pub revocation_id: String,
    pub revocation_receiver: UserId,
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
    ) -> MeeDataSyncResult<MdnDataDelegationCapabilityPack>;
    async fn revoke_shared_access(
        &self,
        data_subset_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult;
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListResponse>>;
    async fn is_revocation_list_empty(&self) -> MeeDataSyncResult<bool>;
}
