use crate::{db_models, error::MdnCloudControllerErr};
use sea_orm::{entity::prelude::*, DeriveActiveEnum};
use serde::{Deserialize, Serialize};
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
pub enum MdnUserAccountRole {
    #[sea_orm(string_value = "Admin")]
    Admin,
    #[sea_orm(string_value = "Customer")]
    Customer,
}

#[derive(Debug)]
pub struct UserAccountDomainModel {
    pub mdn_user_uid: String,
    pub mdn_user_role: MdnUserAccountRole,
    pub _mdn_user_email: String,
    pub _mdn_user_phone: Option<String>,
    pub _mdn_user_name: Option<String>,
}

impl TryFrom<db_models::mdn_users::Model> for UserAccountDomainModel {
    type Error = MdnCloudControllerErr;

    fn try_from(
        db_models::mdn_users::Model {
            mdn_user_uid,
            mdn_user_email,
            mdn_user_phone,
            mdn_user_name,
            mdn_user_role,
            ..
        }: db_models::mdn_users::Model,
    ) -> Result<Self, Self::Error> {
        Ok(Self {
            mdn_user_uid,
            _mdn_user_email: mdn_user_email,
            mdn_user_role: mdn_user_role.parse()?,
            _mdn_user_phone: mdn_user_phone,
            _mdn_user_name: mdn_user_name,
        })
    }
}
