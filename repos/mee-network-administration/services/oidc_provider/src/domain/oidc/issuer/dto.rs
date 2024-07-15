use crate::error::MeeOidcProviderErr;
use oxide_auth::primitives::grant::Grant;
use serde::{Deserialize, Serialize};

type OidcProviderIssuedTokensModel =
    crate::db_models::oidc_provider_issued_tokens::Model;

impl TryFrom<OidcProviderIssuedTokensModel> for Grant {
    type Error = MeeOidcProviderErr;

    fn try_from(
        OidcProviderIssuedTokensModel {
            grant_owner_id,
            grant_client_id,
            grant_redirect_uri,
            grant_scope,
            grant_until,
            ..
        }: OidcProviderIssuedTokensModel,
    ) -> Result<Self, Self::Error> {
        Ok(Grant {
            owner_id: grant_owner_id,
            client_id: grant_client_id,
            scope: grant_scope.parse()?,
            redirect_uri: grant_redirect_uri.parse()?,
            until: grant_until.parse()?,
            extensions: Default::default(),
        })
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct OidcProviderIssuedTokensCreateDto {
    pub token_uid: String,
    pub access_token: String,
    pub refresh_token: String,
    pub grant_owner_id: String,
    pub grant_client_id: String,
    pub grant_redirect_uri: String,
    pub grant_scope: String,
    pub grant_until: String,
}
