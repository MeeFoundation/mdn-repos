use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ProviderAccountInfoResponse {
    pub provider_meeid: String,
    pub provider_email: String,
    pub provider_name: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct IsCloudNodeLinkedRequest {
    pub provider_meeid: String,
    pub cloud_node_did: String,
}

pub const IS_CLOUD_NODE_LINKED_API_PATH: &str = "is_cloud_node_linked";
pub const PROVIDER_ACCOUNT_INFO_API_PATH: &str = "profile";
