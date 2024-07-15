use super::account::api_methods::{authorize_user, login_user, register_user};
use crate::app_ctl::AppCtl;
use axum::{routing::post, Router};

pub fn users_router() -> Router<AppCtl> {
    Router::new()
        .route("/register", post(register_user))
        .route("/login", post(login_user))
        .nest(
            "/internal",
            Router::new().route("/authorize", post(authorize_user)),
        )
}
