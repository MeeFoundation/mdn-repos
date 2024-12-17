use crate::{
    db_models::{mdn_custodians, prelude::*},
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct CreateUserCustodianAccountDto {
    pub mdn_custodian_uid: String,
    pub mdn_user_custodian_id: i64,
}

#[async_trait]
pub trait MdnCustodiansRepository {
    async fn create_user_custodian_account(
        &self,
        create_dto: CreateUserCustodianAccountDto,
    ) -> MdnCloudControllerResult<mdn_custodians::Model>;
    async fn _create_provider_custodian_account(
        &self,
    ) -> MdnCloudControllerResult<mdn_custodians::Model>;
    async fn get_user_custodian(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Option<mdn_custodians::Model>>;
    async fn get_custodian_by_uid(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<Option<mdn_custodians::Model>>;
    async fn get_custodian_by_uid_required(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        self.get_custodian_by_uid(mdn_custodian_uid)
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MissingDbEntity(format!(
                    "Custodian ({mdn_custodian_uid})"
                ))
            })
    }
}

pub struct MdnCustodiansRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnCustodiansRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnCustodiansRepository
    for MdnCustodiansRepositoryImpl<'a, C>
{
    async fn get_custodian_by_uid(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<Option<mdn_custodians::Model>> {
        let res = MdnCustodians::find()
            .filter(
                mdn_custodians::Column::MdnCustodianUid.eq(mdn_custodian_uid),
            )
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_user_custodian(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Option<mdn_custodians::Model>> {
        let res = MdnCustodians::find()
            .filter(mdn_custodians::Column::MdnUserCustodianId.eq(mdn_user_id))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn create_user_custodian_account(
        &self,
        CreateUserCustodianAccountDto {
            mdn_custodian_uid,
            mdn_user_custodian_id,
        }: CreateUserCustodianAccountDto,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        let res = mdn_custodians::ActiveModel {
            mdn_custodian_id: NotSet,
            mdn_custodian_uid: Set(mdn_custodian_uid),
            mdn_user_custodian_id: Set(Some(mdn_user_custodian_id)),
            mdn_provider_custodian_id: Set(None),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
    async fn _create_provider_custodian_account(
        &self,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        todo!()
    }
}
