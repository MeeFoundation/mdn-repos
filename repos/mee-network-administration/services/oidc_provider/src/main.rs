use app_ctl::AppCtl;
use error::MeeOidcProviderResult;

mod app_ctl;
mod config;
mod db_models;
mod domain;
mod error;
#[cfg(test)]
mod tests;

#[tokio::main]
async fn main() -> MeeOidcProviderResult {
    AppCtl::try_new(None).await?.run().await
}
