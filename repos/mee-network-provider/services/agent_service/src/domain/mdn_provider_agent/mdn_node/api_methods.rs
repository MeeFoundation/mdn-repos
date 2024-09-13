use super::api_types::{
    DelPersonaAttributesRequest, DelegateReadAccessToProviderRequest,
    DelegatedCap, GetPersonaAttributesRequest, GetPersonaAttributesResponse,
    SetPersonaAttributesRequest,
};
use crate::{app_ctl::AppCtl, error::AgentServiceResult};
use axum::{extract::State, Json};
use mee_data_sync::mdn::{
    common::store::ReadDataRecord,
    provider_agent::delegation::manager::{
        ImportCapabilitiesFromProvider, ImportCapabilitiesFromVirtualAgent,
    },
};

#[utoipa::path(
  get,
  path = "/api/v1/provider_agent/node/iroh_ticket",
  responses(
      (status = 200, description = "Returns iroh node network (discovery) ticket", body = String),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn iroh_ticket(
    State(app_ctl): State<AppCtl>,
) -> AgentServiceResult<String> {
    let ticket = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .iroh_net_ticket()
        .await?;

    Ok(ticket)
}

#[utoipa::path(
  get,
  path = "/api/v1/provider_agent/node/willow_id",
  responses(
      (status = 200, description = "Returns Willow UserId (public key)", body = String),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn willow_id(
    State(app_ctl): State<AppCtl>,
) -> AgentServiceResult<String> {
    let ticket = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .willow_id()
        .await?;

    Ok(ticket)
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/capabilities/delegate_read_access_to_provider",
  request_body(content = DelegateReadAccessToProviderRequest, example = json!({"data_path": "alice/address/0/city", "provider_id": "id"})),
  responses(
      (status = 200, description = "Returns capabilities to read subset of user's data", body = ImportCapabilitiesFromProvider),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn delegate_read_access_to_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<DelegateReadAccessToProviderRequest>,
) -> AgentServiceResult<Json<ImportCapabilitiesFromProvider>> {
    let caps = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .delegate_read_access_to_provider(payload)
        .await?;

    Ok(Json(caps))
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/capabilities/import_capabilities_from_provider",
  responses(
      (status = 200, description = "Import provided capabilities", body = ()),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn import_capabilities_from_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ImportCapabilitiesFromProvider>,
) -> AgentServiceResult<()> {
    app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .import_capabilities_from_provider(payload)
        .await?;

    Ok(())
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/capabilities/import_search_schemas_ns_from_virtual_agent",
  responses(
      (status = 200, description = "Import search schemas namespace from virtual agent", body = ()),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn import_search_schemas_ns_from_virtual_agent(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ImportCapabilitiesFromVirtualAgent>,
) -> AgentServiceResult<()> {
    app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .import_search_schemas_ns_from_virtual_agent(payload)
        .await?;

    Ok(())
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/capabilities/revoke_shared_access_from_provider",
  responses(
      (status = 200, description = "Revokes issued capability", body = DelegatedCap),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn revoke_shared_access_from_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<DelegatedCap>,
) -> AgentServiceResult<()> {
    app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .revoke_shared_access_from_provider(payload)
        .await?;

    Ok(())
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/capabilities/delegated_caps",
  responses(
      (status = 200, description = "Revokes issued capability", body = Vec<DelegatedCap>),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn delegated_caps(
    State(app_ctl): State<AppCtl>,
) -> AgentServiceResult<Json<Vec<DelegatedCap>>> {
    let res = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .delegated_caps()
        .await?;

    Ok(Json(res))
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/persona/virtual_agent_search_schemas",
  responses(
      (status = 200, description = "Returns search schemas from virtual agent", body = Vec<ReadDataRecord>),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn virtual_agent_search_schemas(
    State(app_ctl): State<AppCtl>,
) -> AgentServiceResult<Json<Vec<ReadDataRecord>>> {
    let res = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .virtual_agent_search_schemas()
        .await?;

    Ok(Json(res))
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/persona/set_attributes",
  request_body(content = SetPersonaAttributesRequest, example = json!({"key": "alice/address/0/city", "value": "Paris"})),
  responses(
    (
        status = 200,
        description = "Set persona attributes",
        body = SetPersonaAttributesRequest,
    ),
    (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn set_persona_attributes(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<SetPersonaAttributesRequest>,
) -> AgentServiceResult<()> {
    app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .set_persona_attributes(payload)
        .await?;

    Ok(())
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/persona/get_attributes",
  request_body(content = GetPersonaAttributesRequest, example = json!({"key": "alice/address/0/city"})),
  responses(
    (
        status = 200,
        description = "Get persona attributes",
        body = Vec<GetPersonaAttributesResponse>,
    ),
    (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn get_persona_attributes(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<GetPersonaAttributesRequest>,
) -> AgentServiceResult<Json<Vec<GetPersonaAttributesResponse>>> {
    let res = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .get_persona_attributes(payload)
        .await?;

    Ok(Json(res))
}

#[utoipa::path(
  post,
  path = "/api/v1/provider_agent/persona/del_attributes",
  request_body(content = DelPersonaAttributesRequest, example = json!({"key": "alice/address/0/city"})),
  responses(
    (
        status = 200,
        description = "Delete persona attributes",
        body = Vec<bool>,
    ),
    (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn del_persona_attributes(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<DelPersonaAttributesRequest>,
) -> AgentServiceResult<Json<Vec<bool>>> {
    let res = app_ctl
        .mdn_provider_agent_ctl
        .mdn_provider_agent_node_service
        .del_persona_attributes(payload)
        .await?;

    Ok(Json(res))
}
