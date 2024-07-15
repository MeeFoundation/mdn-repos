use super::api_types::{
    CreateUserAccountRequest, UserAccountLoginRequest, UserAccountLoginResponse,
};
use crate::{app_ctl::AppCtl, error::MeeUserManagerResult};
use axum::{extract::State, Json};
use axum_extra::extract::CookieJar;
use mee_http_utils::interservice::InterServiceSecuredApi;
use service_utils::mee_user_manager::{
    api_types::{AuthorizeUserRequest, AuthorizeUserResponse},
    COOKIE_MEE_USER_SESSION_ID,
};

#[utoipa::path(
    get,
    path = "/api/v1/users/internal/authorize",
    responses(
        (status = 200, description = "Get provider profile info", body = AuthorizeUserResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
    security(
      ("inter_service_api_secret" = [])
    )
  )]
pub async fn authorize_user(
    State(app_ctl): State<AppCtl>,
    _inter_service_secured_api: InterServiceSecuredApi,
    Json(payload): Json<AuthorizeUserRequest>,
) -> MeeUserManagerResult<Json<AuthorizeUserResponse>> {
    Ok(Json(
        app_ctl
            .user_controller
            .authorize_user_login_request(payload)
            .await?,
    ))
}

#[utoipa::path(
    post,
    path = "/api/v1/users/register",
    responses(
        (status = 200, description = "User account created successfully", body = UserAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn register_user(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CreateUserAccountRequest>,
) -> MeeUserManagerResult<Json<UserAccountLoginResponse>> {
    Ok(Json(app_ctl.user_controller.register_user(payload).await?))
}

#[utoipa::path(
    post,
    path = "/api/v1/users/login",
    responses(
        (status = 200, description = "User logged in successfully", body = UserAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn login_user(
    jar: CookieJar,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<UserAccountLoginRequest>,
) -> MeeUserManagerResult<(CookieJar, Json<UserAccountLoginResponse>)> {
    let res = app_ctl.user_controller.login_user(payload).await?;

    // TODO: check the cookie security
    // The cookie is required by OIDC provider
    // Any other user endpoints protected by bearer token
    let cookie = axum_extra::extract::cookie::Cookie::build((
        COOKIE_MEE_USER_SESSION_ID,
        res.auth_token.clone(),
    ))
    .http_only(true)
    .path("/")
    .expires(time::OffsetDateTime::now_utc() + time::Duration::days(14))
    .build();

    let jar = jar.add(cookie);

    Ok((jar, Json(res)))
}
