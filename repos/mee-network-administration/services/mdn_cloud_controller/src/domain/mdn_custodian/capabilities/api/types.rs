use crate::db_models::mdn_custodian_context_operation_caps;
pub use mdn_identity_agent::mdn_cloud::mdn_capabilities::api_types::*;

impl From<mdn_custodian_context_operation_caps::Model>
    for MdnCustodianContextOperationCapsResponse
{
    fn from(
        mdn_custodian_context_operation_caps::Model {
            mdn_custodian_context_operation_cap_uid,
            mdn_custodian_context_operation_cap_token,
            mdn_custodian_context_operation_cap_expires,
            ..
        }: mdn_custodian_context_operation_caps::Model,
    ) -> Self {
        Self {
            mdn_custodian_context_operation_cap_uid,
            mdn_custodian_context_operation_cap_token,
            mdn_custodian_context_operation_cap_expires:
                mdn_custodian_context_operation_cap_expires.to_rfc3339(),
        }
    }
}
