use super::{
    user_account::api::account::methods::{login_user, register_user},
    user_devices::api::devices::methods::{
        approve_user_device_linkage, list_user_device_linkage_requests,
        register_user_device,
    },
};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_users_router() -> Router<AppCtl> {
    Router::new()
        .nest(
            "/accounts",
            Router::new()
                .route("/register", post(register_user))
                .route("/login", post(login_user)),
        )
        .nest(
            "/devices",
            Router::new()
                .route("/register", post(register_user_device))
                .route(
                    "/linkage_requests",
                    get(list_user_device_linkage_requests),
                )
                .route("/approve_linkage", post(approve_user_device_linkage)),
        )
}
