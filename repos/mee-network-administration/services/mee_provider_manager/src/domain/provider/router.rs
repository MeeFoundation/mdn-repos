use super::{
    account::api_methods::{
        login_provider, provider_profile, register_provider,
    },
    cloud_nodes::api_methods::{
        attach_cloud_node, is_cloud_node_linked_with_provider, list_cloud_nodes,
    },
};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};
use service_utils::mee_provider_manager::api_types::{
    IS_CLOUD_NODE_LINKED_API_PATH, PROVIDER_ACCOUNT_INFO_API_PATH,
};

pub fn providers_router() -> Router<AppCtl> {
    Router::new()
        .route("/register", post(register_provider))
        .route("/login", post(login_provider))
        .nest(
            "/cloud_nodes",
            Router::new()
                .route("/", get(list_cloud_nodes))
                .route("/", post(attach_cloud_node)),
        )
        .nest(
            "/internal",
            Router::new()
                .route(
                    &format!("/{IS_CLOUD_NODE_LINKED_API_PATH}"),
                    post(is_cloud_node_linked_with_provider),
                )
                .route(
                    &format!("/{PROVIDER_ACCOUNT_INFO_API_PATH}/:provider_meeid"),
                    get(provider_profile),
                ),
        )
}
