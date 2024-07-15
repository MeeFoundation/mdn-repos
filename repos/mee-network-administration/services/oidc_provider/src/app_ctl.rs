use crate::{
    config::AppConfig,
    domain::oidc::{
        controller::OidcController, openapi_schema::ApiDoc,
        router::oidc_provider_router,
    },
    error::MeeOidcProviderResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::monitoring::health_check_router;
use mee_authority_secrets::{
    MeeAuthoritySignatureService, MeeAuthoritySignatureServiceDefault,
};
use mee_secrets_manager::client::SimpleFileSecretsManagerClient;
use service_utils::{
    mee_provider_manager::{
        auth::MeeProviderAuthorizer,
        client::MeeProviderManagerServiceClientDefault,
    },
    mee_user_manager::client::MeeUserManagerServiceClientDefault,
};
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

#[derive(Clone)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,
    pub(crate) mee_authority_signature:
        Arc<dyn MeeAuthoritySignatureService + Send + Sync>,

    pub(crate) oidc_controller: OidcController,
}

impl AppCtl {
    pub async fn try_new(
        app_config: Option<AppConfig>,
    ) -> MeeOidcProviderResult<Self> {
        let app_config = if let Some(app_config) = app_config {
            app_config
        } else {
            tracing_subscriber::fmt::try_init()?;

            let dotenv = dotenvy::dotenv();
            tracing::info!("Trying to load .env file: {dotenv:#?}");

            AppConfig::parse()
        };

        let rdb_storage = RbdStorage::try_new::<migrations::Migrator>(
            app_config.clone().into(),
        )
        .await?;

        let mee_authority_signature =
            Arc::new(MeeAuthoritySignatureServiceDefault::new(
                app_config.mee_signature_secret_path.clone(),
                // TODO replace with real world secure secret manager
                Arc::new(SimpleFileSecretsManagerClient::new(format!(
                    "{}/../target",
                    env!("CARGO_MANIFEST_DIR")
                ))),
            ));

        let mee_user_manager_service_client =
            Arc::new(MeeUserManagerServiceClientDefault::try_new(
                app_config.user_manager_url.clone(),
                app_config.inter_service_api_secret.clone(),
            )?);

        let mee_provider_manager_service_client =
            Arc::new(MeeProviderManagerServiceClientDefault::try_new(
                app_config.provider_manager_url.clone(),
                app_config.inter_service_api_secret.clone(),
            )?);

        Ok(Self {
            oidc_controller: OidcController::new(
                app_config.clone(),
                mee_user_manager_service_client,
                mee_authority_signature.clone(),
                mee_provider_manager_service_client,
                Arc::new(rdb_storage),
            ),
            mee_authority_signature,
            app_config,
        })
    }
    pub async fn run(self) -> MeeOidcProviderResult {
        let app = Router::new()
            .merge(
                SwaggerUi::new("/swagger-ui")
                    .url("/oidc-api-docs/openapi.json", ApiDoc::openapi()),
            )
            .merge(health_check_router())
            .nest("/", oidc_provider_router())
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

impl MeeProviderAuthorizer for AppCtl {
    fn mee_authority_signature(
        &self,
    ) -> Arc<dyn MeeAuthoritySignatureService + Send + Sync> {
        self.mee_authority_signature.clone()
    }
}
