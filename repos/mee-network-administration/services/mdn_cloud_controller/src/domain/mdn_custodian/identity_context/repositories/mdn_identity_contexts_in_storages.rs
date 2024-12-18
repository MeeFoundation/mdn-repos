use crate::{
    db_models::mdn_identity_contexts_in_storages,
    error::MdnCloudControllerResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct CreateMdnContextInStorageDto {
    pub mdn_identity_context_id: i64,
    pub mdn_custodian_storage_id: i64,
}

#[async_trait]
pub trait MdnContextInStorageRepository {
    async fn link_context_to_storage(
        &self,
        payload: CreateMdnContextInStorageDto,
    ) -> MdnCloudControllerResult<mdn_identity_contexts_in_storages::Model>;
}

pub struct MdnContextInStorageRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnContextInStorageRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnContextInStorageRepository
    for MdnContextInStorageRepositoryImpl<'a, C>
{
    async fn link_context_to_storage(
        &self,
        CreateMdnContextInStorageDto {
            mdn_identity_context_id,
            mdn_custodian_storage_id,
        }: CreateMdnContextInStorageDto,
    ) -> MdnCloudControllerResult<mdn_identity_contexts_in_storages::Model>
    {
        let res = mdn_identity_contexts_in_storages::ActiveModel {
            mdn_identity_context_in_storage_id: NotSet,
            mdn_identity_context_in_storage_uid: Set(format!(
                "mdn-ctx-in-storage-{}",
                uuid::Uuid::new_v4()
            )),
            mdn_identity_context_id: Set(mdn_identity_context_id),
            mdn_custodian_storage_id: Set(mdn_custodian_storage_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
