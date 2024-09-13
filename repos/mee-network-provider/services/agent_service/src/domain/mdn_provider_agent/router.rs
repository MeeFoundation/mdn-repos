use super::mdn_node::api_methods::{
    del_persona_attributes, delegate_read_access_to_provider, delegated_caps,
    get_persona_attributes, import_capabilities_from_provider,
    import_search_schemas_ns_from_virtual_agent, iroh_ticket,
    revoke_shared_access_from_provider, set_persona_attributes,
    virtual_agent_search_schemas, willow_id,
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
                .route("/get_attributes", post(get_persona_attributes))
                .route("/del_attributes", post(del_persona_attributes))
                .route(
                    "/virtual_agent_search_schemas",
                    post(virtual_agent_search_schemas),
                ),
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
                )
                .route("/delegated_caps", post(delegated_caps))
                .route(
                    "/revoke_shared_access_from_provider",
                    post(revoke_shared_access_from_provider),
                ),
        )
}
