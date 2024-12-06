use super::api::methods::{list_all_custodian_storages, register_custodian_storage};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_custodian_storages_router() -> Router<AppCtl> {
    Router::new()
        .route(
            "/register_custodian_storage",
            post(register_custodian_storage),
        )
        .route("/list_all_custodian_storages", get(list_all_custodian_storages))
}
