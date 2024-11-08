use crate::db_models;
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
    pub mdn_user_uid: String,
    pub auth_token: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct AuthorizeUserResponse {
    pub mdn_user_uid: String,
    pub mdn_user_email: String,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct AuthorizeUserRequest {
    pub auth_token: String,
}

impl From<db_models::mdn_users::Model> for AuthorizeUserResponse {
    fn from(
        db_models::mdn_users::Model {
            mdn_user_uid,
            mdn_user_email,
            ..
        }: db_models::mdn_users::Model,
    ) -> Self {
        Self {
            mdn_user_uid,
            mdn_user_email,
        }
    }
}
