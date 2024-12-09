use super::types::{
    CreateUserAccountRequest, UserAccountLoginRequest, UserAccountLoginResponse,
};
use crate::{app_ctl::AppCtl, error::MdnCentralResult};
use axum::{extract::State, Json};
use axum_extra::extract::CookieJar;

pub const COOKIE_MEE_USER_SESSION_ID: &str = "mee_user_session_id";

#[utoipa::path(
    post,
    path = "/api/v1/mdn_users/accounts/register",
    responses(
        (status = 200, description = "User account created successfully", body = UserAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn register_user(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CreateUserAccountRequest>,
) -> MdnCentralResult<Json<UserAccountLoginResponse>> {
    Ok(Json(
        app_ctl
            .mdn_user_account_controller
            .register_user(payload)
            .await?,
    ))
}

#[utoipa::path(
    post,
    path = "/api/v1/mdn_users/accounts/login",
    responses(
        (status = 200, description = "User logged in successfully", body = UserAccountLoginResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
)]
pub async fn login_user(
    jar: CookieJar,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<UserAccountLoginRequest>,
) -> MdnCentralResult<(CookieJar, Json<UserAccountLoginResponse>)> {
    let res = app_ctl
        .mdn_user_account_controller
        .login_user(payload)
        .await?;

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
