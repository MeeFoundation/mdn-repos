use super::api_types::{
    ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest, UserDeviceLinkageRequest,
    UserDeviceResponse,
};
use async_trait::async_trait;
use mee_http_utils::requests::{any_response_handle_error, json_response_handle_error};
use url::Url;

#[async_trait]
pub trait MdnUserDevicesApiClient {
    async fn register(
        &self,
        payload: RegisterUserDeviceRequest,
        auth_token: &str,
    ) -> anyhow::Result<()>;
    async fn linkage_requests(
        &self,
        auth_token: &str,
    ) -> anyhow::Result<Vec<UserDeviceLinkageRequest>>;
    async fn approve_linkage(
        &self,
        payload: ApproveUserDeviceLinkageRequest,
        auth_token: &str,
    ) -> anyhow::Result<()>;
    async fn list_all(&self, auth_token: &str) -> anyhow::Result<Vec<UserDeviceResponse>>;
}

pub struct MdnUserDevicesApiClientDefault {
    api_base_url: Url,
    http_client: reqwest::Client,
}

impl MdnUserDevicesApiClientDefault {
    pub fn try_new(api_base_url: Url) -> anyhow::Result<Self> {
        Ok(Self {
            api_base_url,
            http_client: reqwest::ClientBuilder::new().use_rustls_tls().build()?,
        })
    }
    fn make_api_v1_path_url(&self, path: &str) -> anyhow::Result<Url> {
        Ok(format!("{}api/v1/mdn_users{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnUserDevicesApiClient for MdnUserDevicesApiClientDefault {
    async fn register(
        &self,
        payload: RegisterUserDeviceRequest,
        auth_token: &str,
    ) -> anyhow::Result<()> {
        any_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/devices/register")?)
                .json(&payload)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(())
    }
    async fn list_all(&self, auth_token: &str) -> anyhow::Result<Vec<UserDeviceResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/devices/list_all")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn linkage_requests(
        &self,
        auth_token: &str,
    ) -> anyhow::Result<Vec<UserDeviceLinkageRequest>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_v1_path_url("/devices/linkage_requests")?)
                .bearer_auth(auth_token)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn approve_linkage(
        &self,
        payload: ApproveUserDeviceLinkageRequest,
        auth_token: &str,
    ) -> anyhow::Result<()> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_v1_path_url("/devices/approve_linkage")?)
                .bearer_auth(auth_token)
                .json(&payload)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
