use crate::app_ctl::AppCtl;
use axum::Router;

pub fn mdn_capabilities_router() -> Router<AppCtl> {
    Router::new()
}
