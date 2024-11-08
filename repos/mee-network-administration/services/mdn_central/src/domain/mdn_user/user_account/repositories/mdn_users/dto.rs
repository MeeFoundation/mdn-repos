use crate::domain::mdn_user::user_account::services::auth::service_models::MdnUserAccountRole;

#[derive(Debug)]
pub struct CreateUserAccountDto {
    pub mdn_user_uid: String,
    pub mdn_user_email: String,
    pub mdn_user_phone: Option<String>,
    pub mdn_user_name: Option<String>,
    pub mdn_user_role: MdnUserAccountRole,
    pub is_user_active: bool,
    pub is_user_verified: bool,
    pub salt: String,
    pub password: String,
}
