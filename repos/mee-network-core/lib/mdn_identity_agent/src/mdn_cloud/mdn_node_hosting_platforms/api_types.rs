use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct RegisterMdnNodeHostingPlatformRequest {
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub node_hosting_platform_did: String,
    pub node_hosting_platform_did_proof: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnNodeHostingPlatformResponse {
    pub mdn_node_hosting_platform_uid: String,
}
