use super::api_types::{
    AuthorizeUserRequest, AuthorizeUserResponse, AUTHORIZE_USER_PATH,
};
use mee_http_utils::{
    interservice::INTER_SERVICE_API_SECRET_HEADER,
    requests::json_response_handle_error,
};
use reqwest::Client;
use url::Url;

#[async_trait::async_trait]
pub trait MeeUserManagerServiceClient {
    async fn authorize_user(
        &self,
        auth_token: String,
    ) -> anyhow::Result<Option<AuthorizeUserResponse>>;
}

pub struct MeeUserManagerServiceClientDefault {
    http_client: Client,
    api_base_url: Url,
    inter_service_api_secret: String,
}

impl MeeUserManagerServiceClientDefault {
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
impl MeeUserManagerServiceClient for MeeUserManagerServiceClientDefault {
    async fn authorize_user(
        &self,
        auth_token: String,
    ) -> anyhow::Result<Option<AuthorizeUserResponse>> {
        let res = json_response_handle_error(
            self.http_client
                .post(format!(
                    "{}api/v1/users/internal/{AUTHORIZE_USER_PATH}",
                    self.api_base_url
                ))
                .header(
                    INTER_SERVICE_API_SECRET_HEADER,
                    &self.inter_service_api_secret,
                )
                .json(&AuthorizeUserRequest { auth_token })
                .send()
                .await?,
            anyhow::Error::msg,
        )
        .await?;

        Ok(res)
    }
}
