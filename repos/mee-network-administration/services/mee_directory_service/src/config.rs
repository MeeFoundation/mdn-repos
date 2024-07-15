use clap::Parser;
use mee_db_utils::sql_storage::RdbStorageConfig;
use url::Url;

#[derive(Debug, Clone, Parser)]
#[command(author, version, about, long_about = None)]
pub struct AppConfig {
    #[arg(env, long)]
    pub mdn_license_manager_url: Url,

    #[arg(env, long)]
    pub user_manager_url: Url,

    #[arg(env, long)]
    pub provider_manager_url: Url,

    #[arg(env, long)]
    pub mee_signature_secret_path: String,

    #[arg(env, long)]
    pub inter_service_api_secret: String,

    #[arg(env, long)]
    pub server_host: String,

    #[arg(env, long)]
    pub server_port: u16,

    #[arg(env, long, help = "SQLite/PostgreSQL connection URL")]
    pub database_url: Url,

    #[arg(env, long)]
    pub db_pool_size: u32,
}

impl From<AppConfig> for RdbStorageConfig {
    fn from(
        AppConfig {
            database_url,
            db_pool_size,
            ..
        }: AppConfig,
    ) -> Self {
        Self {
            database_url,
            db_pool_size,
        }
    }
}
