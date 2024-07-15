use sea_orm::prelude::DateTimeUtc;
use serde::{Deserialize, Serialize};

use super::domain::MdnLicenseApplicationStatus;

#[derive(Debug, Serialize, Deserialize)]
pub struct ProviderMdnLicenseApplicationUpdateDto {
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
    pub status: MdnLicenseApplicationStatus,
    pub created_at: DateTimeUtc,
    pub updated_at: DateTimeUtc,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ProviderMdnLicenseApplicationCreateDto {
    pub provider_meeid: String,
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct ModelPage<T> {
    pub data: Vec<T>,
    pub total: u64,
}
