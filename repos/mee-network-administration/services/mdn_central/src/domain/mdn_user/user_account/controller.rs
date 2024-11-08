use super::{
    api_middlewares::LoggedInMdnUser,
    api_types::{
        AuthorizeUserRequest, AuthorizeUserResponse, CreateUserAccountRequest,
        UserAccountLoginRequest, UserAccountLoginResponse,
    },
    repositories::mdn_users::{
        MdnUsersRepository, MdnUserAccountRepositoryImpl,
    },
    services::auth::MdnUserAuthService,
};
use crate::error::MdnCentralResult;
use mee_db_utils::sql_storage::RbdStorage;
use mee_secrets_manager::signatures_service::SignaturesService;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnUserAccountController {
    rdb_storage: Arc<RbdStorage>,
    mdn_central_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
}

impl MdnUserAccountController {
    pub fn new(
        rdb_storage: Arc<RbdStorage>,
        mdn_central_authority_signature: Arc<
            dyn SignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mdn_central_authority_signature,
        }
    }
    pub fn user_account_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> MdnUserAuthService<'a> {
        MdnUserAuthService::new(
            Box::new(self.user_account_repository(tx)),
            self.mdn_central_authority_signature.clone(),
        )
    }
    pub fn user_account_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl MdnUsersRepository + 'a {
        MdnUserAccountRepositoryImpl::new(tx)
    }

    pub async fn register_user(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let res = self
            .user_account_service(&*self.rdb_storage.connection())
            .create_customer_account(payload)
            .await?;

        Ok(res)
    }

    pub async fn login_user(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let res = self
            .user_account_service(&*self.rdb_storage.connection())
            .user_login(payload)
            .await?;

        Ok(res)
    }

    pub async fn authorize_user_login_request(
        &self,
        payload: AuthorizeUserRequest,
    ) -> MdnCentralResult<AuthorizeUserResponse> {
        let res = self
            .user_account_service(&*self.rdb_storage.connection())
            .authorize_user_account(&payload.auth_token)
            .await?;

        Ok(res)
    }

    pub async fn authorize_user_token(
        &self,
        token: String,
    ) -> MdnCentralResult<LoggedInMdnUser> {
        let res = self
            .user_account_service(&*self.rdb_storage.connection())
            .authorize_user_token(&token)
            .await?;

        Ok(res)
    }
}
