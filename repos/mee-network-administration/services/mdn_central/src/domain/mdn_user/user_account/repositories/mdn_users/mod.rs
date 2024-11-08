use crate::{
    db_models::{mdn_users, prelude::*},
    error::MdnCentralResult,
};
use dto::CreateUserAccountDto;
use sea_orm::{entity::*, query::*};

pub mod dto;

#[async_trait::async_trait]
pub trait MdnUsersRepository {
    async fn create_account(
        &self,
        create_dto: CreateUserAccountDto,
    ) -> MdnCentralResult<mdn_users::Model>;
    async fn get_account_by_email(
        &self,
        email: &str,
    ) -> MdnCentralResult<Option<mdn_users::Model>>;
    async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCentralResult<Option<mdn_users::Model>>;
}

pub struct MdnUserAccountRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnUserAccountRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> MdnUsersRepository
    for MdnUserAccountRepositoryImpl<'a, C>
{
    async fn create_account(
        &self,
        CreateUserAccountDto {
            mdn_user_uid,
            mdn_user_email,
            mdn_user_phone,
            mdn_user_name,
            mdn_user_role,
            is_user_active,
            is_user_verified,
            salt,
            password,
        }: CreateUserAccountDto,
    ) -> MdnCentralResult<mdn_users::Model> {
        let acc = mdn_users::ActiveModel {
            mdn_user_id: NotSet,
            mdn_user_uid: Set(mdn_user_uid),
            mdn_user_email: Set(mdn_user_email),
            mdn_user_phone: Set(mdn_user_phone),
            mdn_user_name: Set(mdn_user_name),
            mdn_user_role: Set(mdn_user_role.to_string()),
            is_user_active: Set(is_user_active),
            is_user_verified: Set(is_user_verified),
            salt: Set(salt),
            password: Set(password),
        }
        .insert(self.db_conn)
        .await?;

        Ok(acc)
    }
    async fn get_account_by_email(
        &self,
        email: &str,
    ) -> MdnCentralResult<Option<mdn_users::Model>> {
        let res = MdnUsers::find()
            .filter(mdn_users::Column::MdnUserEmail.eq(email))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCentralResult<Option<mdn_users::Model>> {
        let res = MdnUsers::find()
            .filter(mdn_users::Column::MdnUserUid.eq(uid))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}
