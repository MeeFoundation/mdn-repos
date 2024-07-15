use super::{
    domain::ProviderAccountDomainModel, dto::CreateProviderAccountDto,
};
use crate::{
    db_models::{mee_network_providers, prelude::*},
    error::{MeeProviderManagerErr, MeeProviderManagerResult},
};
use sea_orm::{entity::*, query::*};

#[async_trait::async_trait]
pub trait ProviderAccountRepository {
    async fn create_account(
        &self,
        create_dto: CreateProviderAccountDto,
    ) -> MeeProviderManagerResult<mee_network_providers::Model>;
    async fn get_account_by_email(
        &self,
        email: &str,
    ) -> MeeProviderManagerResult<Option<mee_network_providers::Model>>;
    async fn get_account_by_meeid(
        &self,
        meeid: &str,
    ) -> MeeProviderManagerResult<Option<mee_network_providers::Model>>;
    async fn get_account_by_meeid_err(
        &self,
        meeid: &str,
    ) -> MeeProviderManagerResult<mee_network_providers::Model> {
        match self.get_account_by_meeid(meeid).await? {
            Some(v) => Ok(v),
            None => Err(MeeProviderManagerErr::ProviderAccountNotFound(
                meeid.to_string(),
            ))?,
        }
    }
}

pub struct ProviderAccountRepositoryDefault<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> ProviderAccountRepositoryDefault<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> ProviderAccountRepository
    for ProviderAccountRepositoryDefault<'a, C>
{
    async fn create_account(
        &self,
        CreateProviderAccountDto {
            provider_meeid,
            provider_email,
            provider_role,
            provider_name,
            is_active,
            salt,
            password,
        }: CreateProviderAccountDto,
    ) -> MeeProviderManagerResult<mee_network_providers::Model> {
        let acc = mee_network_providers::ActiveModel {
            provider_id: NotSet,
            provider_meeid: Set(provider_meeid),
            provider_email: Set(provider_email),
            provider_role: Set(provider_role),
            provider_name: Set(provider_name),
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
    ) -> MeeProviderManagerResult<Option<mee_network_providers::Model>> {
        let res = MeeNetworkProviders::find()
            .filter(mee_network_providers::Column::ProviderEmail.eq(email))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_account_by_meeid(
        &self,
        meeid: &str,
    ) -> MeeProviderManagerResult<Option<mee_network_providers::Model>> {
        let res = MeeNetworkProviders::find()
            .filter(mee_network_providers::Column::ProviderMeeid.eq(meeid))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}

impl TryFrom<mee_network_providers::Model> for ProviderAccountDomainModel {
    type Error = MeeProviderManagerErr;

    fn try_from(
        mee_network_providers::Model {
            provider_meeid,
            provider_email,
            provider_role,
            provider_name,
            is_active,
            ..
        }: mee_network_providers::Model,
    ) -> Result<Self, Self::Error> {
        Ok(Self {
            provider_meeid,
            provider_email,
            provider_role,
            provider_name,
            is_active,
        })
    }
}
