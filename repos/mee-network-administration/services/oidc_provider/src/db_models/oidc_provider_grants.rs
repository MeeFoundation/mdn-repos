//! `SeaORM` Entity. Generated by sea-orm-codegen 0.12.15

use sea_orm::entity::prelude::*;
use serde::Serialize;

#[derive(Clone, Debug, PartialEq, DeriveEntityModel, Eq, Serialize)]
#[sea_orm(table_name = "oidc_provider_grants")]
pub struct Model {
    #[sea_orm(primary_key, auto_increment = false)]
    pub record_id: i32,
    pub grant_code: String,
    pub client_id: String,
    pub owner_id: String,
    pub scope: String,
    pub redirect_uri: String,
    pub until: String,
}

#[derive(Copy, Clone, Debug, EnumIter, DeriveRelation)]
pub enum Relation {}

impl ActiveModelBehavior for ActiveModel {}
