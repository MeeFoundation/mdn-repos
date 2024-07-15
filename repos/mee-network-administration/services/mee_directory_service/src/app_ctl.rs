use crate::{
    config::AppConfig, domain::persona_model::router::persona_model_router,
    error::MeeDirectoryServiceResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::{
    interservice::InterserviceApiSecretProvider,
    monitoring::health_check_router,
};
use mee_authority_secrets::{
    MeeAuthoritySignatureService, MeeAuthoritySignatureServiceDefault,
};
use mee_secrets_manager::client::SimpleFileSecretsManagerClient;
use service_utils::mee_provider_manager::auth::MeeProviderAuthorizer;
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";

#[derive(Clone)]
pub struct AppCtl {
    pub rdb_storage: RbdStorage,
    pub app_config: AppConfig,
    mee_authority_signature:
        Arc<dyn MeeAuthoritySignatureService + Send + Sync>,
}

impl AppCtl {
    pub async fn try_new() -> MeeDirectoryServiceResult<Self> {
        let dotenv = dotenvy::dotenv();

        tracing_subscriber::fmt::try_init()?;

        tracing::info!("Trying to load .env file: {dotenv:#?}");

        let app_config = AppConfig::parse();

        let rdb_storage = RbdStorage::try_new::<migrations::Migrator>(
            app_config.clone().into(),
        )
        .await?;

        Ok(Self {
            rdb_storage,
            mee_authority_signature: Arc::new(
                MeeAuthoritySignatureServiceDefault::new(
                    app_config.mee_signature_secret_path.clone(),
                    // TODO replace with real world secure secret manager
                    Arc::new(SimpleFileSecretsManagerClient::new(format!(
                        "{}/../target",
                        env!("CARGO_MANIFEST_DIR")
                    ))),
                ),
            ),
            app_config,
        })
    }
    pub async fn run(self) -> MeeDirectoryServiceResult {
        let api_routes =
            Router::new().nest("/persona_model", persona_model_router());

        let app = Router::new()
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    crate::domain::persona_model::api_schema::OPEN_API_PATH
                ),
                crate::domain::persona_model::api_schema::ApiDoc::openapi(),
            ))
            .merge(health_check_router())
            .nest(API_V1_PATH, api_routes)
            .with_state(self.clone())
            .layer(TraceLayer::new_for_http());

        let listener = tokio::net::TcpListener::bind(format!(
            "{}:{}",
            self.app_config.server_host, self.app_config.server_port
        ))
        .await?;

        axum::serve(listener, app).await?;

        Ok(())
    }
}

// Service factory methods
impl AppCtl {}

impl MeeProviderAuthorizer for AppCtl {
    fn mee_authority_signature(
        &self,
    ) -> Arc<dyn MeeAuthoritySignatureService + Send + Sync> {
        self.mee_authority_signature.clone()
    }
}

impl InterserviceApiSecretProvider for AppCtl {
    fn inter_service_api_secret(&self) -> &str {
        &self.app_config.inter_service_api_secret
    }
}
