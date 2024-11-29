use super::types::RegisterMdnNodeRequest;
use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    error::MdnCentralResult,
};
use axum::extract::{Json, State};
use mdn_identity_agent::mdn_cloud::mdn_nodes::api_types::MdnNodeResponse;

pub async fn list_all(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<MdnNodeResponse>>> {
    Ok(Json(
        app_ctl
            .mdn_nodes_controller
            .list_all(logged_in_mdn_user.mdn_custodian_uid())
            .await?,
    ))
}

pub async fn register_node(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<RegisterMdnNodeRequest>,
) -> MdnCentralResult {
    Ok(app_ctl
        .mdn_nodes_controller
        .add_node(payload, logged_in_mdn_user.mdn_custodian_uid())
        .await?)
}
