use super::api_types::{MdnNodeHostingPlatformResponse, RegisterMdnNodeHostingPlatformRequest};
use async_trait::async_trait;
use mee_http_utils::requests::{any_response_handle_error, json_response_handle_error};
use url::Url;

#[async_trait]
pub trait MdnNodesApiClient {
    async fn register(
        &self,
        payload: RegisterMdnNodeHostingPlatformRequest,
        auth_token: &str,
    ) -> anyhow::Result<()>;
    async fn list_all(
        &self,
        auth_token: &str,
    ) -> anyhow::Result<Vec<MdnNodeHostingPlatformResponse>>;
}

pub struct MdnNodesApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnNodesApiClientDefault {
    pub fn try_new(api_base_url: Url) -> anyhow::Result<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> anyhow::Result<Url> {
        Ok(format!("{}api/v1/mdn_nodes{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnNodesApiClient for MdnNodesApiClientDefault {
    async fn register(
        &self,
        payload: RegisterMdnNodeHostingPlatformRequest,
        auth_token: &str,
    ) -> anyhow::Result<()> {
        any_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/register_node_hosting_platform")?)
                .json(&payload)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(())
    }
    async fn list_all(
        &self,
        auth_token: &str,
    ) -> anyhow::Result<Vec<MdnNodeHostingPlatformResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/list_all_node_hosting_platforms")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
