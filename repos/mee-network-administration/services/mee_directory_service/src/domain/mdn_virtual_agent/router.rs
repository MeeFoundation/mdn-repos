use super::mdn_node::api_methods::{
    iroh_ticket, share_search_schemas_ns_with_provider,
};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_virtual_agent_router() -> Router<AppCtl> {
    Router::new()
        .nest(
            "/node",
            Router::new().route("/iroh_ticket", get(iroh_ticket)), // .route("/willow_id", get(willow_id)),
        )
        .nest(
            "/capabilities",
            Router::new().route(
                "/share_search_schemas_ns_with_provider",
                post(share_search_schemas_ns_with_provider),
            ),
        )
}
