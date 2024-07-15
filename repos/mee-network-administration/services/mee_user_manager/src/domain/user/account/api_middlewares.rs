use super::domain::UserRole;
use crate::{app_ctl::AppCtl, error::MeeUserManagerErr};
use axum::{
    extract::FromRequestParts,
    http::{header::AUTHORIZATION, request::Parts},
};
use axum_extra::headers::authorization::{Bearer, Credentials};

#[derive(Debug, Clone)]
pub struct LoggedInUser {
    pub meeid: String,
    pub role: UserRole,
}

#[async_trait::async_trait]
impl FromRequestParts<AppCtl> for LoggedInUser {
    type Rejection = MeeUserManagerErr;

    async fn from_request_parts(
        parts: &mut Parts,
        state: &AppCtl,
    ) -> Result<Self, Self::Rejection> {
        let auth_header = parts
            .headers
            .get(AUTHORIZATION)
            .ok_or(MeeUserManagerErr::MissingUserAuthToken)?;

        let bearer = Bearer::decode(auth_header)
            .ok_or(MeeUserManagerErr::MissingUserAuthToken)?;

        let res = state
            .user_controller
            .authorize_user_token(bearer.token().to_string())
            .await?;

        Ok(res)
    }
}
