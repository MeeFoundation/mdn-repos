use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct RegisterUserDeviceRequest {
    pub user_device_did: String,
    pub user_device_jwt_proof: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub device_description: Option<String>,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserDeviceLinkageRequest {
    pub device_description: String,
    pub device_did: String,
    pub mdn_user_device_uid: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ApproveUserDeviceLinkageRequest {
    pub device_approver_did: String,
    pub device_approver_jwt_proof: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}
