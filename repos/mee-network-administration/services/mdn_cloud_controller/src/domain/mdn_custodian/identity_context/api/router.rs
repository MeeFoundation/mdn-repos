use super::methods::{create_context, list_contexts};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_identity_context_router() -> Router<AppCtl> {
    Router::new()
        .route("/create_context", post(create_context))
        .route("/list_contexts", get(list_contexts))
}
