//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "mdn_node_willow_caps")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub mdn_node_willow_cap_id: i64,
    #[sea_orm(unique)]
    pub mdn_node_willow_cap_uid: String,
    pub mdn_node_willow_cap_token: String,
    pub mdn_custodian_cap_id: i64,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(
        belongs_to = "super::mdn_custodian_caps::Entity",
        from = "Column::MdnCustodianCapId",
        to = "super::mdn_custodian_caps::Column::MdnCustodianCapId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MdnCustodianCaps,
    #[sea_orm(has_many = "super::mdn_identity_contexts::Entity")]
    MdnIdentityContexts,
}

impl Related<super::mdn_custodian_caps::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnCustodianCaps.def()
    }
}

impl Related<super::mdn_identity_contexts::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnIdentityContexts.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}
