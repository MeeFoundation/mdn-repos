use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::account::services::account::MdnCustodiansService,
        mdn_user::{
            identity_context::repositories::mdn_context_scoped_ids::{
                CreateScopedIdDto, MdnContextScopedIdsRepository,
            },
            user_account::{
                api::{
                    middlewares::DirectlyLoggedInMdnUser,
                    types::{
                        AuthorizeUserResponse, CreateUserAccountRequest,
                        UserAccountLoginRequest, UserAccountLoginResponse,
                    },
                },
                repositories::mdn_users::{
                    CreateUserAccountDto, MdnUsersRepository,
                },
            },
        },
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use argon2::{
    password_hash::{rand_core::OsRng, SaltString},
    Argon2, PasswordHash, PasswordHasher, PasswordVerifier,
};
use mdn_identity_agent::mdn_cloud::user_account::auth_utils::{
    decode_mdn_cloud_user_id_token, encode_mdn_cloud_user_id_token,
    EncodeMdnCloudUserIdTokenParams,
};
use mee_did::universal_resolver::{
    DIDResolverExt, UniversalDidResolver, VerificationRelationship,
};
use service_models::{MdnUserAccountRole, UserAccountDomainModel};
use std::sync::Arc;

pub mod service_models;

pub struct MdnUserAccountService<'a> {
    user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
    mdn_custodians_service: MdnCustodiansService<'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
}

impl<'a> MdnUserAccountService<'a> {
    pub fn new(
        user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        mdn_custodians_service: MdnCustodiansService<'a>,
        mdn_context_scoped_ids_repository: Box<
            dyn MdnContextScopedIdsRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            mdn_custodians_service,
            user_account_repository,
            mdn_central_authority_signature,
            mdn_context_scoped_ids_repository,
        }
    }
    async fn make_login_response(
        &self,
        user: UserAccountDomainModel,
        device_did: String,
    ) -> MdnCentralResult<UserAccountLoginResponse> {
        let mdn_did =
            self.mdn_central_authority_signature.mee_sig_did().await?;

        let db_user =
            self.get_account_by_uid_required(&user.mdn_user_uid).await?;

        let mdn_user_custodian_uid = self
            .mdn_custodians_service
            .get_user_custodian(db_user.mdn_user_id)
            .await?
            .mdn_custodian_uid;

        let auth_token =
            encode_mdn_cloud_user_id_token(EncodeMdnCloudUserIdTokenParams {
                mdn_user_custodian_uid,
                sub: user.mdn_user_uid.clone(),
                aud: device_did,
                mdn_user_role: user.mdn_user_role.to_string(),
                sign_key: self
                    .mdn_central_authority_signature
                    .mee_sig()
                    .await?,
                kid: Some(
                    UniversalDidResolver
                        .resolve_did_for_relation(
                            &mdn_did,
                            VerificationRelationship::Authentication,
                        )
                        .await?,
                ),
                iss: mdn_did,
            })?;

        let res = UserAccountLoginResponse {
            mdn_user_uid: user.mdn_user_uid,
            auth_token,
        };

        Ok(res)
    }

    pub async fn user_login(
        &self,
        UserAccountLoginRequest {
            email,
            password,
            device_did,
        }: UserAccountLoginRequest,
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

        let res = self
            .make_login_response(user.try_into()?, device_did)
            .await?;

        Ok(res)
    }
    pub async fn create_customer_account(
        &self,
        CreateUserAccountRequest {
            email,
            phone,
            password,
            device_did,
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
                mdn_user_uid: format!("mdn_user-{}", uuid::Uuid::new_v4()),
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

        let user_custodian = self
            .mdn_custodians_service
            .create_user_custodian_account(res.mdn_user_id)
            .await?;

        self.mdn_context_scoped_ids_repository
            .create_context_scoped_id(CreateScopedIdDto {
                mdn_context_scoped_uid: format!(
                    "mdn_user_csi_self-${}",
                    uuid::Uuid::new_v4()
                ),
                mdn_user_id: res.mdn_user_id,
                for_mdn_custodian_id: user_custodian.mdn_custodian_id,
            })
            .await?;

        self.make_login_response(res.try_into()?, device_did).await
    }
    pub async fn _authorize_user_account(
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
    ) -> MdnCentralResult<DirectlyLoggedInMdnUser> {
        let mee_sig = self.mdn_central_authority_signature.mee_sig().await?;

        let mdn_user_id_token = decode_mdn_cloud_user_id_token(token, mee_sig)?;

        let user = DirectlyLoggedInMdnUser {
            mdn_user_uid: mdn_user_id_token.sub,
            _mdn_user_account_role: mdn_user_id_token.mdn_user_role.parse()?,
            mdn_user_custodian_uid: mdn_user_id_token.mdn_user_custodian_uid,
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
        self.get_account_by_uid(uid)
            .await?
            .ok_or_else(|| MdnCentralErr::MissingDbEntity(format!("{uid}")))
    }
}
