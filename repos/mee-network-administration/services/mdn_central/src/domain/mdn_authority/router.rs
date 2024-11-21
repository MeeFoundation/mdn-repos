use super::api_methods::jwks;
use crate::app_ctl::AppCtl;
use axum::{routing::get, Router};

pub fn mdn_authority_router() -> Router<AppCtl> {
    Router::new().route("/jwks.json", get(jwks))
}
