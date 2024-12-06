use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct RegisterMdnCustodianStorageRequest {
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub mdn_custodian_storage_did: String,
    pub mdn_custodian_storage_did_proof: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnCustodianStorageResponse {
    pub mdn_custodian_storage_uid: String,
}
