use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct OidcProviderGrantsCreateDto {
    pub grant_code: String,
    pub owner_id: String,
    pub client_id: String,
    pub redirect_uri: String,
    pub scope: String,
    pub until: String,
}
