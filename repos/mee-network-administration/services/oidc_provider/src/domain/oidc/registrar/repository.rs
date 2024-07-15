use super::dto::OidcProviderRegistrarCreateDto;
use crate::{
    db_models::{oidc_provider_registrar, prelude::*},
    error::MeeOidcProviderResult,
};
use sea_orm::{
    ActiveModelTrait, ActiveValue::NotSet, ColumnTrait, ConnectionTrait,
    EntityTrait, QueryFilter, Set,
};

#[async_trait::async_trait]
pub trait OidcProviderRegistrarRepository {
    async fn create_client(
        &self,
        oidc_provider_registrar_create_dto: OidcProviderRegistrarCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_registrar::Model>;
    async fn get_by_client_id(
        &self,
        client_id: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_registrar::Model>>;
}

pub struct OidcProviderRegistrarRepositoryDefault<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> OidcProviderRegistrarRepositoryDefault<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> OidcProviderRegistrarRepository
    for OidcProviderRegistrarRepositoryDefault<'a, C>
{
    async fn create_client(
        &self,
        OidcProviderRegistrarCreateDto {
            client_id,
            default_scope,
            redirect_uri,
            provider_uid,
            client_type,
        }: OidcProviderRegistrarCreateDto,
    ) -> MeeOidcProviderResult<oidc_provider_registrar::Model> {
        let res = oidc_provider_registrar::ActiveModel {
            record_id: NotSet,
            client_id: Set(client_id),
            client_type: Set(client_type),
            default_scope: Set(default_scope),
            redirect_uri: Set(redirect_uri),
            provider_uid: Set(provider_uid),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
    async fn get_by_client_id(
        &self,
        client_id: &str,
    ) -> MeeOidcProviderResult<Option<oidc_provider_registrar::Model>> {
        let res = OidcProviderRegistrar::find()
            .filter(oidc_provider_registrar::Column::ClientId.eq(client_id))
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
}
