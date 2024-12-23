use super::types::MdnCustodianContextOperationCapsResponse;
use crate::{
    app_ctl::AppCtl,
    domain::{
        mdn_custodian::capabilities::api::types::IssueContextOpsCapTokenRequest,
        mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    },
    error::MdnCloudControllerResult,
};
use axum::{extract::State, Json};

pub async fn issue_context_ops_cap(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(req): Json<IssueContextOpsCapTokenRequest>,
) -> MdnCloudControllerResult {
    app_ctl
        .mdn_capabilities_controller
        .issue_context_ops_cap(req, logged_in_mdn_user)
        .await
}

pub async fn context_ops_caps(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCloudControllerResult<Json<Vec<MdnCustodianContextOperationCapsResponse>>> {
    app_ctl
        .mdn_capabilities_controller
        .context_ops_caps(logged_in_mdn_user)
        .await
        .map(Json)
}
