use super::mdn_node::{api_methods::*, api_types::*};
use mee_data_sync::mdn::provider_agent::delegation::manager::{
    ImportCapabilitiesFromProvider, ImportCapabilitiesFromVirtualAgent,
};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
    paths(
        iroh_ticket,
        willow_id,
        delegate_read_access_to_provider,
        import_capabilities_from_provider,
        import_search_schemas_ns_from_virtual_agent,
        get_persona_attributes,
        set_persona_attributes,
    ),
    components(
        schemas(
            DelegateReadAccessToProviderRequest,
            ImportCapabilitiesFromProvider,
            SetPersonaAttributesRequest,
            GetPersonaAttributesResponse,
            GetPersonaAttributesRequest,
            ImportCapabilitiesFromVirtualAgent,
        ),
    ),
    tags(
        (name = "MDN provider agent API", description = "REST API"),
    )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_provider_agent/openapi.json";
