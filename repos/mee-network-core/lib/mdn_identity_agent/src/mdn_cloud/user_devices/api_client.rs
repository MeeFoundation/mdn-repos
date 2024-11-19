use super::api_types::{
    ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest, UserDeviceLinkageRequest,
};
use async_trait::async_trait;
use mee_http_utils::requests::json_response_handle_error;
use url::Url;

#[async_trait]
pub trait MdnUserDevicesApiClient {
    async fn register(&self, payload: RegisterUserDeviceRequest) -> anyhow::Result<()>;
    async fn linkage_requests(&self) -> anyhow::Result<Vec<UserDeviceLinkageRequest>>;
    async fn approve_linkage(&self, payload: ApproveUserDeviceLinkageRequest)
        -> anyhow::Result<()>;
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
    fn make_api_path_url(&self, path: &str) -> anyhow::Result<Url> {
        Ok(format!("{}/mdn_users{}", self.api_base_url, path).parse()?)
    }
}

#[async_trait]
impl MdnUserDevicesApiClient for MdnUserDevicesApiClientDefault {
    async fn register(&self, payload: RegisterUserDeviceRequest) -> anyhow::Result<()> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_path_url("/devices/register")?)
                .json(&payload)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
    async fn linkage_requests(&self) -> anyhow::Result<Vec<UserDeviceLinkageRequest>> {
        let res = json_response_handle_error(
            self.http_client
                .get(self.make_api_path_url("/devices/linkage_requests")?)
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
    ) -> anyhow::Result<()> {
        let res = json_response_handle_error(
            self.http_client
                .post(self.make_api_path_url("/devices/approve_linkage")?)
                .json(&payload)
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
