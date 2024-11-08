use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserDeviceLinkageRequest {
    pub device_description: String,
    pub device_did: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ApproveUserDeviceLinkageRequest {
    pub device_did_to_approve: String,
    pub device_did_approver_signature: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct LinkUserDeviceRequest {
    pub user_device_did: String,
    pub user_device_did_signature: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct RegisterUserDeviceRequest {
    pub user_device_did: String,
    pub user_device_did_signature: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
}
