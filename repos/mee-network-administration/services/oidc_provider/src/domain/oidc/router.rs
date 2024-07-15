use super::provider::api_methods::{
    authorize, authorize_consent, get_client, issue_token, jwks, new_client,
    provider_metadata, refresh_token, user_login_page,
};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub const OAUTH2_AUTHORIZE_PATH: &str = "/oauth2/authorize";
pub const USER_LOGIN_PAGE_PATH: &str = "/users/login";

pub fn oidc_provider_router() -> Router<AppCtl> {
    Router::new()
        .route("/.well-known/openid-configuration", get(provider_metadata))
        .route("/jwks.json", get(jwks))
        .route(OAUTH2_AUTHORIZE_PATH, get(authorize))
        .route(OAUTH2_AUTHORIZE_PATH, post(authorize_consent))
        .route("/oauth2/token", post(issue_token))
        .route("/oauth2/refresh", post(refresh_token))
        .route("/oidc/client", post(new_client))
        .route("/oidc/client/:client_id", get(get_client))
        .route(USER_LOGIN_PAGE_PATH, get(user_login_page))
}
