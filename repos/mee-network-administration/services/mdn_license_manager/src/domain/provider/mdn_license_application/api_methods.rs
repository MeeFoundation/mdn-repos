use super::api_types::{
    MdnLicenseApprovedProviderAccessTokenRequest,
    MdnLicenseApprovedProviderAccessTokenResponse,
};
use crate::{app_ctl::AppCtl, error::MdnLicenseManagerResult};
use axum::{
    extract::{Path, State},
    Json,
};
use axum_extra::extract::Query;

#[utoipa::path(
  post,
  path = "/api/v1/providers/mdn_license_applications/access_token",
  responses(
      (status = 200, description = "Access token issued successfully", body = MdnLicenseApprovedProviderAccessTokenResponse),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn mdn_license_approved_provider_access_token(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<MdnLicenseApprovedProviderAccessTokenRequest>,
) -> MdnLicenseManagerResult<Json<MdnLicenseApprovedProviderAccessTokenResponse>>
{
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .issued_mdn_license_approved_provider_access_token(payload)
            .await?,
    ))
}

use super::api_types::*;

/// Create draft Mee data network license application for provider
#[utoipa::path(
        post,
        path = "/api/v1/providers/{provider_meeid}/mdn_license_applications",
        params(
            ("provider_meeid", Path, description = "Provider mee id"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application created successfully", body = ProviderMdnLicenseApplicationWriteRequest),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn create(
    Path(provider_meeid): Path<String>,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ProviderMdnLicenseApplicationWriteRequest>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .create(provider_meeid, payload)
            .await?,
    ))
}

///Get provider Mee data network license application by meeid for provider
#[utoipa::path(
        get,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application found", body = ProviderMdnLicenseApplicationModelResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn get_by_meeid(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .get_by_meeid(provider_meeid, meeid)
            .await?,
    ))
}

///Get all HIL appliications by provider sorted by last update
#[utoipa::path(
        get,
       path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("application_statuses" = StatusesQueryParam, Query, description = "Filter by application statuses"),
        ),
        responses(
            (status = 200, description = "All the provider's provider Mee data network license application found", body = Vec<ProviderMdnLicenseApplicationModelResponse>),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn get_all_by_provider(
    Path(provider_meeid): Path<String>,
    Query(application_statuses): Query<StatusesQueryParam>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<
    Json<Vec<ProviderMdnLicenseApplicationModelResponse>>,
> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .get_all_by_provider(provider_meeid, application_statuses.statuses)
            .await?,
    ))
}

///Get all provider Mee data network license appliications with pagination and sorting by last update
#[utoipa::path(
        post,
       path =  "/api/v1/providers/mdn_license_applications/list",
        responses(
            (status = 200, description = "Page with provider provider Mee data network license applications", body = ProviderMdnLicenseApplicationListResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn get_all(
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ProviderMdnLicenseApplicationListRequest>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationListResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .get_all(payload)
            .await?,
    ))
}
///Update draft provider Mee data network license application (Provider can edit only draft applications)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application updated", body = ProviderMdnLicenseApplicationWriteRequest),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn update_draft(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<ProviderMdnLicenseApplicationWriteRequest>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .update_draft(provider_meeid, meeid, payload)
            .await?,
    ))
}

///Update draft provider Mee data network license application status to Processing (Provider submits it)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}/to_processing",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application after changing its status to processing", body = ProviderMdnLicenseApplicationModelResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn to_processing(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .to_processing(provider_meeid, meeid)
            .await?,
    ))
}

///Update processing provider Mee data network license application status to canceled (Provider can cancel it)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}/to_canceled",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application after changing its status to canceled", body = ProviderMdnLicenseApplicationModelResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn to_canceled(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .to_canceled(provider_meeid, meeid)
            .await?,
    ))
}

///Update processing provider Mee data network license application status to approved (Mee admin can approve it.
///In case another approved application for this provider exists it will automatically discontinued)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}/to_approved",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "All provider's provider Mee data network license applications after changing its statuses", body = Vec<ProviderMdnLicenseApplicationModelResponse>),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn to_approved(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<
    Json<Vec<ProviderMdnLicenseApplicationModelResponse>>,
> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .to_approved(provider_meeid, meeid)
            .await?,
    ))
}

///Update processing provider Mee data network license application status to rejected (Mee admin can reject it)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}/to_rejected",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application after changing its status to rejected", body = ProviderMdnLicenseApplicationModelResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn to_rejected(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .to_rejected(provider_meeid, meeid)
            .await?,
    ))
}

///Update canceled provider Mee data network license application status to draft (If Provider wants resubmit it again)
#[utoipa::path(
        put,
        path =  "/api/v1/providers/{provider_meeid}/mdn_license_applications/{meeid}/to_draft",
        params(
            ("provider_meeid", Path, description = "Provider meeid"),
            ("meeid", Path, description = "provider Mee data network license application meeid"),
        ),
        responses(
            (status = 200, description = "provider Mee data network license application after changing its status to draft", body = ProviderMdnLicenseApplicationModelResponse),
            (status = 500, description = "Something went wrong", body = String),
        ),
    )]
pub async fn to_draft(
    Path((provider_meeid, meeid)): Path<(String, String)>,
    State(app_ctl): State<AppCtl>,
) -> MdnLicenseManagerResult<Json<ProviderMdnLicenseApplicationModelResponse>> {
    Ok(Json(
        app_ctl
            .provider_mdn_license_controller
            .to_draft(provider_meeid, meeid)
            .await?,
    ))
}
