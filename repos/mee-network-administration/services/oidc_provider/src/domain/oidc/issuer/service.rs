use super::repository::OidcProviderIssuedTokensRepository;
use crate::{
    domain::oidc::issuer::dto::OidcProviderIssuedTokensCreateDto,
    error::{MeeOidcProviderErr, MeeOidcProviderResult},
};
use async_trait::async_trait;
use biscuit_auth::{
    macros::{authorizer, biscuit},
    AuthorizerLimits, Biscuit,
};
use chrono::{DateTime, Duration, Utc};
use oxide_auth::primitives::{
    generator::{RandomGenerator, TagGrant},
    grant::Grant,
    issuer::{IssuedToken, RefreshedToken, TokenType},
};
use oxide_auth_async::primitives::Issuer;
use mee_authority_secrets::MeeAuthoritySignatureService;
use serde::{Deserialize, Serialize};
use std::sync::Arc;
use strum_macros::{Display, EnumString};
use utoipa::ToSchema;
use uuid::Uuid;

// TODO: move to shared wallet core sdk
#[derive(
    Debug, Clone, Serialize, Deserialize, Display, EnumString, ToSchema,
)]
pub enum MeeNetworkWalletRole {
    #[strum(serialize = "super_wallet")]
    #[serde(rename = "super_wallet")]
    SuperWallet,
    #[strum(serialize = "virtual_wallet")]
    #[serde(rename = "virtual_wallet")]
    VirtualWallet,
}

#[derive(Clone)]
pub struct OidcProviderIssuerService<'a> {
    oidc_provider_issued_tokens_repository:
        Arc<dyn OidcProviderIssuedTokensRepository + Send + Sync + 'a>,
    mee_network_authority_signature_service:
        Arc<dyn MeeAuthoritySignatureService + Send + Sync>,
    token_duration: Duration,
}

impl<'a> OidcProviderIssuerService<'a> {
    pub fn new(
        oidc_provider_issued_tokens_repository: Arc<
            dyn OidcProviderIssuedTokensRepository + Send + Sync + 'a,
        >,
        mee_network_authority_signature_service: Arc<
            dyn MeeAuthoritySignatureService + Send + Sync,
        >,
    ) -> Self {
        Self {
            mee_network_authority_signature_service,
            oidc_provider_issued_tokens_repository,
            token_duration: Duration::days(14),
        }
    }
    async fn _extract_token_uid(
        &self,
        token: &str,
    ) -> MeeOidcProviderResult<Option<String>> {
        let root_key = self
            .mee_network_authority_signature_service
            .get_signature_for_biscuit()
            .await?
            .ok_or(MeeOidcProviderErr::MissingMeeAuthoritySignature)?;

        let biscuit = Biscuit::from_base64(token, root_key.public())?;

        let mut token_uids: Vec<(String,)> = {
            let mut authorizer = authorizer!(
                r#"
                    allow if true;
                "#
            );

            authorizer.set_limits(AuthorizerLimits {
                max_time: std::time::Duration::from_millis(500),
                ..Default::default()
            });
            // authorizer.set_time();
            authorizer.add_token(&biscuit)?;
            authorizer.authorize()?;

            authorizer.query("data($uid) <- token_uid($uid)")?
        };

        Ok(token_uids.pop().map(|(id,)| id))
    }
    async fn create_auth_token(
        &self,
        grant: Grant,
        token_uid: &str,
    ) -> MeeOidcProviderResult<(String, DateTime<Utc>)> {
        let root_key = self
            .mee_network_authority_signature_service
            .get_signature_for_biscuit()
            .await?
            .ok_or(MeeOidcProviderErr::MissingMeeAuthoritySignature)?;

        let expires = Utc::now() + self.token_duration;

        let biscuit = biscuit!(
            r#"
                token_uid({token_uid});
                oidc_logged_in_user({owner_id});
                wallet_role({wallet_role});
                expires({expiration_time});

                check if time($time), $time <= {expiration_time};
            "#,
            token_uid = token_uid,
            owner_id = grant.owner_id,
            wallet_role = MeeNetworkWalletRole::VirtualWallet.to_string(),
            expiration_time =
                Into::<std::time::SystemTime>::into(expires),
        );

        let biscuit = biscuit.build(&root_key)?;

        Ok((biscuit.to_base64()?, expires))
    }
}

#[async_trait]
impl<'a> Issuer for OidcProviderIssuerService<'a> {
    async fn issue(&mut self, grant: Grant) -> Result<IssuedToken, ()> {
        let token_uid = Uuid::new_v4().to_string();

        let (access_token, token_until) = self
            .create_auth_token(grant.clone(), &token_uid)
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Access token generation error: {e}"
                );
                
            })?;

        let refresh_token = RandomGenerator::new(16).tag(0, &grant)?;

        let Grant {
            owner_id: grant_owner_id,
            client_id: grant_client_id,
            scope: grant_scope,
            redirect_uri: grant_redirect_uri,
            ..
        } = grant;

        self.oidc_provider_issued_tokens_repository
            .create_token(OidcProviderIssuedTokensCreateDto {
                token_uid,
                access_token: access_token.clone(),
                refresh_token: refresh_token.clone(),
                grant_owner_id,
                grant_client_id,
                grant_redirect_uri: grant_redirect_uri.to_string(),
                grant_scope: grant_scope.to_string(),
                grant_until: token_until.to_string(),
            })
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Access token persisting error: {e}"
                );
                
            })?;

        Ok(IssuedToken {
            token: access_token,
            refresh: Some(refresh_token),
            until: token_until,
            token_type: TokenType::Bearer,
        })
    }

    async fn refresh(
        &mut self,
        current_refresh_token: &str,
        grant: Grant,
    ) -> Result<RefreshedToken, ()> {
        let current_token_record = self
            .oidc_provider_issued_tokens_repository
            .get_info_by_refresh_token(current_refresh_token)
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Refresh token fetching error for the client ({}): {e}",
                    grant.client_id
                );
                
            })?
            .ok_or_else(|| {
                tracing::error!(
                    "[OAuth Issuer] Refresh token is not found for the client ({})",
                    grant.client_id
                );
                
            })?;

        let (new_access_token, token_until) = self
            .create_auth_token(grant.clone(), &current_token_record.token_uid)
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Access token generation error: {e}"
                );
                
            })?;

        let new_refresh_token = RandomGenerator::new(16).tag(0, &grant)?;

        self.oidc_provider_issued_tokens_repository
            .refresh_token(
                &new_access_token,
                &new_refresh_token,
                current_refresh_token,
            )
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Refresh token update error: {e}"
                );
                
            })?;

        Ok(RefreshedToken {
            token: new_access_token,
            refresh: Some(new_refresh_token),
            until: token_until,
            token_type: TokenType::Bearer,
        })
    }

    async fn recover_token(
        &mut self,
        current_access_token: &str,
    ) -> Result<Option<Grant>, ()> {
        if let Some(issued_token_info) = self.oidc_provider_issued_tokens_repository
            .get_info_by_access_token(current_access_token)
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Refresh token ({}) is not found for the client: {e}",
                    current_access_token,
                );
                
            })? {
                let mut grant: Grant = issued_token_info.try_into().map_err(|e| {
                    tracing::error!(
                        "[OAuth Issuer] Error recovering access token grant from issued token info record: {e}",
                    );
                    
                })?;
        
                grant.until = Utc::now() + Duration::minutes(10);

                return Ok(Some(grant));
            }

        Ok(None)
    }

    async fn recover_refresh(
        &mut self,
        current_refresh_token: &str,
    ) -> Result<Option<Grant>, ()> {
        if let Some(issued_token_info) = self.oidc_provider_issued_tokens_repository
            .get_info_by_refresh_token(current_refresh_token)
            .await
            .map_err(|e| {
                tracing::error!(
                    "[OAuth Issuer] Refresh token ({}) is not found for the client: {e}",
                    current_refresh_token,
                );
                
            })? {
                let mut grant: Grant = issued_token_info.try_into().map_err(|e| {
                    tracing::error!(
                        "[OAuth Issuer] Error recovering refresh token grant from issued token info record: {e}",
                    );
                    
                })?;
        
                grant.until = Utc::now() + Duration::minutes(10);
        
                return Ok(Some(grant));
            }

        Ok(None)
    }
}
