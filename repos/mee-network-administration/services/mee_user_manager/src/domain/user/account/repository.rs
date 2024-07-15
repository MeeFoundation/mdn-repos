use super::{domain::UserAccountDomainModel, dto::CreateUserAccountDto};
use crate::{
    db_models::{mee_network_users, prelude::*},
    error::{MeeUserManagerErr, MeeUserManagerResult},
};
use sea_orm::{entity::*, query::*};

#[async_trait::async_trait]
pub trait UserAccountRepository {
    async fn create_account(
        &self,
        create_dto: CreateUserAccountDto,
    ) -> MeeUserManagerResult<mee_network_users::Model>;
    async fn get_account_by_email(
        &self,
        email: &str,
    ) -> MeeUserManagerResult<Option<mee_network_users::Model>>;
    async fn get_account_by_meeid(
        &self,
        meeid: &str,
    ) -> MeeUserManagerResult<Option<mee_network_users::Model>>;
}

pub struct UserAccountRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> UserAccountRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> UserAccountRepository
    for UserAccountRepositoryImpl<'a, C>
{
    async fn create_account(
        &self,
        CreateUserAccountDto {
            user_meeid,
            user_email,
            user_role,
            user_phone,
            is_active,
            salt,
            password,
        }: CreateUserAccountDto,
    ) -> MeeUserManagerResult<mee_network_users::Model> {
        let acc = mee_network_users::ActiveModel {
            user_id: NotSet,
            user_meeid: Set(user_meeid),
            user_email: Set(user_email),
            user_phone: Set(user_phone),
            user_role: Set(user_role),
            is_active: Set(is_active),
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
    ) -> MeeUserManagerResult<Option<mee_network_users::Model>> {
        let res = MeeNetworkUsers::find()
            .filter(mee_network_users::Column::UserEmail.eq(email))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_account_by_meeid(
        &self,
        meeid: &str,
    ) -> MeeUserManagerResult<Option<mee_network_users::Model>> {
        let res = MeeNetworkUsers::find()
            .filter(mee_network_users::Column::UserMeeid.eq(meeid))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}

impl TryFrom<mee_network_users::Model> for UserAccountDomainModel {
    type Error = MeeUserManagerErr;

    fn try_from(
        mee_network_users::Model {
            user_meeid,
            user_email,
            user_phone,
            user_role,
            is_active,
            ..
        }: mee_network_users::Model,
    ) -> Result<Self, Self::Error> {
        Ok(Self {
            user_meeid,
            user_email,
            user_role,
            user_phone,
            is_active,
        })
    }
}
