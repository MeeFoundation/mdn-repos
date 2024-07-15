use crate::db_models::mee_network_users;
use sea_orm::{entity::prelude::*, DeriveActiveEnum};
use serde::{Deserialize, Serialize};
use service_utils::mee_user_manager::api_types::AuthorizeUserResponse;
use strum_macros::{Display, EnumString};
use utoipa::ToSchema;

#[derive(
    Debug,
    Serialize,
    Deserialize,
    ToSchema,
    PartialEq,
    Clone,
    Display,
    EnumString,
    EnumIter,
    DeriveActiveEnum,
    Eq,
)]
#[sea_orm(rs_type = "String", db_type = "String(None)")]
pub enum UserRole {
    #[sea_orm(string_value = "Admin")]
    Admin,
    #[sea_orm(string_value = "Customer")]
    Customer,
}

#[derive(Debug)]
pub struct UserAccountDomainModel {
    pub user_meeid: String,
    pub user_email: String,
    pub user_role: UserRole,
    pub user_phone: Option<String>,
    pub is_active: bool,
}

impl From<mee_network_users::Model> for AuthorizeUserResponse {
    fn from(
        mee_network_users::Model {
            user_meeid,
            user_email,
            ..
        }: mee_network_users::Model,
    ) -> Self {
        Self {
            user_meeid,
            user_email,
        }
    }
}
