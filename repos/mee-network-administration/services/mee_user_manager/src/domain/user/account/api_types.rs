use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CreateUserAccountRequest {
    pub email: String,
    pub phone: Option<String>,
    pub password: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserAccountLoginRequest {
    pub email: String,
    pub password: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserAccountLoginResponse {
    pub meeid: String,
    pub auth_token: String,
}
