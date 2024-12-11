use crate::{
    db_models::{mdn_context_scoped_ids, prelude::*},
    error::{MdnCentralErr, MdnCentralResult},
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct CreateScopedIdDto {
    pub mdn_context_scoped_uid: String,
    pub mdn_user_id: i64,
    pub for_mdn_custodian_id: i64,
}

#[async_trait]
pub trait MdnContextScopedIdsRepository {
    async fn create_context_scoped_id(
        &self,
        create_id_dto: CreateScopedIdDto,
    ) -> MdnCentralResult;
    async fn get_context_scoped_id_by_uid(
        &self,
        csi_uid: &str,
    ) -> MdnCentralResult<Option<mdn_context_scoped_ids::Model>>;
    async fn get_context_scoped_id_by_custodian_uid(
        &self,
        mdn_user_id: i64,
        for_custodian_id: i64,
    ) -> MdnCentralResult<Option<mdn_context_scoped_ids::Model>>;
    async fn get_context_scoped_id_by_uid_required(
        &self,
        csi_uid: &str,
    ) -> MdnCentralResult<mdn_context_scoped_ids::Model> {
        Ok(self
            .get_context_scoped_id_by_uid(csi_uid)
            .await?
            .ok_or_else(|| {
                MdnCentralErr::MissingDbEntity(format!("{csi_uid}"))
            })?)
    }
}

pub struct MdnContextScopedIdsRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnContextScopedIdsRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnContextScopedIdsRepository
    for MdnContextScopedIdsRepositoryImpl<'a, C>
{
    async fn create_context_scoped_id(
        &self,
        CreateScopedIdDto {
            mdn_context_scoped_uid,
            mdn_user_id,
            for_mdn_custodian_id,
        }: CreateScopedIdDto,
    ) -> MdnCentralResult {
        mdn_context_scoped_ids::ActiveModel {
            mdn_context_scoped_id: NotSet,
            mdn_context_scoped_uid: Set(mdn_context_scoped_uid),
            mdn_user_id: Set(mdn_user_id),
            for_mdn_custodian_id: Set(for_mdn_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(())
    }
    async fn get_context_scoped_id_by_uid(
        &self,
        csi_uid: &str,
    ) -> MdnCentralResult<Option<mdn_context_scoped_ids::Model>> {
        let res = MdnContextScopedIds::find()
            .filter(
                mdn_context_scoped_ids::Column::MdnContextScopedUid.eq(csi_uid),
            )
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_context_scoped_id_by_custodian_uid(
        &self,
        mdn_user_id: i64,
        for_custodian_id: i64,
    ) -> MdnCentralResult<Option<mdn_context_scoped_ids::Model>> {
        let res = MdnContextScopedIds::find()
            .filter(
                mdn_context_scoped_ids::Column::ForMdnCustodianId
                    .eq(for_custodian_id)
                    .and(
                        mdn_context_scoped_ids::Column::MdnUserId
                            .eq(mdn_user_id),
                    ),
            )
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}
