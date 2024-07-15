use crate::db_models::provider_cloud_nodes;
use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CloudNodeAttachmentRequest {
    pub cloud_node_discovery_url: String,
    pub cloud_node_did: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CloudNodeAttachmentResponse {
    pub cloud_node_uid: String,
    pub cloud_node_discovery_url: String,
    pub cloud_node_did: String,
}

impl From<provider_cloud_nodes::Model> for CloudNodeAttachmentResponse {
    fn from(
        provider_cloud_nodes::Model {
            cloud_node_uid,
            cloud_node_discovery_url,
            cloud_node_did,
            ..
        }: provider_cloud_nodes::Model,
    ) -> Self {
        Self {
            cloud_node_uid,
            cloud_node_discovery_url,
            cloud_node_did,
        }
    }
}
