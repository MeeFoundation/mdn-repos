use super::api_types::{MdnCustodianStorageResponse, RegisterMdnCustodianStorageRequest};
use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_http_utils::requests::{any_response_handle_error, json_response_handle_error};
use url::Url;

#[async_trait]
pub trait MdnCustodianStorageApiClient {
    async fn register_storage(
        &self,
        payload: RegisterMdnCustodianStorageRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<()>;
    async fn list_all_storages(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianStorageResponse>>;
}

pub struct MdnCustodianStorageApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnCustodianStorageApiClientDefault {
    pub fn try_new(api_base_url: Url) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> MdnIdentityAgentResult<Url> {
        Ok(format!("{}api/v1/mdn_custodian_storages{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnCustodianStorageApiClient for MdnCustodianStorageApiClientDefault {
    async fn register_storage(
        &self,
        payload: RegisterMdnCustodianStorageRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<()> {
        any_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/register")?)
                .json(&payload)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(())
    }
    async fn list_all_storages(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianStorageResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/list_all")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
