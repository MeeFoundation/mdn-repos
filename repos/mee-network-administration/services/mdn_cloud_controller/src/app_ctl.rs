use crate::{
    config::AppConfig,
    domain::{
        mdn_authority::{
            api_router::mdn_authority_router, utils::MdnSignaturesService,
        },
        mdn_custodian::{
            capabilities::api::{
                controller::MdnCapabilitiesController,
                router::mdn_capabilities_router,
            },
            identity_context::api::{
                controller::MdnIdentityContextController,
                router::mdn_identity_context_router,
            },
            storage::api::{
                controller::MdnCustodianStoragesController,
                router::mdn_custodian_storages_router,
            },
        },
        mdn_user::user_account::api::{
            controller::MdnUserAccountController, router::mdn_users_router,
        },
    },
    error::MdnCloudControllerResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::monitoring::health_check_router;
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
    pub(crate) mdn_user_account_controller: MdnUserAccountController,
    pub(crate) mdn_custodian_storages_controller:
        MdnCustodianStoragesController,
    pub(crate) mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
    pub(crate) mdn_capabilities_controller: MdnCapabilitiesController,
    pub(crate) mdn_identity_context_controller: MdnIdentityContextController,
}

impl AppCtl {
    pub async fn try_new() -> MdnCloudControllerResult<Self> {
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
                    app_config
                        .mdn_cloud_controller_jwk_signature_secret_path
                        .clone(),
                ))
                .did_id_secret_path(Some(
                    app_config.mdn_cloud_controller_did_secret_path.clone(),
                ))
                .iroh_key_secret_path(Some(
                    app_config
                        .mdn_cloud_controller_iroh_signature_secret_path
                        .clone(),
                ))
                .build()
                .map_err(anyhow::Error::from)?;

        let mdn_cloud_controller_authority_signature =
            Arc::new(SignaturesServiceDefault::new(
                signatures_service_config,
                // TODO replace with real world secure secret manager
                Arc::new(SimpleFileSecretsManagerClient::new("".to_string())),
            ));

        Ok(Self {
            mdn_identity_context_controller: MdnIdentityContextController::new(
                rdb_storage.clone(),
                mdn_cloud_controller_authority_signature.clone(),
            ),
            mdn_user_account_controller: MdnUserAccountController::new(
                rdb_storage.clone(),
                mdn_cloud_controller_authority_signature.clone(),
            ),
            mdn_custodian_storages_controller:
                MdnCustodianStoragesController::new(
                    rdb_storage.clone(),
                    mdn_cloud_controller_authority_signature.clone(),
                ),
            mdn_capabilities_controller: MdnCapabilitiesController::new(
                rdb_storage.clone(),
                mdn_cloud_controller_authority_signature.clone(),
            ),
            app_config,
            mdn_cloud_controller_authority_signature,
        })
    }
    pub async fn run(self) -> MdnCloudControllerResult {
        let api_routes = Router::new()
            .nest("/mdn_users", mdn_users_router())
            .nest("/mdn_custodian_storages", mdn_custodian_storages_router())
            .nest("/mdn_capabilities", mdn_capabilities_router())
            .nest("/mdn_identity_contexts", mdn_identity_context_router());

        let mut app = Router::new()
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    crate::domain::mdn_user::user_account::api::openapi_schema::OPEN_API_PATH
                ),
                crate::domain::mdn_user::user_account::api::openapi_schema::ApiDoc::openapi(),
            ))
            .merge(mdn_authority_router())
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
                        "http://127.0.0.1:8003".parse::<HeaderValue>()?,
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
