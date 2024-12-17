use crate::{
    db_models::{mdn_custodian_storages, prelude::*},
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddMdnCustodianStorageDto {
    pub mdn_custodian_storage_did: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
    pub mdn_custodian_id: i64,
}

#[async_trait]
pub trait MdnCustodianStoragesRepository {
    async fn register_custodian_storage(
        &self,
        add_node_platform: AddMdnCustodianStorageDto,
    ) -> MdnCloudControllerResult<mdn_custodian_storages::Model>;
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_custodian_storages::Model>>;
    async fn get_custodian_storage_by_did(
        &self,
        custodian_id: i64,
        custodian_storage_did: &str,
    ) -> MdnCloudControllerResult<Option<mdn_custodian_storages::Model>>;
    async fn get_custodian_storage_by_did_required(
        &self,
        custodian_id: i64,
        custodian_storage_did: &str,
    ) -> MdnCloudControllerResult<mdn_custodian_storages::Model> {
        self.get_custodian_storage_by_did(custodian_id, custodian_storage_did)
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MissingDbEntity(format!(
                    "{custodian_storage_did}"
                ))
            })
    }
}

pub struct MdnCustodianStoragesRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnCustodianStoragesRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnCustodianStoragesRepository
    for MdnCustodianStoragesRepositoryImpl<'a, C>
{
    async fn list_all(
        &self,
        custodian_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_custodian_storages::Model>> {
        Ok(MdnCustodianStorages::find()
            .filter(
                mdn_custodian_storages::Column::MdnCustodianId.eq(custodian_id),
            )
            .all(self.db_conn)
            .await?)
    }
    async fn get_custodian_storage_by_did(
        &self,
        custodian_id: i64,
        custodian_storage_did: &str,
    ) -> MdnCloudControllerResult<Option<mdn_custodian_storages::Model>> {
        Ok(MdnCustodianStorages::find()
            .filter(
                mdn_custodian_storages::Column::MdnCustodianStorageDid
                    .eq(custodian_storage_did)
                    .and(
                        mdn_custodian_storages::Column::MdnCustodianId
                            .eq(custodian_id),
                    ),
            )
            .one(self.db_conn)
            .await?)
    }
    async fn register_custodian_storage(
        &self,
        AddMdnCustodianStorageDto {
            mdn_custodian_storage_did,
            willow_peer_id,
            iroh_node_id,
            mdn_custodian_id,
        }: AddMdnCustodianStorageDto,
    ) -> MdnCloudControllerResult<mdn_custodian_storages::Model> {
        let res = mdn_custodian_storages::ActiveModel {
            mdn_custodian_storage_id: NotSet,
            mdn_custodian_storage_uid: Set(format!(
                "mdn_custodian_storage-{}",
                uuid::Uuid::new_v4()
            )),
            mdn_custodian_storage_did: Set(mdn_custodian_storage_did),
            willow_peer_id: Set(willow_peer_id),
            iroh_node_id: Set(iroh_node_id),
            mdn_custodian_id: Set(mdn_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
