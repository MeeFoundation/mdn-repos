use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CreateProviderAccountRequest {
    pub email: String,
    pub password: String,
    pub provider_name: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ProviderAccountLoginRequest {
    pub email: String,
    pub password: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ProviderAccountLoginResponse {
    pub meeid: String,
    pub auth_token: String,
}
