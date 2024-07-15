use super::account::{
    api_middlewares::LoggedInUser,
    api_types::{
        CreateUserAccountRequest, UserAccountLoginRequest,
        UserAccountLoginResponse,
    },
    repository::{UserAccountRepository, UserAccountRepositoryImpl},
    service::UserAccountService,
};
use crate::error::MeeUserManagerResult;
use mee_db_utils::sql_storage::IRbdStorage;
use mee_authority_secrets::MeeAuthoritySignatureService;
use sea_orm::{ConnectionTrait, TransactionTrait};
use service_utils::mee_user_manager::api_types::{
    AuthorizeUserRequest, AuthorizeUserResponse,
};
use std::sync::Arc;

#[derive(Clone)]
pub struct UserController {
    rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
    mee_authority_signature:
        Arc<dyn MeeAuthoritySignatureService + Send + Sync>,
}

impl UserController {
    pub fn new(
        rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
        mee_authority_signature: Arc<
            dyn MeeAuthoritySignatureService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mee_authority_signature,
        }
    }
    pub fn user_account_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> UserAccountService<'a> {
        UserAccountService::new(
            Box::new(self.user_account_repository(tx)),
            self.mee_authority_signature.clone(),
        )
    }
    pub fn user_account_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl UserAccountRepository + 'a {
        UserAccountRepositoryImpl::new(tx)
    }
    pub async fn register_user(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MeeUserManagerResult<UserAccountLoginResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let user_account_service = this.user_account_service(tx);
                    let res = user_account_service
                        .create_customer_account(payload)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn login_user(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MeeUserManagerResult<UserAccountLoginResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let user_account_service = this.user_account_service(tx);
                    let res = user_account_service.user_login(payload).await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn authorize_user_login_request(
        &self,
        payload: AuthorizeUserRequest,
    ) -> MeeUserManagerResult<AuthorizeUserResponse> {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let user_account_service = this.user_account_service(tx);
                    let res = user_account_service
                        .authorize_user_account(&payload.auth_token)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
    pub async fn authorize_user_token(
        &self,
        token: String,
    ) -> MeeUserManagerResult<LoggedInUser> {
        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                let this = self.clone();
                Box::pin(async move {
                    let res = this
                        .user_account_service(tx)
                        .authorize_user_token(&token)
                        .await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
}
