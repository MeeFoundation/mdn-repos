use super::api_types::{
    ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest,
    LinkUserDeviceRequest, UserDeviceLinkageRequest,
};
use crate::{app_ctl::AppCtl, error::MdnCentralResult};
use axum::{extract::State, Json};

#[utoipa::path(
    post,
    path = "/api/v1/mdn_users/devices/register",
    responses(
        (status = 200, description = "User device has been successfully registered", body = ()),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn register_user_device(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<RegisterUserDeviceRequest>,
) -> MdnCentralResult<Json<()>> {
    todo!()
}

#[utoipa::path(
    post,
    path = "/api/v1/mdn_users/devices/link",
    responses(
        (status = 200, description = "User device has been successfully linked", body = ()),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn link_user_device(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<LinkUserDeviceRequest>,
) -> MdnCentralResult<Json<()>> {
    todo!()
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
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<UserDeviceLinkageRequest>>> {
    todo!()
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
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ApproveUserDeviceLinkageRequest>,
) -> MdnCentralResult<Json<()>> {
    todo!()
}
