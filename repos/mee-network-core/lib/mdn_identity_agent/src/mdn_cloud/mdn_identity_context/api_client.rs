use super::api_types::{CreateMdnIdentityContextRequest, MdnIdentityContextResponse};
use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_http_utils::requests::json_response_handle_error;
use url::Url;

#[async_trait]
pub trait MdnIdentityContextApiClient {
    async fn create_context(
        &self,
        payload: CreateMdnIdentityContextRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse>;
    async fn list_contexts(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityContextResponse>>;
}

pub struct MdnIdentityContextApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnIdentityContextApiClientDefault {
    pub fn try_new(api_base_url: Url) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> MdnIdentityAgentResult<Url> {
        Ok(format!("{}api/v1/mdn_identity_contexts{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnIdentityContextApiClient for MdnIdentityContextApiClientDefault {
    async fn create_context(
        &self,
        payload: CreateMdnIdentityContextRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<MdnIdentityContextResponse> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/create_context")?)
                .json(&payload)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn list_contexts(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityContextResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/list_contexts")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
