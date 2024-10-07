use super::api_types::ShareSearchSchemasNsWithProviderRequest;
use crate::{app_ctl::AppCtl, error::MeeDirectoryServiceResult};
use axum::{extract::State, Json};
use mee_data_sync::mdn::{
    common::store::ReadDataRecord,
    provider_agent::delegation::manager::ImportCapabilitiesFromVirtualAgent,
};

#[utoipa::path(
    get,
    path = "/api/v1/virtual_agent/node/iroh_ticket",
    responses(
        (status = 200, description = "Returns iroh node network (discovery) ticket", body = String),
        (status = 500, description = "Something went wrong", body = String),
    ),
  )]
pub async fn iroh_ticket(
    State(app_ctl): State<AppCtl>,
) -> MeeDirectoryServiceResult<String> {
    let ticket = app_ctl
        .mdn_virtual_agent_ctl
        .mdn_virtual_agent_node_service
        .iroh_net_ticket()
        .await?;

    Ok(ticket)
}

#[utoipa::path(
  post,
  path = "/api/v1/virtual_agent/capabilities/share_search_schemas_ns_with_provider",
  responses(
      (status = 200, description = "Share search schemas namespace with the MDN provider", body = ImportCapabilitiesFromVirtualAgent),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn share_search_schemas_ns_with_provider(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ShareSearchSchemasNsWithProviderRequest>,
) -> MeeDirectoryServiceResult<Json<ImportCapabilitiesFromVirtualAgent>> {
    let res = app_ctl
        .mdn_virtual_agent_ctl
        .mdn_virtual_agent_node_service
        .share_search_schemas_ns_with_provider(payload.provider_id.parse()?)
        .await?;

    Ok(Json(res))
}

#[utoipa::path(
    get,
    path = "/api/v1/virtual_agent/persona/search_schemas",
    responses(
        (status = 200, description = "Returns search schemas", body = Vec<ReadDataRecord>),
        (status = 500, description = "Something went wrong", body = String),
    ),
  )]
pub async fn search_schemas(
    State(app_ctl): State<AppCtl>,
) -> MeeDirectoryServiceResult<Json<Vec<ReadDataRecord>>> {
    let res = app_ctl
        .mdn_virtual_agent_ctl
        .mdn_virtual_agent_node_service
        .search_schemas()
        .await?;

    Ok(Json(res))
}
