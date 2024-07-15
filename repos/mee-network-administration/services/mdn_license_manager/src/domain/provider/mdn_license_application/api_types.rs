use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

use super::{
    domain::{
        MdnLicenseApplicationStatus, ProviderMdnLicenseApplicationModel,
        ProviderMdnLicenseApplicationUpdateModel,
    },
    dto::ProviderMdnLicenseApplicationCreateDto,
};

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct MdnLicenseApprovedProviderAccessTokenRequest {
    pub provider_node_ssi_jwt: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct MdnLicenseApprovedProviderAccessTokenResponse {
    pub mdn_license_approved_provider_access_token: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct ProviderMdnLicenseApplicationWriteRequest {
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
}
impl ProviderMdnLicenseApplicationWriteRequest {
    pub fn into_dto(
        self,
        provider_meeid: String,
    ) -> ProviderMdnLicenseApplicationCreateDto {
        ProviderMdnLicenseApplicationCreateDto {
            provider_meeid,
            contact_email: self.contact_email,
            company_name: self.company_name,
            company_uri: self.company_uri,
            cloud_node_discovery_url: self.cloud_node_discovery_url,
            decentralized_id: self.decentralized_id,
        }
    }
}
impl From<ProviderMdnLicenseApplicationWriteRequest>
    for ProviderMdnLicenseApplicationUpdateModel
{
    fn from(val: ProviderMdnLicenseApplicationWriteRequest) -> Self {
        ProviderMdnLicenseApplicationUpdateModel {
            contact_email: val.contact_email,
            company_name: val.company_name,
            company_uri: val.company_uri,
            cloud_node_discovery_url: val.cloud_node_discovery_url,
            decentralized_id: val.decentralized_id,
        }
    }
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct ProviderMdnLicenseApplicationModelResponse {
    pub meeid: String,
    pub provider_meeid: String,
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
    pub status: MdnLicenseApplicationStatus,
    pub created_at: i64,
    pub updated_at: i64,
}

impl From<ProviderMdnLicenseApplicationModel>
    for ProviderMdnLicenseApplicationModelResponse
{
    fn from(
        ProviderMdnLicenseApplicationModel {
            meeid,
            provider_meeid,
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
            status,
            created_at,
            updated_at,
        }: ProviderMdnLicenseApplicationModel,
    ) -> Self {
        Self {
            meeid,
            provider_meeid,
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
            status,
            created_at: created_at.timestamp(),
            updated_at: updated_at.timestamp(),
        }
    }
}

#[derive(Debug, Deserialize, Serialize, ToSchema, Clone)]
pub struct ProviderMdnLicenseApplicationListRequest {
    pub limit: Option<u64>,
    pub offset: Option<u64>,
    ///search by contact_email, company_name, company_uri, cloud_node_discovery_url, decentralized_id
    pub search: Option<String>,
    pub statuses: Option<Vec<MdnLicenseApplicationStatus>>,
}

#[derive(Debug, Deserialize, Serialize, ToSchema)]
pub struct ProviderMdnLicenseApplicationListResponse {
    pub data: Vec<ProviderMdnLicenseApplicationModelResponse>,
    pub total: u64,
    pub request: ProviderMdnLicenseApplicationListRequest,
}

#[derive(Debug, Deserialize, Serialize, ToSchema)]
pub struct StatusesQueryParam {
    pub statuses: Option<Vec<MdnLicenseApplicationStatus>>,
}
