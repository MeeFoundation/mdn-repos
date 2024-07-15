use super::repository::OidcProviderRegistrarRepository;
use crate::{
    db_models::oidc_provider_registrar,
    domain::oidc::{
        provider::api_types::{
            OidcProviderRegistrarCreateRequest,
            OidcProviderRegistrarCreateResponse,
        },
        registrar::dto::OidcProviderRegistrarCreateDto,
    },
    error::{MeeOidcProviderErr, MeeOidcProviderResult},
};
use async_trait::async_trait;
use oxide_auth::{
    endpoint::{PreGrant, Scope},
    primitives::registrar::{
        BoundClient, ClientType, ClientUrl, EncodedClient, RegistrarError,
    },
};
use oxide_auth_async::primitives::Registrar;
use service_utils::mee_provider_manager::{
    api_types::ProviderAccountInfoResponse, auth::LoggedInProvider,
    client::MeeProviderManagerServiceClient,
};
use std::borrow::Cow;
use std::sync::Arc;
use url::Url;
use uuid::Uuid;

#[derive(Clone)]
pub struct OidcProviderRegistrarService<'a> {
    oidc_client_registrar_repository:
        Arc<dyn OidcProviderRegistrarRepository + Send + Sync + 'a>,
    mee_provider_manager_service_client:
        Arc<dyn MeeProviderManagerServiceClient + Send + Sync>,
}

impl<'a> OidcProviderRegistrarService<'a> {
    pub fn new(
        oidc_client_registrar_repository: Arc<
            dyn OidcProviderRegistrarRepository + Send + Sync + 'a,
        >,
        mee_provider_manager_service_client: Arc<
            dyn MeeProviderManagerServiceClient + Send + Sync,
        >,
    ) -> Self {
        Self {
            oidc_client_registrar_repository,
            mee_provider_manager_service_client,
        }
    }
    pub async fn get_client_info(
        &self,
        client_id: &str,
    ) -> MeeOidcProviderResult<ProviderAccountInfoResponse> {
        let client = self
            .oidc_client_registrar_repository
            .get_by_client_id(client_id)
            .await?
            .ok_or_else(|| MeeOidcProviderErr::OAuth2MissingClientId)?;

        let res = self
            .mee_provider_manager_service_client
            .get_provider_by_id(client.provider_uid)
            .await?;

        Ok(res)
    }
    pub async fn new_client(
        &self,
        OidcProviderRegistrarCreateRequest {
            redirect_uri,
            client_type,
        }: OidcProviderRegistrarCreateRequest,
        logged_in_provider: LoggedInProvider,
    ) -> MeeOidcProviderResult<OidcProviderRegistrarCreateResponse> {
        let oidc_provider_registrar::Model { client_id, .. } = self
            .oidc_client_registrar_repository
            .create_client(OidcProviderRegistrarCreateDto {
                client_id: format!("{}.itsmee.org", Uuid::new_v4()),
                default_scope: "openid".to_string(),
                redirect_uri,
                client_type,
                provider_uid: logged_in_provider.meeid,
            })
            .await?;

        Ok(OidcProviderRegistrarCreateResponse { client_id })
    }
}

impl TryFrom<oidc_provider_registrar::Model> for EncodedClient {
    type Error = MeeOidcProviderErr;

    fn try_from(
        oidc_provider_registrar::Model {
            client_id,
            redirect_uri,
            default_scope,
            ..
        }: oidc_provider_registrar::Model,
    ) -> MeeOidcProviderResult<Self> {
        Ok(Self {
            client_id,
            redirect_uri: redirect_uri.parse::<Url>()?.into(),
            default_scope: default_scope.parse()?,
            additional_redirect_uris: vec![],
            encoded_client: ClientType::Public,
        })
    }
}

#[async_trait]
impl<'b> Registrar for OidcProviderRegistrarService<'b> {
    async fn bound_redirect<'a>(
        &self,
        bound: ClientUrl<'a>,
    ) -> Result<BoundClient<'a>, RegistrarError> {
        let client: EncodedClient = match self
            .oidc_client_registrar_repository
            .get_by_client_id(bound.client_id.as_ref())
            .await
            .map_err(|e| {
                tracing::error!("OAuth2 registrar client query error: {e}");
                RegistrarError::PrimitiveError
            })? {
            None => return Err(RegistrarError::Unspecified),
            Some(stored) => stored.try_into().map_err(|e| {
                tracing::error!("OAuth2 registrar record parsing error: {e}");
                RegistrarError::PrimitiveError
            })?,
        };

        // Perform exact matching as motivated in the rfc
        let registered_url = match bound.redirect_uri {
            None => client.redirect_uri.clone(),
            Some(ref url) => {
                let original = std::iter::once(&client.redirect_uri);
                let alternatives = client.additional_redirect_uris.iter();
                if let Some(registered) = original
                    .chain(alternatives)
                    .find(|&registered| *registered == *url.as_ref())
                {
                    registered.clone()
                } else {
                    return Err(RegistrarError::Unspecified);
                }
            }
        };

        Ok(BoundClient {
            client_id: bound.client_id,
            redirect_uri: Cow::Owned(registered_url),
        })
    }

    async fn negotiate<'a>(
        &self,
        bound: BoundClient<'a>,
        _scope: Option<Scope>,
    ) -> Result<PreGrant, RegistrarError> {
        let client: EncodedClient = self
            .oidc_client_registrar_repository
            .get_by_client_id(bound.client_id.as_ref())
            .await
            .map_err(|e| {
                tracing::error!("OAuth2 registrar client query error: {e}");
                RegistrarError::PrimitiveError
            })?
            .ok_or_else(|| {
                tracing::error!(
                    "Bound client appears to not have been constructed with this registrar"
                );
                RegistrarError::PrimitiveError
            })?
            .try_into()
            .map_err(|e| {
                tracing::error!("OAuth2 registrar record parsing error: {e}");
                RegistrarError::PrimitiveError
            })?;

        Ok(PreGrant {
            client_id: bound.client_id.into_owned(),
            redirect_uri: bound.redirect_uri.into_owned(),
            scope: client.default_scope.clone(),
        })
    }

    async fn check(
        &self,
        _client_id: &str,
        _passphrase: Option<&[u8]>,
    ) -> Result<(), RegistrarError> {
        // TODO check password based clients
        Ok(())
    }
}
