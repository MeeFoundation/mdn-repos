use crate::config::AppConfig;
use clap::Parser;
use mee_db_utils::db_migrator::run_db_migrator;

mod config;

#[tokio::main(flavor = "current_thread")]
async fn main() -> anyhow::Result<()> {
    let dotenv = dotenvy::dotenv();
    tracing::info!("Trying to load .env file: {dotenv:#?}");

    run_db_migrator::<migrations::Migrator>(AppConfig::try_parse()?).await
}
