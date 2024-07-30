use axum::extract::FromRef;
use axum::Router;
use clap::builder::TypedValueParser;
// use tower_http::trace::TraceLayer;
use super::config::AppConfig;
use super::error::*;
use super::storage::*;
use crate::api;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;
pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";
use crate::storage::DB;
use clap::Parser;
use std::sync::Arc;

#[derive(Clone, FromRef)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,

    pub(crate) db: DB,
}

impl AppCtl {
    pub async fn try_new() -> ApiResult<Self> {
        let app_config = AppConfig::parse();
        let db = Arc::new(StorageImpl::new(&app_config.db_path)?);

        Ok(Self { app_config, db })
    }

    pub async fn run(self) -> ApiResult<()> {
        let app = Router::new()
            .nest(API_V1_PATH, Router::new().merge(api::router()))
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!("{API_V1_PATH}{}", api::OPEN_API_PATH),
                api::api_schema::ApiDoc::openapi(),
            ))
            .with_state(self.clone());
        // .layer(TraceLayer::new_for_http());

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
