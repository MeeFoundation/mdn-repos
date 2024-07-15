use super::api_types::{IsCloudNodeLinkedRequest, ProviderAccountInfoResponse};
use crate::mee_provider_manager::api_types::{
    IS_CLOUD_NODE_LINKED_API_PATH, PROVIDER_ACCOUNT_INFO_API_PATH,
};
use mee_http_utils::{
    interservice::INTER_SERVICE_API_SECRET_HEADER,
    requests::json_response_handle_error,
};
use reqwest::Client;
use url::Url;

#[async_trait::async_trait]
pub trait MeeProviderManagerServiceClient {
    async fn get_provider_by_id(
        &self,
        provider_meeid: String,
    ) -> anyhow::Result<ProviderAccountInfoResponse>;
    async fn is_cloud_node_linked_with_provider(
        &self,
        provider_meeid: String,
        cloud_node_did: String,
    ) -> anyhow::Result<bool>;
}

pub struct MeeProviderManagerServiceClientDefault {
    http_client: Client,
    api_base_url: Url,
    inter_service_api_secret: String,
}

impl MeeProviderManagerServiceClientDefault {
    pub fn try_new(
        api_base_url: Url,
        inter_service_api_secret: String,
    ) -> anyhow::Result<Self> {
        Ok(Self {
            http_client: reqwest::ClientBuilder::new()
                .use_rustls_tls()
                .build()?,
            inter_service_api_secret,
            api_base_url,
        })
    }
}

#[async_trait::async_trait]
impl MeeProviderManagerServiceClient
    for MeeProviderManagerServiceClientDefault
{
    async fn get_provider_by_id(
        &self,
        provider_meeid: String,
    ) -> anyhow::Result<ProviderAccountInfoResponse> {
        let res = json_response_handle_error(
            self.http_client
                .get(format!(
                    "{}api/v1/providers/internal/{PROVIDER_ACCOUNT_INFO_API_PATH}/{}",
                    self.api_base_url, provider_meeid
                ))
                .header(
                    INTER_SERVICE_API_SECRET_HEADER,
                    &self.inter_service_api_secret,
                )
                .send()
                .await?,
            anyhow::Error::msg,
        ).await?;

        Ok(res)
    }
    async fn is_cloud_node_linked_with_provider(
        &self,
        provider_meeid: String,
        cloud_node_did: String,
    ) -> anyhow::Result<bool> {
        let res = json_response_handle_error(
            self.http_client
                .post(format!(
                    "{}api/v1/providers/internal/{IS_CLOUD_NODE_LINKED_API_PATH}",
                    self.api_base_url
                ))
                .header(
                    INTER_SERVICE_API_SECRET_HEADER,
                    &self.inter_service_api_secret,
                )
                .json(&IsCloudNodeLinkedRequest {
                    provider_meeid,
                    cloud_node_did,
                })
                .send()
                .await?,
            anyhow::Error::msg,
        ).await?;

        Ok(res)
    }
}
