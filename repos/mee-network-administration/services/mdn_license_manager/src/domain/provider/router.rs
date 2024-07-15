use super::mdn_license_application::api_methods::*;
use crate::app_ctl::AppCtl;
use axum::{
    routing::{get, post, put},
    Router,
};

pub fn router() -> Router<AppCtl> {
    Router::new().route(
        "/providers/mdn_license_applications/access_token",
        post(mdn_license_approved_provider_access_token),
    )
    .route("/providers/:provider_meeid/mdn_license_applications", post(create))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid", get(get_by_meeid))
        .route("/providers/:provider_meeid/mdn_license_applications", get(get_all_by_provider))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid", put(update_draft))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid/to_processing", put(to_processing))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid/to_canceled", put(to_canceled))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid/to_approved", put(to_approved))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid/to_rejected", put(to_rejected))
        .route("/providers/:provider_meeid/mdn_license_applications/:uid/to_draft", put(to_draft))
        .route("/providers/mdn_license_applications/list", post(get_all))
}
