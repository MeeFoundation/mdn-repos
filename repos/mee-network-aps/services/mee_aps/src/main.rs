use app_ctl::AppCtl;
use error::ApsServiceResult;

mod app_ctl;
mod config;
mod db_models;
mod domain;
mod error;

#[tokio::main]
async fn main() -> ApsServiceResult {
    AppCtl::try_new().await?.run().await
}
