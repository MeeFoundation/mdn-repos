use clap::Parser;

#[derive(Debug, Clone, Parser)]
#[command(author, version, about, long_about = None)]
pub struct AppConfig {
    #[arg(env, long, default_value_t = 8080)]
    pub server_port: u16,

    #[arg(env, long, default_value = "localhost")]
    pub server_host: String,

    #[arg(env, long, default_value = "mee-ql-db")]
    pub db_path: String,
}
