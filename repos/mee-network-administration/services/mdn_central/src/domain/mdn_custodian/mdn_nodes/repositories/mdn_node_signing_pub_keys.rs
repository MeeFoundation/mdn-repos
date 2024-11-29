use crate::{db_models::mdn_node_signing_pub_keys, error::MdnCentralResult};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddPubKeyDto {
    pub mdn_node_signing_pub_key_did: String,
    pub mdn_node_id: i64,
}

#[async_trait]
pub trait MdnNodeSigningPubKeysRepository {
    async fn add_pub_key(
        &self,
        add_pub_key: AddPubKeyDto,
    ) -> MdnCentralResult<mdn_node_signing_pub_keys::Model>;
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
impl<'a, C: ConnectionTrait> MdnNodeSigningPubKeysRepository
    for MdnNodeSigningPubKeysRepositoryImpl<'a, C>
{
    async fn add_pub_key(
        &self,
        AddPubKeyDto {
            mdn_node_signing_pub_key_did,
            mdn_node_id,
        }: AddPubKeyDto,
    ) -> MdnCentralResult<mdn_node_signing_pub_keys::Model> {
        let res = mdn_node_signing_pub_keys::ActiveModel {
            mdn_node_signing_pub_key_id: NotSet,
            mdn_node_signing_pub_key_did: Set(mdn_node_signing_pub_key_did),
            mdn_node_id: Set(mdn_node_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
