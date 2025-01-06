use crate::{
    db_models::{mdn_custodian_context_operation_caps, prelude::*},
    error::MdnCloudControllerResult,
};
use async_trait::async_trait;
use chrono::{DateTime, FixedOffset};
use sea_orm::{entity::*, query::*};

pub struct AddCustodianContextOperationCapsDto {
    pub mdn_custodian_context_operation_cap_uid: String,
    pub mdn_custodian_context_operation_cap_token: String,
    pub mdn_custodian_context_operation_cap_expires: DateTime<FixedOffset>,
    pub from_mdn_user_id: i64,
    pub to_mdn_custodian_id: i64,
}

#[async_trait]
pub trait CustodianContextOperationCapsRepository {
    async fn add_cap(
        &self,
        cap: AddCustodianContextOperationCapsDto,
    ) -> MdnCloudControllerResult<mdn_custodian_context_operation_caps::Model>;
    async fn list_issued_caps(
        &self,
        user_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_custodian_context_operation_caps::Model>>;
}

pub struct CustodianContextOperationCapsRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait>
    CustodianContextOperationCapsRepositoryImpl<'a, C>
{
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> CustodianContextOperationCapsRepository
    for CustodianContextOperationCapsRepositoryImpl<'a, C>
{
    async fn list_issued_caps(
        &self,
        user_id: i64,
    ) -> MdnCloudControllerResult<Vec<mdn_custodian_context_operation_caps::Model>>
    {
        let res = MdnCustodianContextOperationCaps::find()
            .filter(
                mdn_custodian_context_operation_caps::Column::FromMdnUserId
                    .eq(user_id),
            )
            .all(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn add_cap(
        &self,
        AddCustodianContextOperationCapsDto {
            mdn_custodian_context_operation_cap_uid,
            mdn_custodian_context_operation_cap_token,
            mdn_custodian_context_operation_cap_expires,
            from_mdn_user_id,
            to_mdn_custodian_id,
        }: AddCustodianContextOperationCapsDto,
    ) -> MdnCloudControllerResult<mdn_custodian_context_operation_caps::Model> {
        let res = mdn_custodian_context_operation_caps::ActiveModel {
            mdn_custodian_context_operation_cap_id: NotSet,
            mdn_custodian_context_operation_cap_uid: Set(
                mdn_custodian_context_operation_cap_uid,
            ),
            mdn_custodian_context_operation_cap_token: Set(
                mdn_custodian_context_operation_cap_token,
            ),
            mdn_custodian_context_operation_cap_expires: Set(
                mdn_custodian_context_operation_cap_expires,
            ),
            from_mdn_user_id: Set(from_mdn_user_id),
            to_mdn_custodian_id: Set(to_mdn_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
