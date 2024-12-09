//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "mdn_providers")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub mdn_provider_id: i64,
    #[sea_orm(unique)]
    pub mdn_provider_uid: String,
    #[sea_orm(unique)]
    pub mdn_provider_email: String,
    pub mdn_provider_name: Option<String>,
    pub mdn_provider_role: String,
    pub mdn_provider_created_at: DateTimeWithTimeZone,
    pub is_provider_active: bool,
    pub is_provider_verified: bool,
    pub salt: String,
    pub password: String,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(has_many = "super::mdn_custodians::Entity")]
    MdnCustodians,
}

impl Related<super::mdn_custodians::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnCustodians.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}
