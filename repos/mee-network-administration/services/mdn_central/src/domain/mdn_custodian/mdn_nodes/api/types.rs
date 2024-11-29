use crate::db_models::mdn_nodes;
pub use mdn_identity_agent::mdn_cloud::mdn_nodes::api_types::*;

impl From<mdn_nodes::Model> for MdnNodeResponse {
    fn from(mdn_nodes::Model { mdn_node_uid, .. }: mdn_nodes::Model) -> Self {
        Self { mdn_node_uid }
    }
}
