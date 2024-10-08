//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "provider_cloud_nodes")]
pub struct Model {
    #[sea_orm(primary_key, auto_increment = false)]
    pub cloud_node_id: i32,
    pub cloud_node_uid: String,
    pub cloud_node_discovery_url: String,
    pub cloud_node_did: String,
    pub provider_id: i32,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {
    #[sea_orm(
        belongs_to = "super::mee_network_providers::Entity",
        from = "Column::ProviderId",
        to = "super::mee_network_providers::Column::ProviderId",
        on_update = "NoAction",
        on_delete = "NoAction"
    )]
    MeeNetworkProviders,
}

impl Related<super::mee_network_providers::Entity> for Entity {
    fn to() -> RelationDef {
        Relation::MeeNetworkProviders.def()
    }
}

impl ActiveModelBehavior for ActiveModel {}
