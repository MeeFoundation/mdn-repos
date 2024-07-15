use crate::app_ctl::AppCtl;
use axum::Router;

pub fn persona_model_router() -> Router<AppCtl> {
    Router::new()
}
