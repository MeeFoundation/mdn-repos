use crate::db_models::mdn_node_hosting_platforms;
pub use mdn_identity_agent::mdn_cloud::mdn_node_hosting_platforms::api_types::*;

impl From<mdn_node_hosting_platforms::Model>
    for MdnNodeHostingPlatformResponse
{
    fn from(
        mdn_node_hosting_platforms::Model {
            mdn_node_hosting_platform_uid,
            ..
        }: mdn_node_hosting_platforms::Model,
    ) -> Self {
        Self {
            mdn_node_hosting_platform_uid,
        }
    }
}
