use crate::{db_models::mdn_user_signing_pub_keys, error::MdnCentralResult};
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
    ) -> MdnCentralResult<mdn_user_signing_pub_keys::Model>;
}

pub struct MdnNodeSigningPubKeysRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnNodeSigningPubKeysRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnUserSigningPubKeysRepository
    for MdnNodeSigningPubKeysRepositoryImpl<'a, C>
{
    async fn add_pub_key(
        &self,
        AddPubKeyDto {
            mdn_user_signing_pub_key_did,
            mdn_custodian_storage_id,
            mdn_user_id,
        }: AddPubKeyDto,
    ) -> MdnCentralResult<mdn_user_signing_pub_keys::Model> {
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
