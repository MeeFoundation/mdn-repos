use super::api_types::{
    OidcProviderRegistrarCreateRequest, OidcProviderRegistrarCreateResponse,
};
use crate::{
    app_ctl::AppCtl,
    domain::oidc::controller::{ConsentStatus, UserOauthLoginPageParams},
    error::MeeOidcProviderResult,
};
use axum::{
    extract::{Path, Query, State},
    http::Uri,
    response::{IntoResponse, Response},
    Json,
};
use axum_extra::extract::CookieJar;
use identity_jose::jwk::JwkSet;
use openid::Config;
use oxide_auth_axum::{OAuthRequest, OAuthResponse};
use service_utils::mee_provider_manager::{
    api_types::ProviderAccountInfoResponse, auth::LoggedInProvider,
};

/// OIDC provider metadata
# [utoipa::path(
    get,
    path = "/.well-known/openid-configuration",
    responses(
        (status = 200, description = "Provider metadata", body = ConfigTO),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn provider_metadata(
    State(app_ctl): State<AppCtl>,
) -> MeeOidcProviderResult<Json<Config>> {
    Ok(Json(app_ctl.oidc_controller.provider_metadata().await?))
}

/// OIDC provider JWK set
# [utoipa::path(
    get,
    path = "/jwks.json",
    responses(
        (status = 200, description = "JWK set", body = JwkSetTO),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn jwks(
    State(app_ctl): State<AppCtl>,
) -> MeeOidcProviderResult<Json<JwkSet>> {
    Ok(Json(app_ctl.oidc_controller.jwks().await?))
}

/// OYT provider registration as OIDC client
# [utoipa::path(
    post,
    path = "/oidc/client",
    responses(
        (status = 200, description = "New client created", body = OidcProviderRegistrarCreateResponse),
        (status = 500, description = "Something went wrong", body = String),
    ),
    security(
        ("token_biscuit" = [])
    )
)]
pub async fn new_client(
    State(app_ctl): State<AppCtl>,
    current_provider: LoggedInProvider,
    Json(payload): Json<OidcProviderRegistrarCreateRequest>,
) -> MeeOidcProviderResult<Json<OidcProviderRegistrarCreateResponse>> {
    Ok(Json(
        app_ctl
            .oidc_controller
            .new_client(current_provider, payload)
            .await?,
    ))
}

/// Get OIDC client info
# [utoipa::path(
    get,
    path = "/oidc/client/{client_id}",
    params(
        ("client_id", description = "OIDC Client ID"),
    ),
    responses(
        (status = 200, description = "Client info", body = ProviderAccountInfoResponse),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn get_client(
    State(app_ctl): State<AppCtl>,
    _current_provider: LoggedInProvider,
    Path(client_id): Path<String>,
) -> MeeOidcProviderResult<Json<ProviderAccountInfoResponse>> {
    Ok(Json(app_ctl.oidc_controller.get_client(client_id).await?))
}

/// Authorize user consent
#[utoipa::path(
    post,
    path = "/oauth2/authorize",
    responses(
        (status = 200, description = "Authorization page", body = OAuthResponseTO),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn authorize_consent(
    State(app_ctl): State<AppCtl>,
    consent: Option<Query<ConsentStatus>>,
    jar: CookieJar,
    uri: Uri,
    oauth: OAuthRequest,
) -> MeeOidcProviderResult<Response> {
    app_ctl
        .oidc_controller
        .authorize_consent(consent.map(|c| c.0), jar, uri, oauth)
        .await
}

/// Refresh token
#[utoipa::path(
    post,
    path = "/oauth2/refresh",
    responses(
        (status = 200, description = "Token refreshed", body = OAuthResponseTO),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn refresh_token(
    State(app_ctl): State<AppCtl>,
    oauth: OAuthRequest,
) -> MeeOidcProviderResult<OAuthResponse> {
    app_ctl.oidc_controller.refresh_token(oauth).await
}

/// Issue token
#[utoipa::path(
    post,
    path = "/oauth2/token",
    responses(
        (status = 200, description = "Token issued", body = OAuthResponseTO),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn issue_token(
    State(app_ctl): State<AppCtl>,
    oauth: OAuthRequest,
) -> MeeOidcProviderResult<OAuthResponse> {
    app_ctl.oidc_controller.issue_token(oauth).await
}

/// User login page
#[utoipa::path(
    get,
    path = "/users/login",
    responses(
        (status = 200, description = "Login page", body = String),
        (status = 404, description = "Client not found", body = String),
    )
)]
pub async fn user_login_page(
    State(app_ctl): State<AppCtl>,
    login_params: Option<Query<UserOauthLoginPageParams>>,
) -> MeeOidcProviderResult<impl IntoResponse> {
    app_ctl
        .oidc_controller
        .user_login_page(login_params.map(|p| p.0))
        .await
}

/// Authorize user
# [utoipa::path(
    get,
    path = "/oauth2/authorize",
    responses(
        (status = 200, description = "Authorization page", body = OAuthResponseTO),
        (status = 500, description = "Something went wrong", body = String),
    ))
]
pub async fn authorize(
    State(app_ctl): State<AppCtl>,
    uri: Uri,
    jar: CookieJar,
    oauth: OAuthRequest,
) -> MeeOidcProviderResult<Response> {
    app_ctl.oidc_controller.authorize(uri, jar, oauth).await
}
