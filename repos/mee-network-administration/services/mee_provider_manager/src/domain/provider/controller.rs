use super::{
    account::{
        api_types::{
            CreateProviderAccountRequest, ProviderAccountLoginRequest,
            ProviderAccountLoginResponse,
        },
        repository::{
            ProviderAccountRepository, ProviderAccountRepositoryDefault,
        },
        service::ProviderAccountService,
    },
    cloud_nodes::{
        api_types::{CloudNodeAttachmentRequest, CloudNodeAttachmentResponse},
        repository::{
            ProviderCloudNodesRepository, ProviderCloudNodesRepositoryDefault,
        },
        service::ProviderCloudNodesService,
    },
};
use crate::error::MeeProviderManagerResult;
use mee_db_utils::sql_storage::IRbdStorage;
use mee_secrets_manager::signatures_service::SignaturesService;
use sea_orm::ConnectionTrait;
use sea_orm::TransactionTrait;
use service_utils::mee_provider_manager::{
    api_types::ProviderAccountInfoResponse, auth::LoggedInProvider,
};
use std::sync::Arc;

#[derive(Clone)]
pub struct ProviderController {
    rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
    mee_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
}

impl ProviderController {
    pub fn new(
        rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
        mee_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
    ) -> Self {
        Self {
            rdb_storage,
            mee_authority_signature,
        }
    }
    pub fn provider_account_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl ProviderAccountRepository + 'a {
        ProviderAccountRepositoryDefault::new(tx)
    }
    pub fn provider_cloud_nodes_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl ProviderCloudNodesRepository + 'a {
        ProviderCloudNodesRepositoryDefault::new(tx)
    }
    pub fn provider_account_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> ProviderAccountService<'a> {
        let provider_account_repository =
            Box::new(self.provider_account_repository(tx));

        ProviderAccountService::new(
            provider_account_repository,
            self.mee_authority_signature.clone(),
        )
    }
    pub fn provider_cloud_nodes_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> ProviderCloudNodesService<'a> {
        let provider_account_repository =
            Box::new(self.provider_account_repository(tx));

        let provider_cloud_node_repository =
            Box::new(self.provider_cloud_nodes_repository(tx));

        let provider_account_service = ProviderAccountService::new(
            provider_account_repository,
            self.mee_authority_signature.clone(),
        );

        ProviderCloudNodesService::new(
            provider_cloud_node_repository,
            provider_account_service,
        )
    }
}

impl ProviderController {
    pub async fn provider_profile(
        &self,
        provider_meeid: String,
    ) -> MeeProviderManagerResult<ProviderAccountInfoResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let provider_account_service =
                        this.provider_account_service(tx);
                    let res = provider_account_service
                        .get_account_by_meeid_err(&provider_meeid)
                        .await?
                        .into();

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn register_provider(
        &self,
        payload: CreateProviderAccountRequest,
    ) -> MeeProviderManagerResult<ProviderAccountLoginResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let provider_account_service =
                        this.provider_account_service(tx);
                    let res = provider_account_service
                        .create_customer_account(payload)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn login_provider(
        &self,
        payload: ProviderAccountLoginRequest,
    ) -> MeeProviderManagerResult<ProviderAccountLoginResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let provider_account_service =
                        this.provider_account_service(tx);
                    let res = provider_account_service
                        .provider_login(payload)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
}

impl ProviderController {
    pub async fn list_cloud_nodes(
        &self,
        logged_in_provider: LoggedInProvider,
    ) -> MeeProviderManagerResult<Vec<CloudNodeAttachmentResponse>> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let provider_cloud_nodes_service =
                        this.provider_cloud_nodes_service(tx);

                    let res = provider_cloud_nodes_service
                        .list_cloud_nodes(logged_in_provider)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn attach_cloud_node(
        &self,
        logged_in_provider: LoggedInProvider,
        payload: CloudNodeAttachmentRequest,
    ) -> MeeProviderManagerResult<CloudNodeAttachmentResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let provider_cloud_nodes_service =
                        this.provider_cloud_nodes_service(tx);
                    let res = provider_cloud_nodes_service
                        .attach_cloud_node(payload, logged_in_provider)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
}
