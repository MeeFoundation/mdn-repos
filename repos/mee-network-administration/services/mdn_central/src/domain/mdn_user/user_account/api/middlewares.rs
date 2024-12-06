use crate::{
    app_ctl::AppCtl,
    domain::mdn_user::user_account::services::account::service_models::MdnUserAccountRole,
    error::MdnCentralErr,
};
use axum::{
    extract::FromRequestParts,
    http::{header::AUTHORIZATION, request::Parts},
};
use axum_extra::headers::authorization::{Bearer, Credentials};

#[derive(Debug, Clone)]
pub struct DirectlyLoggedInMdnUser {
    pub mdn_user_uid: String,
    pub mdn_user_custodian_uid: String,
    pub _mdn_user_account_role: MdnUserAccountRole,
}

pub enum LoggedInMdnUser {
    DirectlyLoggedInMdnUser(DirectlyLoggedInMdnUser),
    // TODO add provider participant support
    OAuthLoggedInUser,
}

impl LoggedInMdnUser {
    pub fn mdn_custodian_uid(&self) -> &str {
        match self {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(logged_in_mdn_user) => {
                &logged_in_mdn_user.mdn_user_custodian_uid
            }
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        }
    }
}

#[async_trait::async_trait]
impl FromRequestParts<AppCtl> for LoggedInMdnUser {
    type Rejection = MdnCentralErr;

    async fn from_request_parts(
        parts: &mut Parts,
        state: &AppCtl,
    ) -> Result<Self, Self::Rejection> {
        let res =
            DirectlyLoggedInMdnUser::from_request_parts(parts, state).await?;

        // TODO add oauth user auth token handling
        Ok(Self::DirectlyLoggedInMdnUser(res))
    }
}

#[async_trait::async_trait]
impl FromRequestParts<AppCtl> for DirectlyLoggedInMdnUser {
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
