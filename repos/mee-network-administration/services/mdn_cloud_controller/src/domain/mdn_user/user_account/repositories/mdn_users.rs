use crate::{
    db_models::{mdn_users, prelude::*},
    domain::mdn_user::user_account::services::account::service_models::MdnUserAccountRole,
    error::MdnCloudControllerResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

#[derive(Debug)]
pub struct CreateUserAccountDto {
    pub mdn_user_email: String,
    pub mdn_user_phone: Option<String>,
    pub mdn_user_name: String,
    pub mdn_user_role: MdnUserAccountRole,
    pub is_user_active: bool,
    pub is_user_verified: bool,
    pub salt: String,
    pub password: String,
}

#[async_trait]
pub trait MdnUsersRepository {
    async fn create_account(
        &self,
        create_dto: CreateUserAccountDto,
    ) -> MdnCloudControllerResult<mdn_users::Model>;
    async fn get_account_by_email(
        &self,
        email: &str,
    ) -> MdnCloudControllerResult<Option<mdn_users::Model>>;
    async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCloudControllerResult<Option<mdn_users::Model>>;
}

pub struct MdnUsersRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnUsersRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnUsersRepository
    for MdnUsersRepositoryImpl<'a, C>
{
    async fn create_account(
        &self,
        CreateUserAccountDto {
            mdn_user_email,
            mdn_user_phone,
            mdn_user_name,
            mdn_user_role,
            is_user_active,
            is_user_verified,
            salt,
            password,
        }: CreateUserAccountDto,
    ) -> MdnCloudControllerResult<mdn_users::Model> {
        let acc = mdn_users::ActiveModel {
            mdn_user_id: NotSet,
            mdn_user_uid: Set(format!("mdn_user-{}", uuid::Uuid::new_v4())),
            mdn_user_email: Set(mdn_user_email),
            mdn_user_phone: Set(mdn_user_phone),
            mdn_user_name: Set(mdn_user_name),
            mdn_user_role: Set(mdn_user_role.to_string()),
            mdn_user_created_at: Set(chrono::Utc::now().into()),
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
    ) -> MdnCloudControllerResult<Option<mdn_users::Model>> {
        let res = MdnUsers::find()
            .filter(mdn_users::Column::MdnUserEmail.eq(email))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCloudControllerResult<Option<mdn_users::Model>> {
        let res = MdnUsers::find()
            .filter(mdn_users::Column::MdnUserUid.eq(uid))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}
