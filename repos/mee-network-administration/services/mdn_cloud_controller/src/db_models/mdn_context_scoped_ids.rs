//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "mdn_context_scoped_ids")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub mdn_context_scoped_id: i64,
    #[sea_orm(unique)]
    pub mdn_context_scoped_uid: String,
    pub mdn_user_id: i64,
    pub for_mdn_custodian_id: i64,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(
        belongs_to = "super::mdn_custodians::Entity",
        from = "Column::ForMdnCustodianId",
        to = "super::mdn_custodians::Column::MdnCustodianId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MdnCustodians,
    #[sea_orm(has_many = "super::mdn_identity_contexts::Entity")]
    MdnIdentityContexts,
    #[sea_orm(
        belongs_to = "super::mdn_users::Entity",
        from = "Column::MdnUserId",
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

impl Related<super::mdn_identity_contexts::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnIdentityContexts.def()
    }
}

impl Related<super::mdn_users::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnUsers.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}