use crate::db_models::mdn_custodian_storages;
pub use mdn_identity_agent::mdn_cloud::mdn_custodian_storage::api_types::*;

impl From<mdn_custodian_storages::Model>
    for MdnCustodianStorageResponse
{
    fn from(
        mdn_custodian_storages::Model {
            mdn_custodian_storage_uid,
            ..
        }: mdn_custodian_storages::Model,
    ) -> Self {
        Self {
            mdn_custodian_storage_uid,
        }
    }
}
