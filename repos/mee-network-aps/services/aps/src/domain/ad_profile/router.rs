use axum::{routing::post, Router};
use crate::app_ctl::AppCtl;
use super::sda_profiles::api_methods::add_sda_profile;

pub fn ad_profiles_router() -> Router<AppCtl> {
    Router::new().route("/ad_profiles", post(add_sda_profile))
}
