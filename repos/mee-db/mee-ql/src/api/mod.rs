pub mod api_methods;
pub mod api_schema;
pub mod api_types;
mod examples;

use crate::{app_ctl::AppCtl, storage::DB};
use api_methods::*;

use axum::{routing::post, Router};

use crate::storage::Storage;

pub fn router() -> Router<AppCtl> {
    Router::new()
        .route("/select", post(select))
        .route("/merge", post(merge))
        .route("/delete", post(delete))
        .route("/update", post(update))
}

pub const OPEN_API_PATH: &str = "/openapi.json";
