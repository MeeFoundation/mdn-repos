use super::api_types::{
    CloudNodeAttachmentRequest, CloudNodeAttachmentResponse,
};
use crate::{app_ctl::AppCtl, error::MeeProviderManagerResult};
use axum::{extract::State, Json};
use mee_http_utils::interservice::InterServiceSecuredApi;
use service_utils::mee_provider_manager::{
    api_types::IsCloudNodeLinkedRequest, auth::LoggedInProvider,
};

#[utoipa::path(
  post,
  path = "/api/v1/providers/internal/is_cloud_node_linked",
  responses(
      (status = 200, description = "Checks if provider's cloud node is linked with them", body = bool),
      (status = 500, description = "Something went wrong", body = String),
  ),
  security(
    ("inter_service_api_secret" = [])
  )
)]
pub async fn is_cloud_node_linked_with_provider(
    State(_app_ctl): State<AppCtl>,
    _inter_service_secured_api: InterServiceSecuredApi,
    Json(_payload): Json<IsCloudNodeLinkedRequest>,
) -> MeeProviderManagerResult<Json<bool>> {
    // TODO: add implementation
    Ok(Json(true))
}

#[utoipa::path(
  get,
  path = "/api/v1/providers/cloud_nodes",
  responses(
      (status = 200, description = "Provider's cloud node list", body = Vec<CloudNodeAttachmentResponse>),
      (status = 500, description = "Something went wrong", body = String),
  ),
  security(
    ("token_biscuit" = [])
  )
)]
pub async fn list_cloud_nodes(
    logged_in_provider: LoggedInProvider,
    State(app_ctl): State<AppCtl>,
) -> MeeProviderManagerResult<Json<Vec<CloudNodeAttachmentResponse>>> {
    Ok(Json(
        app_ctl
            .provider_controller
            .list_cloud_nodes(logged_in_provider)
            .await?,
    ))
}

#[utoipa::path(
  post,
  path = "/api/v1/providers/cloud_nodes",
  responses(
      (status = 200, description = "Cloud has successfully linked with the provider", body = Option<CloudNodeAttachmentResponse>),
      (status = 500, description = "Something went wrong", body = String),
  ),
  security(
    ("token_biscuit" = [])
  )
)]
pub async fn attach_cloud_node(
    logged_in_provider: LoggedInProvider,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<CloudNodeAttachmentRequest>,
) -> MeeProviderManagerResult<Json<CloudNodeAttachmentResponse>> {
    Ok(Json(
        app_ctl
            .provider_controller
            .attach_cloud_node(logged_in_provider, payload)
            .await?,
    ))
}
