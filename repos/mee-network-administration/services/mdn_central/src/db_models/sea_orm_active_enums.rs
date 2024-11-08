//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(
    Debug, Clone, PartialEq, Eq, EnumIter, DeriveActiveEnum, Serialize,
)]
#[sea_orm(
    rs_type = "String",
    db_type = "Enum",
    enum_name = "mdn_user_account_role"
)]
pub enum MdnUserAccountRole {
    #[sea_orm(string_value = "Admin")]
    Admin,
    #[sea_orm(string_value = "Client")]
    Client,
}
