use crate::{
    domain::mdn_user::user_account::{
        api::account::middlewares::LoggedInMdnUser,
        api::account::types::{
            AuthorizeUserResponse, CreateUserAccountRequest,
            UserAccountLoginRequest, UserAccountLoginResponse,
        },
        repositories::mdn_users::{CreateUserAccountDto, MdnUsersRepository},
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use argon2::{
    password_hash::{rand_core::OsRng, SaltString},
    Argon2, PasswordHash, PasswordHasher, PasswordVerifier,
};
use mdn_identity_agent::mdn_cloud::user_auth::{
    decode_mdn_cloud_user_id_token, encode_mdn_cloud_user_id_token,
};
use mee_crypto::jwk::Jwk;
use mee_secrets_manager::signatures_service::SignaturesService;
use service_models::{MdnUserAccountRole, UserAccountDomainModel};
use std::sync::Arc;

pub mod service_models;

pub struct MdnUserAccountService<'a> {
    user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
    mdn_central_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
}

impl<'a> MdnUserAccountService<'a> {
    pub fn new(
        user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
        mee_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
    ) -> Self {
        Self {
            user_account_repository,
            mdn_central_authority_signature: mee_authority_signature,
        }
    }
    async fn mee_sig(&self) -> MdnCentralResult<Jwk> {
        Ok(self
            .mdn_central_authority_signature
            .get_jwk_signature()
            .await?
            .ok_or_else(|| MdnCentralErr::MissingMdnCentralAuthoritySignature)?
            .try_into()?)
    }
    async fn make_login_response(
        &self,
        user: UserAccountDomainModel,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let auth_token = encode_mdn_cloud_user_id_token(
            "TODO: url backed by OIDC config or DID".to_string(),
            user.mdn_user_uid.clone(),
            user.mdn_user_role.to_string(),
            self.mee_sig().await?,
        )?;

        let res = UserAccountLoginResponse {
            mdn_user_uid: user.mdn_user_uid,
            auth_token,
        };

        Ok(res)
    }

    pub async fn user_login(
        &self,
        UserAccountLoginRequest { email, password }: UserAccountLoginRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let Some(user) = self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
        else {
            return Err(MdnCentralErr::MdnUserAccountNotFound(email));
        };

        let parsed_hash = PasswordHash::new(&user.password)
            .map_err(MdnCentralErr::PasswordHashing)?;

        if let Err(_e) =
            Argon2::default().verify_password(password.as_bytes(), &parsed_hash)
        {
            Err(MdnCentralErr::MdnUserAccountInvalidPassword)?;
        }

        let res = self.make_login_response(user.try_into()?).await?;

        Ok(res)
    }
    pub async fn create_customer_account(
        &self,
        CreateUserAccountRequest {
            email,
            phone,
            password,
        }: CreateUserAccountRequest,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        if self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
            .is_some()
        {
            return Err(MdnCentralErr::MdnUserAccountAlreadyExists(email));
        }

        let password_salt = SaltString::generate(&mut OsRng);
        let argon2 = Argon2::default();

        let password_hash = argon2
            .hash_password(password.as_bytes(), &password_salt)
            .map_err(MdnCentralErr::PasswordHashing)?
            .to_string();

        let res = self
            .user_account_repository
            .create_account(CreateUserAccountDto {
                mdn_user_uid: format!("mdn_user_{}", uuid::Uuid::new_v4()),
                mdn_user_email: email,
                mdn_user_role: MdnUserAccountRole::Customer,
                mdn_user_phone: phone,
                is_user_active: true,
                is_user_verified: false,
                mdn_user_name: None,
                salt: password_salt.to_string(),
                password: password_hash,
            })
            .await?;

        self.make_login_response(res.try_into()?).await
    }
    pub async fn authorize_user_account(
        &self,
        token: &str,
    ) -> MdnCentralResult<AuthorizeUserResponse> {
        let user = self.authorize_user_token(token).await?;

        let user = self
            .user_account_repository
            .get_account_by_uid(&user.mdn_user_uid)
            .await?
            .ok_or(MdnCentralErr::MdnUserAccountNotFound(user.mdn_user_uid))?;

        Ok(user.into())
    }
    pub async fn authorize_user_token(
        &self,
        token: &str,
    ) -> MdnCentralResult<LoggedInMdnUser> {
        let mee_sig = self.mee_sig().await?;

        let mdn_user_id_token = decode_mdn_cloud_user_id_token(token, mee_sig)?;

        let user = LoggedInMdnUser {
            mdn_user_uid: mdn_user_id_token.sub,
            mdn_user_account_role: mdn_user_id_token.mdn_user_role.parse()?,
        };

        Ok(user)
    }

    pub async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCentralResult<Option<crate::db_models::mdn_users::Model>> {
        self.user_account_repository.get_account_by_uid(uid).await
    }

    pub async fn get_account_by_uid_required(
        &self,
        uid: &str,
    ) -> MdnCentralResult<crate::db_models::mdn_users::Model> {
        self.get_account_by_uid(uid).await?.ok_or_else(|| {
            MdnCentralErr::MissingDbEntity(format!("user with uid={uid}"))
        })
    }
}
