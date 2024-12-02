use crate::{
    db_models::{mdn_nodes, prelude::*},
    error::MdnCentralResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddMdnNodeDto {
    pub mdn_node_custodian_id: i64,
    pub mdn_node_subject_id: i64,
    pub mdn_node_uid: String,
    pub mdn_node_willow_peer_id: String,
    pub mdn_node_iroh_node_id: String,
}

#[async_trait]
pub trait MdnNodesRepository {
    async fn register_node(
        &self,
        add_node: AddMdnNodeDto,
    ) -> MdnCentralResult<mdn_nodes::Model>;
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCentralResult<Vec<mdn_nodes::Model>>;
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
impl<'a, C: ConnectionTrait> MdnNodesRepository
    for MdnNodesRepositoryImpl<'a, C>
{
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCentralResult<Vec<mdn_nodes::Model>> {
        Ok(MdnNodes::find()
            .filter(mdn_nodes::Column::MdnNodeCustodianId.eq(custodian_id))
            .all(self.db_conn)
            .await?)
    }
    async fn register_node(
        &self,
        AddMdnNodeDto {
            mdn_node_custodian_id,
            mdn_node_uid,
            mdn_node_willow_peer_id,
            mdn_node_iroh_node_id,
            mdn_node_subject_id,
        }: AddMdnNodeDto,
    ) -> MdnCentralResult<mdn_nodes::Model> {
        let res = mdn_nodes::ActiveModel {
            mdn_node_id: NotSet,
            mdn_node_subject_id: Set(mdn_node_subject_id),
            mdn_node_uid: Set(mdn_node_uid),
            mdn_node_willow_peer_id: Set(mdn_node_willow_peer_id),
            mdn_node_iroh_node_id: Set(mdn_node_iroh_node_id),
            mdn_node_custodian_id: Set(mdn_node_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
