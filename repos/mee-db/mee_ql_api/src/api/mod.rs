pub mod api_methods;
pub mod api_schema;

pub mod examples;

use crate::app_ctl::AppCtl;
use api_methods::*;

use axum::{routing::post, Router};

pub fn router() -> Router<AppCtl> {
    Router::new()
        .route("/execute", post(execute))
        .route("/insert_many", post(insert_many))
}

pub const OPEN_API_PATH: &str = "/openapi.json";
