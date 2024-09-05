mod api;
mod app_ctl;
pub mod config;
mod error;

use api::api_types::*;
use app_ctl::AppCtl;
use error::*;
use serde_json::{json, Value};
use std::collections::HashMap;

#[tokio::main]
async fn main() -> ApiResult<()> {
    AppCtl::try_new().await?.run().await
}
