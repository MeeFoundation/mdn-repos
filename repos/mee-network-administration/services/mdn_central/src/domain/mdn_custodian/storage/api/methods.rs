use super::types::RegisterMdnCustodianStorageRequest;
use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    error::MdnCentralResult,
};
use axum::extract::{Json, State};
use mdn_identity_agent::mdn_cloud::mdn_custodian_storage::api_types::MdnCustodianStorageResponse;

pub async fn list_all_custodian_storages(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<Vec<MdnCustodianStorageResponse>>> {
    Ok(Json(
        app_ctl
            .mdn_custodian_storages_controller
            .list_all_custodian_storages(
                logged_in_mdn_user.mdn_custodian_uid(),
            )
            .await?,
    ))
}

pub async fn register_custodian_storage(
    logged_in_mdn_user: LoggedInMdnUser,
    State(app_ctl): State<AppCtl>,
    Json(payload): Json<RegisterMdnCustodianStorageRequest>,
) -> MdnCentralResult {
    Ok(app_ctl
        .mdn_custodian_storages_controller
        .register_custodian_storage(payload, logged_in_mdn_user)
        .await?)
}
