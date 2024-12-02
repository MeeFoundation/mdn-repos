use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct RegisterMdnNodeRequest {
    pub mdn_node_willow_peer_id: String,
    pub mdn_node_iroh_node_id: String,
    pub mdn_node_did: String,
    pub mdn_node_subject_id: String,
    pub mdn_node_did_proof: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnNodeResponse {
    pub mdn_node_uid: String,
}
