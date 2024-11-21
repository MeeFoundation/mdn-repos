use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct RegisterUserDeviceRequest {
    pub user_device_did: String,
    pub user_device_jwt_proof: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub device_description: Option<String>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct UserDeviceLinkageRequest {
    pub device_description: String,
    pub device_did: String,
    pub mdn_user_device_uid: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct UserDeviceResponse {
    pub mdn_user_device_uid: String,
    pub device_description: String,
    pub is_device_linked: bool,
    pub device_did: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct ApproveUserDeviceLinkageRequest {
    pub device_approver_did: String,
    pub device_approver_jwt_proof: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}
