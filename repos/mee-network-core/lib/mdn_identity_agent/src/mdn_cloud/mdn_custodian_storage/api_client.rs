use super::api_types::{MdnCustodianStorageResponse, RegisterMdnCustodianStorageRequest};
use async_trait::async_trait;
use mee_http_utils::requests::{any_response_handle_error, json_response_handle_error};
use url::Url;

#[async_trait]
pub trait MdnCustodianStorageApiClient {
    async fn register(
        &self,
        payload: RegisterMdnCustodianStorageRequest,
        auth_token: &str,
    ) -> anyhow::Result<()>;
    async fn list_all(
        &self,
        auth_token: &str,
    ) -> anyhow::Result<Vec<MdnCustodianStorageResponse>>;
}

pub struct MdnCustodianStorageApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnCustodianStorageApiClientDefault {
    pub fn try_new(api_base_url: Url) -> anyhow::Result<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> anyhow::Result<Url> {
        Ok(format!("{}api/v1/mdn_custodian_storages{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnCustodianStorageApiClient for MdnCustodianStorageApiClientDefault {
    async fn register(
        &self,
        payload: RegisterMdnCustodianStorageRequest,
        auth_token: &str,
    ) -> anyhow::Result<()> {
        any_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/register_custodian_storage")?)
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
    ) -> anyhow::Result<Vec<MdnCustodianStorageResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/list_all_custodian_storages")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
