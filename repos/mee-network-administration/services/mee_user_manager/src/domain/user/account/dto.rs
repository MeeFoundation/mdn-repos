use super::domain::UserRole;

#[derive(Debug)]
pub struct CreateUserAccountDto {
    pub user_meeid: String,
    pub user_email: String,
    pub user_role: UserRole,
    pub user_phone: Option<String>,
    pub is_active: bool,
    pub salt: String,
    pub password: String,
}
