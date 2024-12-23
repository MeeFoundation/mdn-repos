use app_ctl::AppCtl;
use error::MdnCloudControllerResult;

mod app_ctl;
mod config;
mod db_models;
mod domain;
mod error;

#[tokio::main]
async fn main() -> MdnCloudControllerResult {
    AppCtl::try_new().await?.run().await
}
