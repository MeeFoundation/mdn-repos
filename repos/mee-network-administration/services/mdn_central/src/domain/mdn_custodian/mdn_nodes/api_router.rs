use super::api::methods::{list_all, register_node};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_nodes_router() -> Router<AppCtl> {
    Router::new()
        .route("/register", post(register_node))
        .route("/list_all", get(list_all))
}
