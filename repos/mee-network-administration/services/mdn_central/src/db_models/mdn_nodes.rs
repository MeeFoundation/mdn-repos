//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "mdn_nodes")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub mdn_node_id: i64,
    #[sea_orm(unique)]
    pub mdn_node_uid: String,
    pub mdn_node_willow_peer_id: String,
    pub mdn_node_iroh_node_id: String,
    pub mdn_node_subject_id: i64,
    pub mdn_node_custodian_id: i64,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(
        belongs_to = "super::mdn_custodians::Entity",
        from = "Column::MdnNodeCustodianId",
        to = "super::mdn_custodians::Column::MdnCustodianId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MdnCustodians,
    #[sea_orm(has_many = "super::mdn_identity_contexts_on_nodes::Entity")]
    MdnIdentityContextsOnNodes,
    #[sea_orm(has_many = "super::mdn_node_signing_pub_keys::Entity")]
    MdnNodeSigningPubKeys,
    #[sea_orm(
        belongs_to = "super::mdn_users::Entity",
        from = "Column::MdnNodeSubjectId",
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

impl Related<super::mdn_identity_contexts_on_nodes::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnIdentityContextsOnNodes.def()
    }
}

impl Related<super::mdn_node_signing_pub_keys::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnNodeSigningPubKeys.def()
    }
}

impl Related<super::mdn_users::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MdnUsers.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}
