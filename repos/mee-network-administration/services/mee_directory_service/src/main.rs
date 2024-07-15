use app_ctl::AppCtl;
use error::MeeDirectoryServiceResult;

mod app_ctl;
mod config;
mod domain;
mod error;

#[tokio::main]
async fn main() -> MeeDirectoryServiceResult {
    AppCtl::try_new().await?.run().await
}
