mod api;
mod app_ctl;
pub mod config;
mod error;

use app_ctl::AppCtl;
use error::Result;
use tracing_subscriber::filter::EnvFilter;
use tracing_subscriber::fmt;
use tracing_subscriber::prelude::*;

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::registry()
        .with(fmt::layer())
        .with(EnvFilter::from_default_env())
        .init();

    AppCtl::try_new().await?.run().await
}
