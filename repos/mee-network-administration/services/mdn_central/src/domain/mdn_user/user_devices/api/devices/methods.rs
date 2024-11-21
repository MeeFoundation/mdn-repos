use super::types::{
    ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest,
    UserDeviceLinkageRequest,
};
use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::api::account::middlewares::LoggedInMdnUser,
    error::MdnCentralResult,
};
use axum::{extract::State, Json};
use mdn_identity_agent::mdn_cloud::user_devices::api_types::UserDeviceResponse;

#[utoipa::path(
    get,
    path = "/api/v1/mdn_users/devices/list_all",
    responses(
        (status = 200, description = "Returns all registered user devices", body = ()),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn list_user_devices(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<UserDeviceResponse>>> {
    Ok(Json(
        app_ctl
            .mdn_user_devices_controller
            .list_user_devices(logged_in_mdn_user)
            .await?,
    ))
}

#[utoipa::path(
    post,
    path = "/api/v1/mdn_users/devices/register",
    responses(
        (status = 200, description = "User device has been successfully registered", body = ()),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn register_user_device(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<RegisterUserDeviceRequest>,
) -> MdnCentralResult {
    Ok(app_ctl
        .mdn_user_devices_controller
        .register_user_device(payload, logged_in_mdn_user)
        .await?)
}

#[utoipa::path(
    get,
    path = "/api/v1/mdn_users/devices/linkage_requests",
    responses(
        (status = 200, description = "Returns device linkage requests", body = Vec<UserDeviceLinkageRequest>),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn list_user_device_linkage_requests(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<UserDeviceLinkageRequest>>> {
    Ok(Json(
        app_ctl
            .mdn_user_devices_controller
            .list_user_device_linkage_requests(logged_in_mdn_user)
            .await?,
    ))
}

#[utoipa::path(
  post,
  path = "/api/v1/mdn_users/devices/approve_linkage_request",
  responses(
      (status = 200, description = "User device linkage has been successfully approved", body = ()),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn approve_user_device_linkage(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ApproveUserDeviceLinkageRequest>,
) -> MdnCentralResult<()> {
    Ok(app_ctl
        .mdn_user_devices_controller
        .approve_user_device_linkage(logged_in_mdn_user, payload)
        .await?)
}
