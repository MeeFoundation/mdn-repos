mod app_ctl;
mod config;
mod db_models;
mod domain;
mod error;

use app_ctl::AppCtl;
use error::MdnLicenseManagerResult;

#[tokio::main]
async fn main() -> MdnLicenseManagerResult {
    AppCtl::try_new().await?.run().await
}
