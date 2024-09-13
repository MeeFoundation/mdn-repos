use super::mdn_node::{api_methods::*, api_types::*};
use mee_data_sync::mdn::{
    common::store::ReadDataRecord,
    provider_agent::delegation::manager::{
        ImportCapabilitiesFromProvider, ImportCapabilitiesFromVirtualAgent,
    },
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
        del_persona_attributes,
        virtual_agent_search_schemas,
        revoke_shared_access_from_provider,
        delegated_caps,
    ),
    components(
        schemas(
            DelegateReadAccessToProviderRequest,
            ImportCapabilitiesFromProvider,
            SetPersonaAttributesRequest,
            DelPersonaAttributesRequest,
            GetPersonaAttributesResponse,
            GetPersonaAttributesRequest,
            ImportCapabilitiesFromVirtualAgent,
            ReadDataRecord,
            DelegatedCap,
        ),
    ),
    tags(
        (name = "MDN provider agent API", description = "REST API"),
    )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_provider_agent/openapi.json";
