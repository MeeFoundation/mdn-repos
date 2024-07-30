use super::api_types::CreateSdaProfileRequest;
use crate::{app_ctl::AppCtl, error::ApsServiceResult};
use axum::{extract::State, Json};

#[utoipa::path(
  post,
  path = "/api/v1/ad_profiles",
  responses(
      (status = 200, description = "Update ad profile for the provided user", body = ()),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn add_sda_profile(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CreateSdaProfileRequest>,
) -> ApsServiceResult<()> {
    let res = app_ctl
        .add_profile_controller
        .update_sda_profile(payload)
        .await?;

    Ok(res)
}
