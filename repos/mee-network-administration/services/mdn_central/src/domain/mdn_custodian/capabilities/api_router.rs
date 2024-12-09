use super::api::methods::{issue_context_ops_cap, context_ops_caps};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_capabilities_router() -> Router<AppCtl> {
    Router::new()
        // TODO add provider initiated user auth flow with restricted ctx ops cap issuance
        .route("/issue_context_ops_cap", post(issue_context_ops_cap))
        .route("/context_ops_caps", get(context_ops_caps))
}
