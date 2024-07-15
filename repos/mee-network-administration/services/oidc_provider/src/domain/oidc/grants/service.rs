use super::{
    dto::OidcProviderGrantsCreateDto, repository::OidcProviderGrantsRepository,
};
use crate::db_models::oidc_provider_grants;
use async_trait::async_trait;
use oxide_auth::primitives::{
    generator::{RandomGenerator, TagGrant},
    grant::Grant,
};
use oxide_auth_async::primitives::Authorizer;
use std::sync::Arc;

#[derive(Clone)]
pub struct OidcProviderGrantsService<'a> {
    oidc_provider_grants_repository:
        Arc<dyn OidcProviderGrantsRepository + Send + Sync + 'a>,
}

impl<'a> OidcProviderGrantsService<'a> {
    pub fn new(
        oidc_provider_grants_repository: Arc<
            dyn OidcProviderGrantsRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            oidc_provider_grants_repository,
        }
    }
}

#[async_trait]
impl<'a> Authorizer for OidcProviderGrantsService<'a> {
    async fn authorize(&mut self, grant: Grant) -> Result<String, ()> {
        let grant_code = RandomGenerator::new(16).tag(0, &grant)?;

        let Grant {
            owner_id,
            client_id,
            scope,
            redirect_uri,
            until,
            extensions: _,
        } = grant;

        self.oidc_provider_grants_repository
            .create_grant(OidcProviderGrantsCreateDto {
                owner_id,
                client_id,
                grant_code: grant_code.clone(),
                redirect_uri: redirect_uri.to_string(),
                scope: scope.to_string(),
                until: until.to_string(),
            })
            .await
            .map_err(|e| {
                tracing::error!("Token persisting error: {e}");
                
            })?;

        Ok(grant_code)
    }

    async fn extract(&mut self, grant_code: &str) -> Result<Option<Grant>, ()> {
        let grant = match self
            .oidc_provider_grants_repository
            .remove_by_grant_code(grant_code)
            .await
            .map_err(|e| {
                tracing::error!("Grant ID extraction error: {e}");
                
            })? {
            Some(oidc_provider_grants::Model {
                owner_id,
                client_id,
                redirect_uri,
                scope,
                until,
                ..
            }) => Some(Grant {
                owner_id,
                client_id,
                scope: scope.parse().map_err(|e| {
                    tracing::error!("'scope' parsing error: {e}");
                    
                })?,
                redirect_uri: redirect_uri.parse().map_err(|e| {
                    tracing::error!("'redirect_uri' parsing error: {e}");
                    
                })?,
                until: until.parse().map_err(|e| {
                    tracing::error!("'until' parsing error: {e}");
                    
                })?,
                extensions: Default::default(),
            }),
            None => None,
        };

        Ok(grant)
    }
}
