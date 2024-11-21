use super::{
    api::account::middlewares::LoggedInMdnUser,
    api::account::types::{
        AuthorizeUserRequest, AuthorizeUserResponse, CreateUserAccountRequest,
        UserAccountLoginRequest, UserAccountLoginResponse,
    },
    repositories::mdn_users::{
        MdnUserAccountRepositoryImpl, MdnUsersRepository,
    },
    services::account::MdnUserAccountService,
};
use crate::{
    domain::mdn_authority::utils::MdnSignaturesService, error::MdnCentralResult,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnUserAccountController {
    rdb_storage: RbdStorage,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnUserAccountController {
    pub fn new(
        rdb_storage: RbdStorage,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mdn_central_authority_signature,
        }
    }
    pub fn user_account_service<'a, C: ConnectionTrait>(
        tx: &'a C,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> MdnUserAccountService<'a> {
        MdnUserAccountService::new(
            Box::new(Self::user_account_repository(tx)),
            mdn_central_authority_signature.clone(),
        )
    }
    pub fn user_account_repository<'a, C: ConnectionTrait>(
        tx: &'a C,
    ) -> impl MdnUsersRepository + 'a {
        MdnUserAccountRepositoryImpl::new(tx)
    }

    pub async fn register_user(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let res = Self::user_account_service(
            &*self.rdb_storage.connection(),
            self.mdn_central_authority_signature.clone(),
        )
        .create_customer_account(payload)
        .await?;

        Ok(res)
    }

    pub async fn login_user(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let res = Self::user_account_service(
            &*self.rdb_storage.connection(),
            self.mdn_central_authority_signature.clone(),
        )
        .user_login(payload)
        .await?;

        Ok(res)
    }

    pub async fn _authorize_user_login_request(
        &self,
        payload: AuthorizeUserRequest,
    ) -> MdnCentralResult<AuthorizeUserResponse> {
        let res = Self::user_account_service(
            &*self.rdb_storage.connection(),
            self.mdn_central_authority_signature.clone(),
        )
        ._authorize_user_account(&payload.auth_token)
        .await?;

        Ok(res)
    }

    pub async fn authorize_user_token(
        &self,
        token: String,
    ) -> MdnCentralResult<LoggedInMdnUser> {
        let res = Self::user_account_service(
            &*self.rdb_storage.connection(),
            self.mdn_central_authority_signature.clone(),
        )
        .authorize_user_token(&token)
        .await?;

        Ok(res)
    }
}
