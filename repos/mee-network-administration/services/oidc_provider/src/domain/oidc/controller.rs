use super::{
    grants::{
        repository::{
            OidcProviderGrantsRepository, OidcProviderGrantsRepositoryDefault,
        },
        service::OidcProviderGrantsService,
    },
    issuer::{
        repository::{
            OidcProviderIssuedTokensRepository,
            OidcProviderIssuedTokensRepositoryDefault,
        },
        service::OidcProviderIssuerService,
    },
    oxide_async_endpoint::FnSolicitorWithPayload,
    provider::{
        api_types::{
            OidcProviderRegistrarCreateRequest,
            OidcProviderRegistrarCreateResponse,
        },
        service::OidcProviderService,
    },
    registrar::{
        repository::{
            OidcProviderRegistrarRepository,
            OidcProviderRegistrarRepositoryDefault,
        },
        service::OidcProviderRegistrarService,
    },
    router::{OAUTH2_AUTHORIZE_PATH, USER_LOGIN_PAGE_PATH},
};
use crate::{
    config::AppConfig,
    error::{MeeOidcProviderErr, MeeOidcProviderResult},
};
use askama::Template;
use axum::{
    http::{StatusCode, Uri},
    response::{IntoResponse, Redirect, Response},
};
use axum_extra::extract::CookieJar;
use base64::{engine::general_purpose::STANDARD, Engine};
use mee_db_utils::sql_storage::IRbdStorage;
use identity_jose::jwk::{Jwk, JwkSet};
use mee_secrets_manager::signatures_service::SignaturesService;
use openid::Config;
use oxide_auth::endpoint::{OwnerConsent, Solicitation};
use oxide_auth_axum::{OAuthRequest, OAuthResponse, WebError};
use sea_orm::ConnectionTrait;
use sea_orm::TransactionTrait;
use serde::Deserialize;
use service_utils::{
    mee_provider_manager::{
        api_types::ProviderAccountInfoResponse, auth::LoggedInProvider,
        client::MeeProviderManagerServiceClient,
    },
    mee_user_manager::{
        client::MeeUserManagerServiceClient, COOKIE_MEE_USER_SESSION_ID,
    },
};
use std::{collections::HashMap, sync::Arc};
use url::Url;

#[derive(Clone)]
pub struct OidcController {
    app_config: AppConfig,
    mee_user_manager_service_client:
        Arc<dyn MeeUserManagerServiceClient + Send + Sync>,
    mee_authority_signature:
        Arc<dyn SignaturesService + Send + Sync>,
    mee_provider_manager_service_client:
        Arc<dyn MeeProviderManagerServiceClient + Send + Sync>,
    rdb_storage: Arc<dyn IRbdStorage + Send + Sync>,
}

impl OidcController {
    pub fn new(
        app_config: AppConfig,
        mee_user_manager_service_client: Arc<
            dyn MeeUserManagerServiceClient + Send + Sync,
        >,
        mee_authority_signature: Arc<
            dyn SignaturesService + Send + Sync,
        >,
        mee_provider_manager_service_client: Arc<
            dyn MeeProviderManagerServiceClient + Send + Sync,
        >,
        rdb_storage: Arc<dyn IRbdStorage + Send + Sync>,
    ) -> Self {
        Self {
            mee_user_manager_service_client,
            rdb_storage,
            app_config,
            mee_authority_signature,
            mee_provider_manager_service_client,
        }
    }

    pub fn oidc_provider_registrar_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl OidcProviderRegistrarRepository + 'a {
        OidcProviderRegistrarRepositoryDefault::new(tx)
    }
    pub fn oidc_provider_grants_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl OidcProviderGrantsRepository + 'a {
        OidcProviderGrantsRepositoryDefault::new(tx)
    }
    pub fn oidc_provider_issued_tokens_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl OidcProviderIssuedTokensRepository + 'a {
        OidcProviderIssuedTokensRepositoryDefault::new(tx)
    }
    pub fn oidc_provider_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> OidcProviderService<'a> {
        let oidc_client_registrar_repository =
            Arc::new(self.oidc_provider_registrar_repository(tx));

        let oidc_provider_grants_repository =
            Arc::new(self.oidc_provider_grants_repository(tx));

        let oidc_provider_issued_tokens_repository =
            Arc::new(self.oidc_provider_issued_tokens_repository(tx));

        OidcProviderService::new(
            OidcProviderRegistrarService::new(
                oidc_client_registrar_repository,
                self.mee_provider_manager_service_client.clone(),
            ),
            OidcProviderGrantsService::new(oidc_provider_grants_repository),
            OidcProviderIssuerService::new(
                oidc_provider_issued_tokens_repository,
                self.mee_authority_signature.clone(),
            ),
        )
    }
}

impl OidcController {
    pub async fn provider_metadata(&self) -> MeeOidcProviderResult<Config> {
        let meta = Config {
            issuer: self.app_config.oidc_issuer.clone(),
            authorization_endpoint: self
                .app_config
                .oidc_authorization_endpoint
                .clone(),
            token_endpoint: self.app_config.oidc_token_endpoint.clone(),
            jwks_uri: self.app_config.oidc_jwks_uri.clone(),
            response_types_supported: vec!["code".to_string()],
            subject_types_supported: vec!["pairwise".to_string()],
            id_token_signing_alg_values_supported: ["ES256", "EdDSA"]
                .iter()
                .map(ToString::to_string)
                .collect(),
            claims_parameter_supported: false,
            request_parameter_supported: false,
            request_uri_parameter_supported: false,
            require_request_uri_registration: false,
            introspection_endpoint: None,
            userinfo_endpoint: None,
            end_session_endpoint: None,
            registration_endpoint: None,
            scopes_supported: None,
            response_modes_supported: None,
            grant_types_supported: None,
            acr_values_supported: None,
            id_token_encryption_alg_values_supported: None,
            id_token_encryption_enc_values_supported: None,
            userinfo_signing_alg_values_supported: None,
            userinfo_encryption_alg_values_supported: None,
            userinfo_encryption_enc_values_supported: None,
            request_object_signing_alg_values_supported: None,
            request_object_encryption_alg_values_supported: None,
            request_object_encryption_enc_values_supported: None,
            token_endpoint_auth_methods_supported: None,
            token_endpoint_auth_signing_alg_values_supported: None,
            display_values_supported: None,
            claim_types_supported: None,
            claims_supported: None,
            service_documentation: None,
            claims_locales_supported: None,
            ui_locales_supported: None,
            op_policy_uri: None,
            op_tos_uri: None,
            code_challenge_methods_supported: None,
        };

        Ok(meta)
    }

    pub async fn jwks(&self) -> MeeOidcProviderResult<JwkSet> {
        let sig = self
            .mee_authority_signature
            .get_source_jwk_signature()
            .await?
            .ok_or(MeeOidcProviderErr::MissingMeeAuthoritySignature)?;

        let mut set = JwkSet::new();
        let jwk: Jwk = serde_json::from_value(serde_json::to_value(sig)?)?;

        if let Some(jwk) = jwk.to_public() {
            set.add(jwk);
        }

        Ok(set)
    }

    pub async fn new_client(
        &self,
        current_provider: LoggedInProvider,
        payload: OidcProviderRegistrarCreateRequest,
    ) -> MeeOidcProviderResult<OidcProviderRegistrarCreateResponse> {
        let this = self.clone();

        let result = self
            .rdb_storage
            .connection()
            .transaction(move |tx| {
                Box::pin(async move {
                    let oidc_provider_service = this.oidc_provider_service(tx);

                    let res = oidc_provider_service
                        .registrar
                        .new_client(payload, current_provider)
                        .await?;

                    Ok(res) as MeeOidcProviderResult<_>
                })
            })
            .await?;

        Ok(result)
    }
    pub async fn get_client(
        &self,
        client_id: String,
    ) -> MeeOidcProviderResult<ProviderAccountInfoResponse> {
        let this = self.clone();

        let result = self
            .rdb_storage
            .connection()
            .transaction(move |tx| {
                Box::pin(async move {
                    let oidc_provider_service = this.oidc_provider_service(tx);

                    let res = oidc_provider_service
                        .registrar
                        .get_client_info(&client_id)
                        .await?;

                    Ok(res) as MeeOidcProviderResult<_>
                })
            })
            .await?;

        Ok(result)
    }
}

fn redirect_to_login(uri: Uri) -> Response {
    Redirect::to(&format!(
        "{}?oauth_continue={}",
        USER_LOGIN_PAGE_PATH,
        STANDARD.encode(uri.to_string())
    ))
    .into_response()
}

fn consent_decision(
    allowed: bool,
    _: Solicitation,
    mee_user_id: String,
) -> OwnerConsent<OAuthResponse> {
    if allowed {
        OwnerConsent::Authorized(mee_user_id)
    } else {
        OwnerConsent::Denied
    }
}

#[derive(Deserialize)]
pub struct ConsentStatus {
    allow: bool,
}

#[derive(Template)]
#[template(path = "login_page.html")]
struct LoginPageTemplate {
    client_id_name: String,
}

#[derive(Debug, Deserialize)]
pub struct UserOauthLoginPageParams {
    pub oauth_continue: String,
}

fn extract_client_id(base_uri: &str) -> MeeOidcProviderResult<Option<String>> {
    let url: Url = format!("schema://{}", base_uri).parse()?;

    let oauth_params = url.query_pairs().collect::<HashMap<_, _>>();

    let client_id = oauth_params.get("client_id").map(ToString::to_string);

    Ok(client_id)
}

#[derive(Template)]
#[template(path = "consent_page.html")]
struct ConsentPageTemplate {
    client_id_name: String,
    user_email: String,
    accept_url: String,
    accept_params: String,
}

fn consent_form(
    _: &mut OAuthRequest,
    solicitation: Solicitation,
    consent_info: ConsentInfo,
) -> OwnerConsent<OAuthResponse> {
    let res = || {
        let grant = solicitation.pre_grant();
        let state = solicitation.state();

        let mut oauth_params = vec![
            ("response_type", "code"),
            ("client_id", grant.client_id.as_str()),
            ("redirect_uri", grant.redirect_uri.as_str()),
        ];

        if let Some(state) = state {
            oauth_params.push(("state", state));
        }

        let res = OAuthResponse::default().content_type("text/html")?.body(
            &ConsentPageTemplate {
                user_email: consent_info.user_email,
                client_id_name: consent_info.client_id_name,
                accept_url: OAUTH2_AUTHORIZE_PATH.to_string(),
                accept_params: serde_urlencoded::to_string(oauth_params)?,
            }
            .render()?,
        );

        Ok(res) as MeeOidcProviderResult<_>
    };

    match res() {
        Ok(v) => OwnerConsent::InProgress(v),
        Err(e) => {
            OwnerConsent::Error(WebError::InternalError(Some(e.to_string())))
        }
    }
}

#[derive(Clone)]
struct ConsentInfo {
    user_email: String,
    client_id_name: String,
}

impl OidcController {
    pub async fn authorize_consent(
        &self,
        consent: Option<ConsentStatus>,
        jar: CookieJar,
        uri: Uri,
        oauth: OAuthRequest,
    ) -> MeeOidcProviderResult<Response> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let allowed = consent.map_or(false, |c| c.allow);

                    if let Some(token) = jar.get(COOKIE_MEE_USER_SESSION_ID) {
                        if let Some(logged_in_user) = this
                            .mee_user_manager_service_client
                            .authorize_user(token.value().to_string())
                            .await?
                        {
                            return Ok(this
                            .oidc_provider_service(tx)
                            .endpoint()
                            .with_solicitor(FnSolicitorWithPayload(
                                |_: &mut OAuthRequest,
                                 solicitation: Solicitation,
                                 payload| {
                                    consent_decision(
                                        allowed,
                                        solicitation,
                                        payload,
                                    )
                                },
                                logged_in_user.user_meeid,
                            ))
                            .authorization_flow()
                            .execute(oauth)
                            .await
                            .map_err(|e| e.pack::<WebError>())?
                            .into_response());
                        }
                    }

                    Ok(redirect_to_login(uri))
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn refresh_token(
        &self,
        oauth: OAuthRequest,
    ) -> MeeOidcProviderResult<OAuthResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    Ok(this
                        .oidc_provider_service(tx)
                        .endpoint()
                        .refresh_flow()
                        .execute(oauth)
                        .await
                        .map_err(|e| e.pack::<WebError>())?)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn issue_token(
        &self,
        oauth: OAuthRequest,
    ) -> MeeOidcProviderResult<OAuthResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    Ok(this
                        .oidc_provider_service(tx)
                        .endpoint()
                        .access_token_flow()
                        .execute(oauth)
                        .await
                        .map_err(|e| e.pack::<WebError>())?)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn user_login_page(
        &self,
        login_params: Option<UserOauthLoginPageParams>,
    ) -> MeeOidcProviderResult<impl IntoResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let mut found_client_id = None;

                    if let Some(p) = login_params {
                        let client_id = extract_client_id(&String::from_utf8(
                            STANDARD.decode(&p.oauth_continue)?,
                        )?)?;

                        if let Some(id) = client_id {
                            found_client_id.replace(id.clone());

                            let client_info = this
                                .oidc_provider_service(tx)
                                .registrar
                                .get_client_info(&id)
                                .await?;

                            return Ok(Response::builder()
                                .header("Content-Type", "text/html")
                                .body(
                                    LoginPageTemplate {
                                        client_id_name: client_info
                                            .provider_name,
                                    }
                                    .render()?,
                                )?
                                .into_response());
                        }
                    }

                    let err = if let Some(found_client_id) = found_client_id {
                        format!(
                            "OIDC client ({}) is not found",
                            found_client_id
                        )
                    } else {
                        "".to_string()
                    };

                    Ok((StatusCode::NOT_FOUND, err).into_response())
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn authorize(
        &self,
        uri: Uri,
        jar: CookieJar,
        oauth: OAuthRequest,
    ) -> MeeOidcProviderResult<Response> {
        let req_uri = uri.clone();
        let this = self.clone();

        let res = self
          .rdb_storage
          .connection()
          .transaction({
              move |txn| {
                  Box::pin(async move {
                      if let Some(token) = jar.get(COOKIE_MEE_USER_SESSION_ID) {
                          if let Some(user) = this
                              .mee_user_manager_service_client
                              .authorize_user(token.value().to_string())
                              .await?
                          {
                              let client_id = extract_client_id(
                                  &req_uri.to_string(),
                              )?
                                  .ok_or_else(|| {
                                      MeeOidcProviderErr::OAuth2MissingClientId
                                  })?;

                              let client = this
                                  .oidc_provider_service(txn)
                                  .registrar
                                  .get_client_info(&client_id)
                                  .await?;

                              let user_info = ConsentInfo {
                                  user_email: user.user_email,
                                  client_id_name: client.provider_name,
                              };

                              let response = this
                                  .oidc_provider_service(txn)
                                  .endpoint()
                                  .with_solicitor(FnSolicitorWithPayload(
                                      |req: &mut OAuthRequest, solicitation: Solicitation, payload| {
                                          consent_form(req, solicitation, payload)
                                      },
                                      user_info,
                                  ))
                                  .authorization_flow()
                                  .execute(oauth)
                                  .await
                                  .map_err(|e| e.pack::<WebError>())?
                                  .into_response();

                              return Ok(Some(response));
                          }
                      }

                      Ok(None) as MeeOidcProviderResult<_>
                  })
              }
          })
          .await?;

        match res {
            Some(res) => Ok(res),
            None => Ok(redirect_to_login(uri)),
        }
    }
}
