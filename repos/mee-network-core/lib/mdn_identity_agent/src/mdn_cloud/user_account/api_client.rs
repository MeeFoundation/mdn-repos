use super::api_types::{
    CreateUserAccountRequest, UserAccountLoginRequest, UserAccountLoginResponse,
};
use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_crypto::jwk::JwkSet;
use mee_http_utils::requests::json_response_handle_error;
use url::Url;

#[async_trait]
pub trait MdnUserAccountApiClient {
    async fn register(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MdnIdentityAgentResult<UserAccountLoginResponse>;
    async fn login(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MdnIdentityAgentResult<UserAccountLoginResponse>;
    async fn mdn_jwks(&self) -> MdnIdentityAgentResult<JwkSet>;
}

pub struct MdnUserAccountApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnUserAccountApiClientDefault {
    pub fn try_new(api_base_url: Url) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> MdnIdentityAgentResult<Url> {
        Ok(format!("{}api/v1/mdn_users{}", self.api_base_url, path).parse()?)
    }
    fn make_root_api_path_url(&self, path: &str) -> MdnIdentityAgentResult<Url> {
        Ok(format!("{}{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnUserAccountApiClient for MdnUserAccountApiClientDefault {
    async fn register(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MdnIdentityAgentResult<UserAccountLoginResponse> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/accounts/register")?)
                .json(&payload)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn login(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MdnIdentityAgentResult<UserAccountLoginResponse> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/accounts/login")?)
                .json(&payload)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn mdn_jwks(&self) -> MdnIdentityAgentResult<JwkSet> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_root_api_path_url("jwks.json")?)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
