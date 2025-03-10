//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "mdn_custodian_context_operation_caps")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub mdn_custodian_context_operation_cap_id: i64,
    #[sea_orm(unique)]
    pub mdn_custodian_context_operation_cap_uid: String,
    pub mdn_custodian_context_operation_cap_token: String,
    pub mdn_custodian_context_operation_cap_expires: DateTimeWithTimeZone,
    pub from_mdn_user_id: i64,
    pub to_mdn_custodian_id: i64,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(
        belongs_to = "super::mdn_custodians::Entity",
        from = "Column::ToMdnCustodianId",
        to = "super::mdn_custodians::Column::MdnCustodianId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MdnCustodians,
    #[sea_orm(
        belongs_to = "super::mdn_users::Entity",
        from = "Column::FromMdnUserId",
        to = "super::mdn_users::Column::MdnUserId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MdnUsers,
}

impl Related<super::mdn_custodians::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnCustodians.def()
    }
}

impl Related<super::mdn_users::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnUsers.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}
