use super::services::auth::service_models::MdnUserAccountRole;
use crate::{app_ctl::AppCtl, error::MdnCentralErr};
use axum::{
    extract::FromRequestParts,
    http::{header::AUTHORIZATION, request::Parts},
};
use axum_extra::headers::authorization::{Bearer, Credentials};

#[derive(Debug, Clone)]
pub struct LoggedInMdnUser {
    pub mdn_user_uid: String,
    pub mdn_user_account_role: MdnUserAccountRole,
}

#[async_trait::async_trait]
impl FromRequestParts<AppCtl> for LoggedInMdnUser {
    type Rejection = MdnCentralErr;

    async fn from_request_parts(
        parts: &mut Parts,
        state: &AppCtl,
    ) -> Result<Self, Self::Rejection> {
        let auth_header = parts
            .headers
            .get(AUTHORIZATION)
            .ok_or(MdnCentralErr::MissingMdnUserAuthToken)?;

        let bearer = Bearer::decode(auth_header)
            .ok_or(MdnCentralErr::MissingMdnUserAuthToken)?;

        let res = state
            .mdn_user_account_controller
            .authorize_user_token(bearer.token().to_string())
            .await?;

        Ok(res)
    }
}
