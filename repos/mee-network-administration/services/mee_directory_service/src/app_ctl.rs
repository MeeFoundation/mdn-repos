use crate::{
    config::AppConfig,
    domain::mdn_virtual_agent::{
        controller::MdnVirtualAgentCtl, router::mdn_virtual_agent_router,
    },
    error::MeeDirectoryServiceResult,
};
use axum::Router;
use clap::Parser;
use mee_http_utils::{
    interservice::InterserviceApiSecretProvider,
    monitoring::health_check_router,
};
use mee_secrets_manager::{
    client::SimpleFileSecretsManagerClient,
    signatures_service::{
        SignaturesService, SignaturesServiceConfigBuilder,
        SignaturesServiceDefault,
    },
};
use service_utils::mee_provider_manager::auth::MeeProviderAuthorizer;
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";

#[derive(Clone)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,
    signatures_service: Arc<dyn SignaturesService + Send + Sync>,
    pub(crate) mdn_virtual_agent_ctl: MdnVirtualAgentCtl,
}

impl AppCtl {
    pub async fn try_new() -> MeeDirectoryServiceResult<Self> {
        let dotenv = dotenvy::dotenv();

        tracing_subscriber::fmt::try_init()?;

        tracing::info!("Trying to load .env file: {dotenv:#?}");

        let app_config = AppConfig::parse();

        // let rdb_storage = RbdStorage::try_new::<migrations::Migrator>(
        //     app_config.clone().into(),
        // )
        // .await?;

        let signatures_service_config =
            SignaturesServiceConfigBuilder::default()
                .jwk_secret_path(Some(
                    app_config.jwk_auth_signature_secret_path.clone(),
                ))
                .iroh_key_secret_path(Some(
                    app_config.iroh_signature_secret_path.clone(),
                ))
                .build()
                .map_err(anyhow::Error::from)?;

        let signatures_service = Arc::new(SignaturesServiceDefault::new(
            signatures_service_config,
            // TODO replace with real world secure secret manager
            Arc::new(SimpleFileSecretsManagerClient::new(format!(
                "{}/../target",
                env!("CARGO_MANIFEST_DIR")
            ))),
        ));

        Ok(Self {
            mdn_virtual_agent_ctl: MdnVirtualAgentCtl::new(
                signatures_service.clone(),
            )
            .await?,
            signatures_service,
            app_config,
        })
    }
    pub async fn run(self) -> MeeDirectoryServiceResult {
        let api_routes =
            Router::new().nest("/virtual_agent", mdn_virtual_agent_router());

        let app = Router::new()
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    crate::domain::mdn_virtual_agent::api_schema::OPEN_API_PATH
                ),
                crate::domain::mdn_virtual_agent::api_schema::ApiDoc::openapi(),
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
    ) -> Arc<dyn SignaturesService + Send + Sync> {
        self.signatures_service.clone()
    }
}

impl InterserviceApiSecretProvider for AppCtl {
    fn inter_service_api_secret(&self) -> &str {
        &self.app_config.inter_service_api_secret
    }
}
