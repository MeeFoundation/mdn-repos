use super::domain::OidcClientType;
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct OidcProviderRegistrarCreateDto {
    pub client_id: String,
    pub client_type: OidcClientType,
    pub default_scope: String,
    pub redirect_uri: String,
    pub provider_uid: String,
}
