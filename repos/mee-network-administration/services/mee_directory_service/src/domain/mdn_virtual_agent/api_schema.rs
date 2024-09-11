use super::mdn_node::{api_methods::*, api_types::*};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
    paths(
        share_search_schemas_ns_with_provider,
        iroh_ticket,     
    ),
    components(
        schemas(
            ShareSearchSchemasNsWithProviderRequest
        ),
    ),
    tags(
        (name = "User related functionality", description = "REST API"),
    )
)]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_virtual_agent/openapi.json";
