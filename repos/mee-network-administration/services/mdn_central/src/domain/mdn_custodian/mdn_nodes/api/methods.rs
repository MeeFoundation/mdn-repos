use super::types::RegisterMdnNodeHostingPlatformRequest;
use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    error::MdnCentralResult,
};
use axum::extract::{Json, State};
use mdn_identity_agent::mdn_cloud::mdn_node_hosting_platforms::api_types::MdnNodeHostingPlatformResponse;

pub async fn list_all_node_hosting_platforms(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<MdnNodeHostingPlatformResponse>>> {
    Ok(Json(
        app_ctl
            .mdn_nodes_controller
            .list_all_node_hosting_platforms(logged_in_mdn_user.mdn_custodian_uid())
            .await?,
    ))
}

pub async fn register_node_hosting_platform(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<RegisterMdnNodeHostingPlatformRequest>,
) -> MdnCentralResult {
    Ok(app_ctl
        .mdn_nodes_controller
        .register_node_hosting_platform(payload, logged_in_mdn_user)
        .await?)
}
