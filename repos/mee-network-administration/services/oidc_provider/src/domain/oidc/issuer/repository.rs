use super::dto::OidcProviderIssuedTokensCreateDto;
use crate::{
    db_models::{oidc_provider_issued_tokens, prelude::*},
    error::MeeOidcProviderResult,
};
use sea_orm::{
    ActiveModelTrait, ActiveValue::NotSet, ColumnTrait, ConnectionTrait,
    EntityTrait, IntoActiveModel, QueryFilter, Set,
};

#[async_trait::async_trait]
pub trait OidcProviderIssuedTokensRepository {
    async fn get_info_by_refresh_token(
        &self,
        refresh_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>>;
    async fn get_info_by_access_token(
        &self,
        access_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>>;
    async fn refresh_token(
        &self,
        new_access_token: &str,
        new_refresh_token: &str,
        current_refresh_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>>;
    async fn create_token(
        &self,
        oidc_provider_issued_tokens_create_dto: OidcProviderIssuedTokensCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_issued_tokens::Model>;
}

pub struct OidcProviderIssuedTokensRepositoryDefault<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> OidcProviderIssuedTokensRepositoryDefault<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> OidcProviderIssuedTokensRepository
    for OidcProviderIssuedTokensRepositoryDefault<'a, C>
{
    async fn get_info_by_refresh_token(
        &self,
        refresh_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>> {
        let res = OidcProviderIssuedTokens::find()
            .filter(
                oidc_provider_issued_tokens::Column::RefreshToken
                    .eq(refresh_token),
            )
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_info_by_access_token(
        &self,
        access_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>> {
        let res = OidcProviderIssuedTokens::find()
            .filter(
                oidc_provider_issued_tokens::Column::AccessToken
                    .eq(access_token),
            )
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn refresh_token(
        &self,
        new_access_token: &str,
        new_refresh_token: &str,
        current_refresh_token: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_issued_tokens::Model>> {
        if let Some(res) = self
            .get_info_by_refresh_token(current_refresh_token)
            .await?
        {
            let mut active_model = res.into_active_model();

            active_model.refresh_token = Set(new_refresh_token.to_string());
            active_model.access_token = Set(new_access_token.to_string());

            let res = active_model.update(self.db_conn).await?;

            return Ok(Some(res));
        }

        Ok(None)
    }
    async fn create_token(
        &self,
        OidcProviderIssuedTokensCreateDto {
            token_uid,
            access_token,
            refresh_token,
            grant_owner_id,
            grant_client_id,
            grant_redirect_uri,
            grant_scope,
            grant_until,
        }: OidcProviderIssuedTokensCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_issued_tokens::Model> {
        let res = oidc_provider_issued_tokens::ActiveModel {
            record_id: NotSet,
            token_uid: Set(token_uid),
            access_token: Set(access_token),
            refresh_token: Set(refresh_token),
            grant_client_id: Set(grant_client_id),
            grant_owner_id: Set(grant_owner_id),
            grant_scope: Set(grant_scope),
            grant_redirect_uri: Set(grant_redirect_uri),
            grant_until: Set(grant_until),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
