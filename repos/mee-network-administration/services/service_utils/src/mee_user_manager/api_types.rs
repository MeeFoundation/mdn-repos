use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

pub const AUTHORIZE_USER_PATH: &str = "authorize";

#[derive(Serialize, Deserialize, ToSchema)]
pub struct AuthorizeUserRequest {
    pub auth_token: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct AuthorizeUserResponse {
    pub user_meeid: String,
    pub user_email: String,
}
