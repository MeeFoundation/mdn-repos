use super::{
    middlewares::DirectlyLoggedInMdnUser,
    types::{
        AuthorizeUserRequest, AuthorizeUserResponse, CreateUserAccountRequest,
        UserAccountLoginRequest, UserAccountLoginResponse,
    },
};
use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::{
                repositories::mdn_custodians::MdnCustodiansRepositoryImpl,
                services::account::MdnCustodiansService,
            },
            identity_context::repositories::mdn_context_scoped_ids::MdnContextScopedIdsRepositoryImpl,
        },
        mdn_user::user_account::{
            repositories::{
                mdn_user_signing_pub_keys::MdnUserSigningPubKeysRepositoryImpl,
                mdn_users::MdnUsersRepositoryImpl,
            },
            services::account::MdnUserAccountService,
        },
    },
    error::MdnCloudControllerResult,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnUserAccountController {
    rdb_storage: RbdStorage,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnUserAccountController {
    pub fn new(
        rdb_storage: RbdStorage,
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mdn_cloud_controller_authority_signature,
        }
    }
    pub fn user_account_service_factory<'a, C: ConnectionTrait>(
        tx: &'a C,
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> MdnUserAccountService<'a> {
        MdnUserAccountService::new(
            Box::new(MdnUsersRepositoryImpl::new(tx)),
            mdn_cloud_controller_authority_signature.clone(),
            Self::mdn_custodians_service_factory(tx),
            Box::new(MdnContextScopedIdsRepositoryImpl::new(tx)),
            Box::new(MdnUserSigningPubKeysRepositoryImpl::new(tx)),
        )
    }
    pub fn mdn_custodians_service_factory<'a, C: ConnectionTrait>(
        tx: &'a C,
    ) -> MdnCustodiansService<'a> {
        MdnCustodiansService::new(Box::new(MdnCustodiansRepositoryImpl::new(
            tx,
        )))
    }

    pub async fn register_user(
        &self,
        payload: CreateUserAccountRequest,
    ) -> MdnCloudControllerResult<UserAccountLoginResponse> {
        let res = Self::user_account_service_factory(
            &*self.rdb_storage.connection(),
            self.mdn_cloud_controller_authority_signature.clone(),
        )
        .create_customer_account(payload)
        .await?;

        Ok(res)
    }

    pub async fn login_user(
        &self,
        payload: UserAccountLoginRequest,
    ) -> MdnCloudControllerResult<UserAccountLoginResponse> {
        let res = Self::user_account_service_factory(
            &*self.rdb_storage.connection(),
            self.mdn_cloud_controller_authority_signature.clone(),
        )
        .user_login(payload)
        .await?;

        Ok(res)
    }

    pub async fn _authorize_user_login_request(
        &self,
        payload: AuthorizeUserRequest,
    ) -> MdnCloudControllerResult<AuthorizeUserResponse> {
        let res = Self::user_account_service_factory(
            &*self.rdb_storage.connection(),
            self.mdn_cloud_controller_authority_signature.clone(),
        )
        ._authorize_user_account(&payload.auth_token)
        .await?;

        Ok(res)
    }

    pub async fn authorize_user_token(
        &self,
        token: String,
    ) -> MdnCloudControllerResult<DirectlyLoggedInMdnUser> {
        let res = Self::user_account_service_factory(
            &*self.rdb_storage.connection(),
            self.mdn_cloud_controller_authority_signature.clone(),
        )
        .authorize_user_token(&token)
        .await?;

        Ok(res)
    }
}
