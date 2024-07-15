use super::dto::OidcProviderGrantsCreateDto;
use crate::{
    db_models::{oidc_provider_grants, prelude::*},
    error::MeeOidcProviderResult,
};
use sea_orm::{
    ActiveModelTrait, ActiveValue::NotSet, ColumnTrait, ConnectionTrait,
    EntityTrait, QueryFilter, Set,
};

#[async_trait::async_trait]
pub trait OidcProviderGrantsRepository {
    async fn create_grant(
        &self,
        oidc_provider_grants_create_dto: OidcProviderGrantsCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_grants::Model>;
    async fn remove_by_grant_code(
        &self,
        grant_code: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_grants::Model>>;
}

pub struct OidcProviderGrantsRepositoryDefault<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> OidcProviderGrantsRepositoryDefault<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> OidcProviderGrantsRepository
    for OidcProviderGrantsRepositoryDefault<'a, C>
{
    async fn create_grant(
        &self,
        OidcProviderGrantsCreateDto {
            grant_code,
            client_id,
            scope,
            redirect_uri,
            owner_id,
            until,
        }: OidcProviderGrantsCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_grants::Model> {
        let res = oidc_provider_grants::ActiveModel {
            record_id: NotSet,
            grant_code: Set(grant_code),
            client_id: Set(client_id),
            owner_id: Set(owner_id),
            scope: Set(scope),
            redirect_uri: Set(redirect_uri),
            until: Set(until),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
    async fn remove_by_grant_code(
        &self,
        grant_code: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_grants::Model>> {
        let res = OidcProviderGrants::find()
            .filter(oidc_provider_grants::Column::GrantCode.eq(grant_code))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}
