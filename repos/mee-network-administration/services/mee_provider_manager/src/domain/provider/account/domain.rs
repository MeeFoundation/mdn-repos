use crate::db_models::mee_network_providers;
use service_utils::mee_provider_manager::{
    api_types::ProviderAccountInfoResponse, domain::ProviderRole,
};

#[derive(Debug)]
pub struct ProviderAccountDomainModel {
    pub provider_meeid: String,
    pub provider_email: String,
    pub provider_name: String,
    pub provider_role: ProviderRole,
    pub is_active: bool,
}

impl From<mee_network_providers::Model> for ProviderAccountInfoResponse {
    fn from(
        mee_network_providers::Model {
            provider_meeid,
            provider_email,
            provider_name,
            ..
        }: mee_network_providers::Model,
    ) -> Self {
        Self {
            provider_meeid,
            provider_email,
            provider_name,
        }
    }
}
