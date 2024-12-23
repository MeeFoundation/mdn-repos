use super::mdn_node::{api_methods::*, api_types::*};
use mee_data_sync::mdn_iiw38::{
    common::store::ReadDataRecord,
    provider_agent::delegation::manager::ImportCapabilitiesFromVirtualAgent,
};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
    paths(
        share_search_schemas_ns_with_provider,
        iroh_ticket,
        search_schemas,
    ),
    components(
        schemas(
            ShareSearchSchemasNsWithProviderRequest,
            ImportCapabilitiesFromVirtualAgent,
            ReadDataRecord,
        ),
    ),
    tags(
        (name = "User related functionality", description = "REST API"),
    )
)]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_virtual_agent/openapi.json";
