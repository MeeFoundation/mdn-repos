use crate::{
    db_models::{mdn_node_hosting_platforms, prelude::*},
    error::MdnCentralResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddMdnNodeHostingPlatformDto {
    pub mdn_node_hosting_platform_uid: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub mdn_custodian_id: i64,
}

#[async_trait]
pub trait MdnNodeHostingPlatformsRepository {
    async fn register_node_platform(
        &self,
        add_node_platform: AddMdnNodeHostingPlatformDto,
    ) -> MdnCentralResult<mdn_node_hosting_platforms::Model>;
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCentralResult<Vec<mdn_node_hosting_platforms::Model>>;
}

pub struct MdnNodesRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnNodesRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnNodeHostingPlatformsRepository
    for MdnNodesRepositoryImpl<'a, C>
{
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCentralResult<Vec<mdn_node_hosting_platforms::Model>> {
        Ok(MdnNodeHostingPlatforms::find()
            .filter(
                mdn_node_hosting_platforms::Column::MdnCustodianId
                    .eq(custodian_id),
            )
            .all(self.db_conn)
            .await?)
    }
    async fn register_node_platform(
        &self,
        AddMdnNodeHostingPlatformDto {
            mdn_node_hosting_platform_uid,
            willow_peer_id,
            iroh_node_id,
            mdn_custodian_id,
        }: AddMdnNodeHostingPlatformDto,
    ) -> MdnCentralResult<mdn_node_hosting_platforms::Model> {
        let res = mdn_node_hosting_platforms::ActiveModel {
            mdn_node_hosting_platform_id: NotSet,
            mdn_node_hosting_platform_uid: Set(mdn_node_hosting_platform_uid),
            willow_peer_id: Set(willow_peer_id),
            iroh_node_id: Set(iroh_node_id),
            mdn_custodian_id: Set(mdn_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
