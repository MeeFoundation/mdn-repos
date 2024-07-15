use super::domain::{
    ApprovedProviderMdnLicenseAccessToken, MdnLicenseApplicationStatus,
    ProviderMdnLicenseApplicationModel,
    ProviderMdnLicenseApplicationUpdateModel, ProviderNodeSsiJwt,
};
use super::dto::{ModelPage, ProviderMdnLicenseApplicationCreateDto};
use super::repository::ProviderMdnLicenseApplicationRepo;
use crate::error::{MdnLicenseManagerErr, MdnLicenseManagerResult};
use chrono::{DateTime, Utc};
use service_utils::mee_provider_manager::client::MeeProviderManagerServiceClient;
use uuid::Uuid;

use std::sync::Arc;
use std::vec;

#[async_trait::async_trait]
pub trait ProviderMdnLicenseService {
    async fn issued_mdn_license_approved_provider_access_token(
        &self,
        request: ProviderNodeSsiJwt,
    ) -> MdnLicenseManagerResult<ApprovedProviderMdnLicenseAccessToken>;

    async fn create(
        &self,
        ent: ProviderMdnLicenseApplicationCreateDto,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn get_by_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn get_all_by_provider(
        &self,
        provider_meeid: String,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>>;

    async fn update_draft(
        &self,
        provider_meeid: String,
        meeid: String,
        ent: ProviderMdnLicenseApplicationUpdateModel,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn to_processing(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn to_canceled(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn to_approved(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>>;

    async fn to_rejected(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn to_draft(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn get_all(
        &self,
        limit: Option<u64>,
        offset: Option<u64>,
        search: Option<String>,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<ModelPage<ProviderMdnLicenseApplicationModel>>;

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()>;
}

pub struct ProviderMdnLicenseServiceImpl<'a> {
    mee_provider_manager_service_client:
        Arc<dyn MeeProviderManagerServiceClient + Send + Sync>,
    provider_mdn_license_application_repo:
        Box<dyn ProviderMdnLicenseApplicationRepo + Send + Sync + 'a>,
}

impl<'a> ProviderMdnLicenseServiceImpl<'a> {
    pub fn new(
        mee_provider_manager_service_client: Arc<
            dyn MeeProviderManagerServiceClient + Send + Sync,
        >,
        provider_mdn_license_application_repo: Box<
            dyn ProviderMdnLicenseApplicationRepo + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            mee_provider_manager_service_client,
            provider_mdn_license_application_repo,
        }
    }

    async fn update(
        &self,
        provider_meeid: String,
        meeid: String,
        action: impl FnOnce(
            &mut ProviderMdnLicenseApplicationModel,
        ) -> MdnLicenseManagerResult<()>,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let repo = self.provider_mdn_license_application_repo.as_ref();
        let mut application = repo
            .get_by_provider_and_meeid(provider_meeid.clone(), meeid.clone())
            .await?;

        action(&mut application)?;

        repo.update(application).await?;

        let application = repo
            .get_by_provider_and_meeid(provider_meeid, meeid)
            .await?;

        Ok(application)
    }
}

#[async_trait::async_trait]
impl<'a> ProviderMdnLicenseService for ProviderMdnLicenseServiceImpl<'a> {
    async fn issued_mdn_license_approved_provider_access_token(
        &self,
        request: ProviderNodeSsiJwt,
    ) -> MdnLicenseManagerResult<ApprovedProviderMdnLicenseAccessToken> {
        // TODO: extract provider ID from provider's cloud node signed JWT and check its HIL-compliance
        tracing::debug!("Checking input request: {}. OK.", request);

        let provider_meeid = "provider_meeid".to_string();
        let provider_cloud_node_did = "provider_cloud_node_did".to_string();

        if !self
            .mee_provider_manager_service_client
            .is_cloud_node_linked_with_provider(
                provider_meeid.clone(),
                provider_cloud_node_did.clone(),
            )
            .await?
        {
            return Err(MdnLicenseManagerErr::ProviderLinkDidNotFound(
                provider_cloud_node_did,
                provider_meeid,
            ));
        };

        // TODO: add real issuance
        let res = "mdn_license_approved_provider_access_token".to_string();

        Ok(res)
    }

    async fn create(
        &self,
        ProviderMdnLicenseApplicationCreateDto {
            provider_meeid,
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
        }: ProviderMdnLicenseApplicationCreateDto,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        self.mee_provider_manager_service_client
            .get_provider_by_id(provider_meeid.clone())
            .await?;

        let dt: DateTime<Utc> = Utc::now();

        let domain = ProviderMdnLicenseApplicationModel {
            meeid: Uuid::new_v4().to_string(),
            created_at: dt,
            updated_at: dt,
            provider_meeid,
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
            status: MdnLicenseApplicationStatus::Draft,
        };

        let res = self
            .provider_mdn_license_application_repo
            .create(domain)
            .await?;

        Ok(res)
    }

    async fn get_by_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let res = self
            .provider_mdn_license_application_repo
            .get_by_provider_and_meeid(provider_meeid, meeid)
            .await?;

        Ok(res)
    }

    async fn get_all_by_provider(
        &self,
        provider_meeid: String,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>> {
        let res = self
            .provider_mdn_license_application_repo
            .find_all_by_provider(&provider_meeid, statuses)
            .await?;

        Ok(res)
    }

    async fn update_draft(
        &self,
        provider_meeid: String,
        meeid: String,
        ent: ProviderMdnLicenseApplicationUpdateModel,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let application = self
            .update(provider_meeid, meeid, |application| {
                application.update(ent)
            })
            .await?;

        Ok(application)
    }

    async fn to_processing(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let application = self
            .update(provider_meeid, meeid, |application| {
                application.to_processing()
            })
            .await?;

        Ok(application)
    }

    async fn to_canceled(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let application = self
            .update(provider_meeid, meeid, |application| {
                application.to_canceled()
            })
            .await?;

        Ok(application)
    }

    async fn to_approved(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>> {
        let mut application = self
            .provider_mdn_license_application_repo
            .get_by_provider_and_meeid(provider_meeid.clone(), meeid.clone())
            .await?;

        let approved_applications = self
            .provider_mdn_license_application_repo
            .find_all_by_provider(
                &provider_meeid,
                Some(vec![MdnLicenseApplicationStatus::Approved]),
            )
            .await?;

        application.to_processing()?;
        self.provider_mdn_license_application_repo
            .update(application)
            .await?;

        for mut old in approved_applications.into_iter() {
            old.to_discontinued()?;
            self.provider_mdn_license_application_repo
                .update(old)
                .await?;
        }

        let all_applications = self
            .provider_mdn_license_application_repo
            .find_all_by_provider(&provider_meeid, None)
            .await?;

        Ok(all_applications)
    }

    async fn to_rejected(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let application = self
            .update(provider_meeid, meeid, |application| {
                application.to_rejected()
            })
            .await?;

        Ok(application)
    }

    async fn to_draft(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let application = self
            .update(provider_meeid, meeid, |application| application.to_draft())
            .await?;

        Ok(application)
    }

    async fn get_all(
        &self,
        limit: Option<u64>,
        offset: Option<u64>,
        search: Option<String>,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<ModelPage<ProviderMdnLicenseApplicationModel>>
    {
        let res = self
            .provider_mdn_license_application_repo
            .find_all(limit, offset, search, statuses)
            .await?;

        Ok(res)
    }

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()> {
        self.provider_mdn_license_application_repo
            .delete(provider_meeid, meeid)
            .await?;
        Ok(())
    }
}
