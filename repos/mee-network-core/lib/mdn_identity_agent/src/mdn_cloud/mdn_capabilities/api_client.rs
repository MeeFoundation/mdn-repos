use super::api_types::{IssueContextOpsCapTokenRequest, MdnCustodianContextOperationCapsResponse};
use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_http_utils::requests::{any_response_handle_error, json_response_handle_error};
use url::Url;

#[async_trait]
pub trait MdnCapabilitiesApiClient {
    async fn issue_context_ops_cap(
        &self,
        payload: IssueContextOpsCapTokenRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<()>;
    async fn context_ops_caps(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianContextOperationCapsResponse>>;
}

pub struct MdnCapabilitiesApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnCapabilitiesApiClientDefault {
    pub fn try_new(api_base_url: Url) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> MdnIdentityAgentResult<Url> {
        Ok(format!("{}api/v1/mdn_capabilities{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnCapabilitiesApiClient for MdnCapabilitiesApiClientDefault {
    async fn issue_context_ops_cap(
        &self,
        payload: IssueContextOpsCapTokenRequest,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<()> {
        any_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/issue_context_ops_cap")?)
                .json(&payload)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(())
    }
    async fn context_ops_caps(
        &self,
        auth_token: &str,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianContextOperationCapsResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/context_ops_caps")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
