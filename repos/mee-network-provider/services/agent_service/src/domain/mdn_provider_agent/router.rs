use super::mdn_node::api_methods::{
    delegate_read_access_to_provider, get_persona_attributes,
    import_capabilities_from_provider,
    import_search_schemas_ns_from_virtual_agent, iroh_ticket,
    set_persona_attributes, willow_id,
};
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post},
    Router,
};

pub fn mdn_provider_agent_router() -> Router<AppCtl> {
    Router::new()
        .nest(
            "/persona",
            Router::new()
                .route("/set_attributes", post(set_persona_attributes))
                .route("/get_attributes", post(get_persona_attributes)),
        )
        .nest(
            "/node",
            Router::new()
                .route("/iroh_ticket", get(iroh_ticket))
                .route("/willow_id", get(willow_id)),
        )
        .nest(
            "/capabilities",
            Router::new()
                .route(
                    "/delegate_read_access_to_provider",
                    post(delegate_read_access_to_provider),
                )
                .route(
                    "/import_capabilities_from_provider",
                    post(import_capabilities_from_provider),
                )
                .route(
                    "/import_search_schemas_ns_from_virtual_agent",
                    post(import_search_schemas_ns_from_virtual_agent),
                ),
        )
}
