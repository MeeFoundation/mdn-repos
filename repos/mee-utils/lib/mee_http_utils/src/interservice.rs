use axum::{
    extract::FromRequestParts,
    http::{request::Parts, StatusCode},
    response::IntoResponse,
};

pub const INTER_SERVICE_API_SECRET_HEADER: &str = "Inter-Service-Api-Secret";

#[derive(Debug, thiserror::Error)]
pub enum InterServiceApiSecretError {
    #[error("Inter service communication error: API secret is missing")]
    MissingInterServiceApiSecret,
}

impl IntoResponse for InterServiceApiSecretError {
    fn into_response(self) -> axum::response::Response {
        (StatusCode::INTERNAL_SERVER_ERROR, self.to_string()).into_response()
    }
}

pub trait InterserviceApiSecretProvider {
    fn inter_service_api_secret(&self) -> &str;
}

#[derive(Debug, Clone)]
pub struct InterServiceSecuredApi;

#[async_trait::async_trait]
impl<AppCtl: InterserviceApiSecretProvider + Send + Sync> FromRequestParts<AppCtl>
    for InterServiceSecuredApi
{
    type Rejection = InterServiceApiSecretError;

    async fn from_request_parts(
        parts: &mut Parts,
        state: &AppCtl,
    ) -> Result<Self, Self::Rejection> {
        let secret = parts
            .headers
            .get(INTER_SERVICE_API_SECRET_HEADER)
            .ok_or(InterServiceApiSecretError::MissingInterServiceApiSecret)?
            .to_str()
            .map_err(|_| InterServiceApiSecretError::MissingInterServiceApiSecret)?;

        if state.inter_service_api_secret() != secret {
            Err(InterServiceApiSecretError::MissingInterServiceApiSecret)?
        }

        Ok(InterServiceSecuredApi)
    }
}
