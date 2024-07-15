use app_ctl::AppCtl;
use error::MeeProviderManagerResult;

mod app_ctl;
mod config;
mod db_models;
mod domain;
mod error;

#[tokio::main]
async fn main() -> MeeProviderManagerResult {
    AppCtl::try_new().await?.run().await
}
