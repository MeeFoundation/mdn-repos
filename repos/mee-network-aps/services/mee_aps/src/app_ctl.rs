use crate::{
    config::AppConfig,
    domain::ad_profile::{
        controller::AdProfileController, router::ad_profiles_router,
    },
    error::ApsServiceResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::monitoring::health_check_router;
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";

#[derive(Clone)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,
    pub(crate) add_profile_controller: AdProfileController,
}

impl AppCtl {
    pub async fn try_new() -> ApsServiceResult<Self> {
        let dotenv = dotenvy::dotenv();

        tracing_subscriber::fmt::try_init()?;

        tracing::info!("Trying to load .env file: {dotenv:#?}");

        let app_config = AppConfig::parse();

        let rdb_storage = RbdStorage::try_new::<migrations::Migrator>(
            app_config.clone().into(),
        )
        .await?;

        Ok(Self {
            add_profile_controller: AdProfileController::new(Arc::new(
                rdb_storage,
            )),
            app_config,
        })
    }
    pub async fn run(self) -> ApsServiceResult {
        let api_routes = Router::new().nest("/", ad_profiles_router());

        let mut app = Router::new()
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    crate::domain::ad_profile::api_schema::OPEN_API_PATH
                ),
                crate::domain::ad_profile::api_schema::ApiDoc::openapi(),
            ))
            .merge(health_check_router())
            .nest(API_V1_PATH, api_routes)
            .with_state(self.clone())
            .layer(TraceLayer::new_for_http());

        // TODO remove CORS after testing
        #[cfg(debug_assertions)]
        {
            use axum::http::{header::CONTENT_TYPE, HeaderValue, Method};
            use tower_http::cors::CorsLayer;

            app = app.layer(
                CorsLayer::new()
                    .allow_headers([CONTENT_TYPE])
                    .allow_credentials(true)
                    .allow_origin(
                        "http://127.0.0.1:8003"
                            .parse::<HeaderValue>()
                            .map_err(anyhow::Error::msg)?,
                    )
                    .allow_methods([Method::GET]),
            );
        }

        let listener = tokio::net::TcpListener::bind(format!(
            "{}:{}",
            self.app_config.server_host, self.app_config.server_port
        ))
        .await?;

        axum::serve(listener, app).await?;

        Ok(())
    }
}
