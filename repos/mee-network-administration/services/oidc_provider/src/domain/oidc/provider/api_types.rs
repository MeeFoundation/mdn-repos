use crate::domain::oidc::registrar::domain::OidcClientType;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use url::Url;
use utoipa::ToSchema;

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct OidcProviderRegistrarCreateRequest {
    pub redirect_uri: String,
    pub client_type: OidcClientType,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct OidcProviderRegistrarCreateResponse {
    pub client_id: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct OAuthResponseTO {
    status: u16,
    headers: HashMap<String, String>,
    body: Option<String>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct JwkSetTO {
    pub keys: Vec<JwkTO>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct JwkTO {
    pub kty: String,
    pub use_: Option<String>,
    pub kid: Option<String>,
    pub key_ops: Option<Vec<String>>,
    pub alg: Option<String>,
    pub x5u: Option<Url>,
    pub x5c: Option<Vec<String>>,
    pub x5t: Option<String>,
    pub x5t_s256: Option<String>,
    //TODO add more details if needed
    pub params: Option<String>,
}

// Copy of the Config struct from openid crate
#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct ConfigTO {
    pub issuer: Url,
    pub authorization_endpoint: Url,
    pub token_endpoint: Url,
    pub token_introspection_endpoint: Option<Url>,
    pub userinfo_endpoint: Option<Url>,
    pub end_session_endpoint: Option<Url>,
    pub jwks_uri: Url,
    pub registration_endpoint: Option<Url>,
    pub scopes_supported: Option<Vec<String>>,
    pub response_types_supported: Vec<String>,
    pub response_modes_supported: Option<Vec<String>>,
    pub grant_types_supported: Option<Vec<String>>,
    pub acr_values_supported: Option<Vec<String>>,
    pub subject_types_supported: Vec<String>,
    pub id_token_signing_alg_values_supported: Vec<String>,
    pub id_token_encryption_alg_values_supported: Option<Vec<String>>,
    pub id_token_encryption_enc_values_supported: Option<Vec<String>>,
    pub userinfo_signing_alg_values_supported: Option<Vec<String>>,
    pub userinfo_encryption_alg_values_supported: Option<Vec<String>>,
    pub userinfo_encryption_enc_values_supported: Option<Vec<String>>,
    pub request_object_signing_alg_values_supported: Option<Vec<String>>,
    pub request_object_encryption_alg_values_supported: Option<Vec<String>>,
    pub request_object_encryption_enc_values_supported: Option<Vec<String>>,
    pub token_endpoint_auth_methods_supported: Option<Vec<String>>,
    pub token_endpoint_auth_signing_alg_values_supported: Option<Vec<String>>,
    pub display_values_supported: Option<Vec<String>>,
    pub claim_types_supported: Option<Vec<String>>,
    pub claims_supported: Option<Vec<String>>,
    pub service_documentation: Option<Url>,
    pub claims_locales_supported: Option<Vec<String>>,
    pub ui_locales_supported: Option<Vec<String>>,
    pub claims_parameter_supported: bool,
    pub request_parameter_supported: bool,
    pub request_uri_parameter_supported: bool,
    pub require_request_uri_registration: bool,
    pub op_policy_uri: Option<Url>,
    pub op_tos_uri: Option<Url>,
    pub code_challenge_methods_supported: Option<Vec<String>>,
}
