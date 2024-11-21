use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CreateUserAccountRequest {
    pub email: String,
    pub phone: Option<String>,
    pub password: String,
    pub device_did: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserAccountLoginResponse {
    pub mdn_user_uid: String,
    pub auth_token: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct UserAccountLoginRequest {
    pub email: String,
    pub password: String,
    pub device_did: String,
}
