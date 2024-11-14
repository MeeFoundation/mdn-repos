use serde::{Deserialize, Serialize};
use utoipa::ToSchema;
use crate::domain::mdn_user::user_devices::repositories::device_requests_for_linkage::DeviceLinkageRequestWithDevice;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserDeviceLinkageRequest {
    pub device_description: String,
    pub device_did: String,
    pub mdn_user_device_uid: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}

impl From<DeviceLinkageRequestWithDevice> for UserDeviceLinkageRequest {
    fn from((req, dev): DeviceLinkageRequestWithDevice) -> Self {
        Self {
            device_description: dev.device_description,
            device_did: dev.device_did,
            mdn_user_device_uid: dev.mdn_user_device_uid,
            mdn_user_device_request_for_linkage_uid: req
                .mdn_user_device_request_for_linkage_uid,
        }
    }
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ApproveUserDeviceLinkageRequest {
    pub device_approver_did: String,
    pub device_approver_jwt_proof: String,
    pub mdn_user_device_request_for_linkage_uid: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct RegisterUserDeviceRequest {
    pub user_device_did: String,
    pub user_device_jwt_proof: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub device_description: Option<String>,
}
