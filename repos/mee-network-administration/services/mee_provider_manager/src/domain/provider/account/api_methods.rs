use super::api_types::{
    CreateProviderAccountRequest, ProviderAccountLoginRequest,
    ProviderAccountLoginResponse,
};
use crate::{app_ctl::AppCtl, error::MeeProviderManagerResult};
use axum::{
    extract::{Path, State},
    Json,
};
use mee_http_utils::interservice::InterServiceSecuredApi;
use service_utils::mee_provider_manager::api_types::ProviderAccountInfoResponse;

#[utoipa::path(
    get,
    path = "/api/v1/providers/internal/profile/{provider_meeid}",
    params(
        ("provider_meeid" = String, Path, description = "Provider meeid")
    ),
    responses(
        (status = 200, description = "Get provider profile info", body = ProviderAccountInfoResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
    security(
      ("inter_service_api_secret" = [])
    )
  )]
pub async fn provider_profile(
    State(app_ctl): State<AppCtl>,
    Path(provider_meeid): Path<String>,
    _inter_service_secured_api: InterServiceSecuredApi,
) -> MeeProviderManagerResult<Json<ProviderAccountInfoResponse>> {
    Ok(Json(
        app_ctl
            .provider_controller
            .provider_profile(provider_meeid)
            .await?,
    ))
}

#[utoipa::path(
    post,
    path = "/api/v1/providers/register",
    responses(
        (status = 200, description = "Provider account created successfully", body = ProviderAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn register_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CreateProviderAccountRequest>,
) -> MeeProviderManagerResult<Json<ProviderAccountLoginResponse>> {
    Ok(Json(
        app_ctl
            .provider_controller
            .register_provider(payload)
            .await?,
    ))
}

#[utoipa::path(
    post,
    path = "/api/v1/providers/login",
    responses(
        (status = 200, description = "Provider logged in successfully", body = ProviderAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn login_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ProviderAccountLoginRequest>,
) -> MeeProviderManagerResult<Json<ProviderAccountLoginResponse>> {
    Ok(Json(
        app_ctl.provider_controller.login_provider(payload).await?,
    ))
}
