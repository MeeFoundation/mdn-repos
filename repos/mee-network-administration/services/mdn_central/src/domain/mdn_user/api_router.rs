use super::user_account::api::methods::{login_user, register_user};
use crate::app_ctl::AppCtl;
use axum::{routing::post, Router};

pub fn mdn_users_router() -> Router<AppCtl> {
    Router::new().nest(
        "/accounts",
        Router::new()
            .route("/register", post(register_user))
            .route("/login", post(login_user)),
    )
}
