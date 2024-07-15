use service_utils::mee_provider_manager::domain::ProviderRole;

#[derive(Debug)]
pub struct CreateProviderAccountDto {
    pub provider_meeid: String,
    pub provider_email: String,
    pub provider_role: ProviderRole,
    pub provider_name: String,
    pub is_active: bool,
    pub salt: String,
    pub password: String,
}
