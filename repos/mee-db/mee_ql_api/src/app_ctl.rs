use super::config::AppConfig;
use super::error::Result;
use crate::api;
use axum::extract::FromRef;
use axum::Router;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;
pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";
use crate::api::examples;
use clap::Parser;
use mee_ql::query_executor::*;

#[derive(Clone, FromRef)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,

    pub(crate) db: DB,
}

impl AppCtl {
    pub async fn try_new() -> Result<Self> {
        let app_config = AppConfig::parse();
        let db = QueryExecutorImpl::new_btree_map_based();

        Ok(Self { app_config, db })
    }

    pub async fn run(self) -> Result<()> {
        let data = examples::mock_user_data();
        self.db.insert_many(data).await.unwrap();

        let app = Router::new()
            .nest(API_V1_PATH, Router::new().merge(api::router()))
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!("{API_V1_PATH}{}", api::OPEN_API_PATH),
                api::api_schema::ApiDoc::openapi(),
            ))
            .with_state(self.clone());

        let listener = tokio::net::TcpListener::bind(format!(
            "{}:{}",
            self.app_config.server_host, self.app_config.server_port
        ))
        .await?;

        println!(
            "Server is running. See OpenApi on http://{}:{}{}/",
            self.app_config.server_host, self.app_config.server_port, SWAGGER_PATH
        );

        axum::serve(listener, app).await?;

        Ok(())
    }
}
