use crate::{
    config::AppConfig,
    domain::provider::{
        api_schema as provider_mdn_license_application_schema,
        mdn_license_application::controller::{
            ProviderMdnLicenseController, ProviderMdnLicenseControllerImpl,
        },
        router as provider_mdn_license_application_router,
    },
    error::MdnLicenseManagerResult,
};
use axum::Router;
use clap::Parser;
use mee_db_utils::sql_storage::RbdStorage;
use mee_http_utils::monitoring::health_check_router;
use service_utils::mee_provider_manager::client::{
    MeeProviderManagerServiceClient, MeeProviderManagerServiceClientDefault,
};
use std::sync::Arc;
use tower_http::trace::TraceLayer;
use utoipa::OpenApi;
use utoipa_swagger_ui::SwaggerUi;

pub const API_V1_PATH: &str = "/api/v1";
const SWAGGER_PATH: &str = "/swagger-ui";

type MeeProviderManagerServiceClientDep =
    Arc<dyn MeeProviderManagerServiceClient + Send + Sync>;

type ProviderMdnLicenseControllerDep =
    Arc<dyn ProviderMdnLicenseController + Sync + Send>;

#[derive(Clone)]
pub struct AppCtl {
    pub(crate) app_config: AppConfig,
    pub(crate) provider_mdn_license_controller:
        Arc<dyn ProviderMdnLicenseController + Sync + Send>,
}
impl AppCtl {
    pub async fn try_new() -> MdnLicenseManagerResult<Self> {
        let dotenv = dotenvy::dotenv();

        tracing_subscriber::fmt::try_init()?;

        tracing::info!("Trying to load .env file: {dotenv:#?}");

        let app_config = AppConfig::parse();

        let rdb_storage = Arc::new(
            RbdStorage::try_new::<migrations::Migrator>(
                app_config.clone().into(),
            )
            .await?,
        );

        let mee_provider_manager_service_client =
            Self::mee_provider_manager_service_client(app_config.clone())?;

        Ok(Self {
            app_config,
            provider_mdn_license_controller:
                Self::provider_mdn_license_controller(
                    rdb_storage.clone(),
                    mee_provider_manager_service_client,
                ),
        })
    }
    pub async fn run(self) -> MdnLicenseManagerResult {
        let app = Router::new()
            .nest(
                API_V1_PATH,
                Router::new()
                    .merge(provider_mdn_license_application_router::router()),
            )
            .merge(SwaggerUi::new(SWAGGER_PATH).url(
                format!(
                    "{API_V1_PATH}{}",
                    provider_mdn_license_application_schema::OPEN_API_PATH
                ),
                provider_mdn_license_application_schema::ApiDoc::openapi(),
            ))
            .merge(health_check_router())
            .with_state(self.clone())
            .layer(TraceLayer::new_for_http());

        let listener = tokio::net::TcpListener::bind(format!(
            "{}:{}",
            self.app_config.server_host, self.app_config.server_port
        ))
        .await?;

        println!(
            "Server is running. See OpenApi on http://{}:{}{}/",
            self.app_config.server_host,
            self.app_config.server_port,
            SWAGGER_PATH
        );

        axum::serve(listener, app).await?;

        Ok(())
    }
}

// Service factory methods
impl AppCtl {
    fn mee_provider_manager_service_client(
        app_config: AppConfig,
    ) -> MdnLicenseManagerResult<MeeProviderManagerServiceClientDep> {
        let res = MeeProviderManagerServiceClientDefault::try_new(
            app_config.mee_provider_manager_service_url.clone(),
            app_config.inter_service_api_secret.clone(),
        )?;
        Ok(Arc::new(res))
    }

    fn provider_mdn_license_controller(
        rdb_storage: Arc<RbdStorage>,
        mee_provider_manager_service_client: MeeProviderManagerServiceClientDep,
    ) -> ProviderMdnLicenseControllerDep {
        Arc::new(ProviderMdnLicenseControllerImpl::new(
            rdb_storage,
            mee_provider_manager_service_client,
        ))
    }
}
