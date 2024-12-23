pub use mdn_identity_agent::mdn_cloud::mdn_identity_context::api_types::*;
use crate::domain::mdn_custodian::identity_context::repositories::mdn_identity_contexts::MdnIdentityContextWithCustodianName;

impl From<MdnIdentityContextWithCustodianName> for MdnIdentityContextResponse {
    fn from(
        MdnIdentityContextWithCustodianName {
            mdn_identity_context_uid,
            willow_namespace_id,
            context_scoped_subject_uid,
            custodian_name,
            context_description,
            ..
        }: MdnIdentityContextWithCustodianName,
    ) -> Self {
        Self {
            mdn_identity_context_uid,
            willow_namespace_id,
            context_scoped_subject_uid,
            custodian_name,
            context_description,
        }
    }
}
