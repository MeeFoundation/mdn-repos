use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct MdnIdentityContextResponse {
    pub mdn_identity_context_uid: String,
    pub willow_namespace_id: String,
    pub context_scoped_subject_id: String,
}

#[derive(Serialize, Deserialize)]
pub struct CreateMdnIdentityContextRequest {
    pub willow_namespace_id: String,
    pub context_ops_cap_token: String,
}
