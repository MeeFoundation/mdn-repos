use crate::{
    db_models::{mdn_user_signing_pub_keys, prelude::*},
    error::MdnCloudControllerResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddPubKeyDto {
    pub mdn_user_signing_pub_key_did: String,
    pub mdn_custodian_storage_id: Option<i64>,
    pub mdn_user_id: i64,
}

#[async_trait]
pub trait MdnUserSigningPubKeysRepository {
    async fn add_pub_key(
        &self,
        add_pub_key: AddPubKeyDto,
    ) -> MdnCloudControllerResult<mdn_user_signing_pub_keys::Model>;
    async fn list_pub_keys(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_user_signing_pub_keys::Model>>;
}

pub struct MdnUserSigningPubKeysRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnUserSigningPubKeysRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnUserSigningPubKeysRepository
    for MdnUserSigningPubKeysRepositoryImpl<'a, C>
{
    async fn list_pub_keys(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_user_signing_pub_keys::Model>> {
        Ok(MdnUserSigningPubKeys::find()
            .filter(
                mdn_user_signing_pub_keys::Column::MdnUserId.eq(mdn_user_id),
            )
            .all(self.db_conn)
            .await?)
    }
    async fn add_pub_key(
        &self,
        AddPubKeyDto {
            mdn_user_signing_pub_key_did,
            mdn_custodian_storage_id,
            mdn_user_id,
        }: AddPubKeyDto,
    ) -> MdnCloudControllerResult<mdn_user_signing_pub_keys::Model> {
        let res = mdn_user_signing_pub_keys::ActiveModel {
            mdn_user_signing_pub_key_id: NotSet,
            mdn_user_signing_pub_key_did: Set(mdn_user_signing_pub_key_did),
            mdn_custodian_storage_id: Set(mdn_custodian_storage_id),
            mdn_user_id: Set(mdn_user_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
