use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct IssueContextOpsCapTokenRequest {
    pub cap_token: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnCustodianContextOperationCapsResponse {
    pub mdn_custodian_context_operation_cap_uid: String,
    pub mdn_custodian_context_operation_cap_token: String,
    pub mdn_custodian_context_operation_cap_expires: String,
}
