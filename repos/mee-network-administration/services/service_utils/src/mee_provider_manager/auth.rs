use super::domain::ProviderRole;
use axum::{
    extract::FromRequestParts,
    http::{header::AUTHORIZATION, request::Parts, StatusCode},
    response::IntoResponse,
};
use axum_extra::headers::authorization::{Bearer, Credentials};
use biscuit_auth::{Authorizer, AuthorizerLimits, Biscuit};
use mee_secrets_manager::signatures_service::SignaturesService;
use std::sync::Arc;

#[derive(Debug, Clone)]
pub struct LoggedInProvider {
    pub meeid: String,
    pub role: ProviderRole,
}

#[derive(Debug, thiserror::Error)]
pub enum MeeProviderAuthorizerError {
    #[error("Strum parsing error: {0}")]
    StrumParsing(#[from] strum::ParseError),

    #[error("Biscuit auth token error: {0}")]
    AuthToken(#[from] biscuit_auth::error::Token),

    #[error("Anyhow error: {0}")]
    AnyhowError(#[from] anyhow::Error),

    #[error(
        "Provider management error: provider authorization token is missing"
    )]
    MissingProviderAuthToken,

    #[error("Mee authority signature is missing")]
    MissingMeeAuthoritySignature,

    #[error(
        "Provider management error: provider authorization token is invalid"
    )]
    InvalidProviderAuthToken,

    #[error("Unspecified provider authorizer error: {0}")]
    Other(String),
}

pub type MeeProviderAuthorizerResult<T = ()> =
    Result<T, MeeProviderAuthorizerError>;

impl IntoResponse for MeeProviderAuthorizerError {
    fn into_response(self) -> axum::response::Response {
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}

#[async_trait::async_trait]
pub trait MeeProviderAuthorizer {
    fn mee_authority_signature(
        &self,
    ) -> Arc<dyn SignaturesService + Send + Sync>;
    async fn authorize_provider(
        &self,
        auth_token: &str,
    ) -> MeeProviderAuthorizerResult<LoggedInProvider> {
        let pkey = self
            .mee_authority_signature()
            .get_biscuit_signature_from_source_jwk()
            .await?
            .ok_or(MeeProviderAuthorizerError::MissingMeeAuthoritySignature)?;

        let biscuit = Biscuit::from_base64(auth_token, pkey.public())?;

        let mut providers: Vec<(String, String)> = {
            let mut authorizer = Authorizer::new();

            authorizer.add_policy(
                format!(
                    r#"
                    allow if provider($id), role($r), ["{}", "{}"].contains($r)
                "#,
                    ProviderRole::Admin,
                    ProviderRole::Customer
                )
                .as_str(),
            )?;

            authorizer.set_limits(AuthorizerLimits {
                max_time: std::time::Duration::from_millis(500),
                ..Default::default()
            });
            authorizer.set_time();
            authorizer.add_token(&biscuit)?;
            authorizer.authorize()?;

            authorizer.query("data($id, $rol) <- provider($id), role($rol)")?
        };

        let (meeid, role) = providers
            .pop()
            .ok_or(MeeProviderAuthorizerError::InvalidProviderAuthToken)?;

        let user = LoggedInProvider {
            meeid,
            role: role.parse()?,
        };

        Ok(user)
    }
}

#[async_trait::async_trait]
impl<AppCtl: MeeProviderAuthorizer + Send + Sync> FromRequestParts<AppCtl>
    for LoggedInProvider
{
    type Rejection = MeeProviderAuthorizerError;

    async fn from_request_parts(
        parts: &mut Parts,
        state: &AppCtl,
    ) -> Result<Self, Self::Rejection> {
        let auth_header = parts
            .headers
            .get(AUTHORIZATION)
            .ok_or(MeeProviderAuthorizerError::MissingProviderAuthToken)?;

        let bearer = Bearer::decode(auth_header)
            .ok_or(MeeProviderAuthorizerError::MissingProviderAuthToken)?;

        let res = state.authorize_provider(bearer.token()).await?;

        Ok(res)
    }
}
