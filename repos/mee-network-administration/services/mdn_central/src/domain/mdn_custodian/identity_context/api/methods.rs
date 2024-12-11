use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    error::MdnCentralResult,
};
use axum::{extract::State, Json};
use mdn_identity_agent::mdn_cloud::mdn_identity_context::api_types::{
    CreateMdnIdentityContextRequest, MdnIdentityContextResponse,
};

pub async fn list_contexts(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<MdnIdentityContextResponse>>> {
    Ok(Json(
        app_ctl
            .mdn_identity_context_controller
            .list_contexts(logged_in_mdn_user)
            .await?,
    ))
}

pub async fn create_context(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CreateMdnIdentityContextRequest>,
) -> MdnCentralResult<Json<MdnIdentityContextResponse>> {
    Ok(Json(
        app_ctl
            .mdn_identity_context_controller
            .create_context(payload, logged_in_mdn_user)
            .await?,
    ))
}
