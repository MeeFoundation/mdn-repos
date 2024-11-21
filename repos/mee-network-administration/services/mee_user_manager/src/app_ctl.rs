use crate::{
    config::AppConfig,
    domain::user::{controller::UserController, router::users_router},
    error::MeeUserManagerResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::{
    interservice::InterserviceApiSecretProvider,
    monitoring::health_check_router,
};

use mee_secrets_manager::{
    client::SimpleFileSecretsManagerClient,
    signatures_service::{
        SignaturesServiceConfigBuilder, SignaturesServiceDefault,
    },
};
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";

#[derive(Clone)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,
    pub(crate) user_controller: UserController,
}

impl AppCtl {
    pub async fn try_new() -> MeeUserManagerResult<Self> {
        let dotenv = dotenvy::dotenv();

        tracing_subscriber::fmt::try_init()?;

        tracing::info!("Trying to load .env file: {dotenv:#?}");

        let app_config = AppConfig::parse();

        let rdb_storage = RbdStorage::try_new::<migrations::Migrator>(
            app_config.clone().into(),
        )
        .await?;

        let signatures_service_config =
            SignaturesServiceConfigBuilder::default()
                .jwk_secret_path(Some(
                    app_config.mee_signature_secret_path.clone(),
                ))
                .build()
                .map_err(anyhow::Error::from)?;

        let mee_authority_signature = Arc::new(SignaturesServiceDefault::new(
            signatures_service_config,
            // TODO replace with real world secure secret manager
            Arc::new(SimpleFileSecretsManagerClient::new(format!(
                "{}/../target",
                env!("CARGO_MANIFEST_DIR")
            ))),
        ));

        Ok(Self {
            user_controller: UserController::new(
                Arc::new(rdb_storage),
                mee_authority_signature,
            ),
            app_config,
        })
    }
    pub async fn run(self) -> MeeUserManagerResult {
        let api_routes = Router::new().nest("/users", users_router());

        let mut app = Router::new()
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    crate::domain::user::api_schema::OPEN_API_PATH
                ),
                crate::domain::user::api_schema::ApiDoc::openapi(),
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
                        "http://127.0.0.1:8003".parse::<HeaderValue>().unwrap(),
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

impl InterserviceApiSecretProvider for AppCtl {
    fn inter_service_api_secret(&self) -> &str {
        &self.app_config.inter_service_api_secret
    }
}
