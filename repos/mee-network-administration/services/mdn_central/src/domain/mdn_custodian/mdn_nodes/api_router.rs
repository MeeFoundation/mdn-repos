use super::api::methods::{list_all_node_hosting_platforms, register_node_hosting_platform};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_nodes_router() -> Router<AppCtl> {
    Router::new()
        .route(
            "/register_node_hosting_platform",
            post(register_node_hosting_platform),
        )
        .route("/list_all_node_hosting_platforms", get(list_all_node_hosting_platforms))
}
