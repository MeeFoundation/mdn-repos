use mee_db_utils::sql_storage::IRbdStorage;
use sea_orm::ConnectionTrait;
use sea_orm::TransactionTrait;
use service_utils::mee_provider_manager::client::MeeProviderManagerServiceClient;
use std::sync::Arc;

use crate::error::MdnLicenseManagerResult;

use super::dto::ModelPage;
use super::{
    api_types::{
        MdnLicenseApprovedProviderAccessTokenRequest,
        MdnLicenseApprovedProviderAccessTokenResponse,
        ProviderMdnLicenseApplicationListRequest,
        ProviderMdnLicenseApplicationListResponse,
        ProviderMdnLicenseApplicationModelResponse,
        ProviderMdnLicenseApplicationWriteRequest,
    },
    domain::MdnLicenseApplicationStatus,
    repository::{
        ProviderMdnLicenseApplicationRepo,
        ProviderMdnLicenseApplicationRepoImpl,
    },
    service::{ProviderMdnLicenseService, ProviderMdnLicenseServiceImpl},
};

#[async_trait::async_trait]
pub trait ProviderMdnLicenseController {
    async fn issued_mdn_license_approved_provider_access_token(
        &self,
        request: MdnLicenseApprovedProviderAccessTokenRequest,
    ) -> MdnLicenseManagerResult<MdnLicenseApprovedProviderAccessTokenResponse>;

    async fn create(
        &self,
        provider_meeid: String,
        ent: ProviderMdnLicenseApplicationWriteRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn get_by_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn get_all_by_provider(
        &self,
        provider_meeid: String,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModelResponse>>;

    async fn update_draft(
        &self,
        provider_meeid: String,
        meeid: String,
        ent: ProviderMdnLicenseApplicationWriteRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn to_processing(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn to_canceled(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn to_approved(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModelResponse>>;

    async fn to_rejected(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn to_draft(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>;

    async fn get_all(
        &self,
        payload: ProviderMdnLicenseApplicationListRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationListResponse>;

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()>;
}

#[derive(Clone)]
pub struct ProviderMdnLicenseControllerImpl {
    rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
    mee_provider_manager_service_client:
        Arc<dyn MeeProviderManagerServiceClient + Send + Sync>,
}

impl ProviderMdnLicenseControllerImpl {
    pub fn new(
        rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
        mee_provider_manager_service_client: Arc<
            dyn MeeProviderManagerServiceClient + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mee_provider_manager_service_client,
        }
    }

    fn provider_mdn_license_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl ProviderMdnLicenseService + 'a {
        ProviderMdnLicenseServiceImpl::new(
            self.mee_provider_manager_service_client.clone(),
            Box::new(self.provider_mdn_license_application_repo(tx)),
        )
    }

    fn provider_mdn_license_application_repo<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl ProviderMdnLicenseApplicationRepo + Sync + Send + 'a {
        ProviderMdnLicenseApplicationRepoImpl::new(tx)
    }
}

#[async_trait::async_trait]
impl ProviderMdnLicenseController for ProviderMdnLicenseControllerImpl {
    async fn issued_mdn_license_approved_provider_access_token(
        &self,
        request: MdnLicenseApprovedProviderAccessTokenRequest,
    ) -> MdnLicenseManagerResult<MdnLicenseApprovedProviderAccessTokenResponse>
    {
        let conn = self.rdb_storage.connection();
        let mdn_license_approved_provider_access_token = self
            .provider_mdn_license_service(conn.as_ref())
            .issued_mdn_license_approved_provider_access_token(
                request.provider_node_ssi_jwt,
            )
            .await?;

        Ok(MdnLicenseApprovedProviderAccessTokenResponse {
            mdn_license_approved_provider_access_token,
        })
    }

    async fn create(
        &self,
        provider_meeid: String,
        ent: ProviderMdnLicenseApplicationWriteRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let dto = ent.into_dto(provider_meeid);
        let conn = self.rdb_storage.connection();
        let res = self
            .provider_mdn_license_service(conn.as_ref())
            .create(dto)
            .await?;

        Ok(res.into())
    }

    async fn get_by_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let conn = self.rdb_storage.connection();
        let res = self
            .provider_mdn_license_service(conn.as_ref())
            .get_by_meeid(provider_meeid, meeid)
            .await?;

        Ok(res.into())
    }

    async fn get_all_by_provider(
        &self,
        provider_meeid: String,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModelResponse>>
    {
        let conn = self.rdb_storage.connection();
        let res = self
            .provider_mdn_license_service(conn.as_ref())
            .get_all_by_provider(provider_meeid, statuses)
            .await?;

        Ok(res.into_iter().map(|x| x.into()).collect())
    }

    async fn update_draft(
        &self,
        provider_meeid: String,
        meeid: String,
        payload: ProviderMdnLicenseApplicationWriteRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let dto = payload.into();
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .update_draft(provider_meeid, meeid, dto)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into())
    }

    async fn to_processing(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .to_processing(provider_meeid, meeid)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into())
    }

    async fn to_canceled(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .to_canceled(provider_meeid, meeid)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into())
    }

    async fn to_approved(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModelResponse>>
    {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .to_approved(provider_meeid, meeid)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into_iter().map(|x| x.into()).collect())
    }

    async fn to_rejected(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .to_rejected(provider_meeid, meeid)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into())
    }

    async fn to_draft(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModelResponse>
    {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let res = this
                        .provider_mdn_license_service(tx)
                        .to_draft(provider_meeid, meeid)
                        .await?;
                    Ok(res)
                })
            })
            .await?;

        Ok(res.into())
    }

    async fn get_all(
        &self,
        payload: ProviderMdnLicenseApplicationListRequest,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationListResponse>
    {
        let conn = self.rdb_storage.connection();
        let request = payload.clone();
        let ModelPage { data, total } = self
            .provider_mdn_license_service(conn.as_ref())
            .get_all(
                payload.limit,
                payload.offset,
                payload.search,
                payload.statuses,
            )
            .await?;

        let data = data.into_iter().map(|x| x.into()).collect();

        Ok(ProviderMdnLicenseApplicationListResponse {
            total,
            data,
            request,
        })
    }

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()> {
        let conn = self.rdb_storage.connection();

        self.provider_mdn_license_service(conn.as_ref())
            .delete(meeid, provider_meeid)
            .await?;

        Ok(())
    }
}
