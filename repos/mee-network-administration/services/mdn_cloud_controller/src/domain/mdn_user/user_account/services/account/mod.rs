use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::services::account::MdnCustodiansService,
            identity_context::repositories::mdn_context_scoped_ids::{
                CreateScopedIdDto, MdnContextScopedIdsRepository,
            },
        },
        mdn_user::user_account::{
            api::{
                middlewares::DirectlyLoggedInMdnUser,
                types::{
                    AuthorizeUserResponse, CreateUserAccountRequest,
                    UserAccountLoginRequest, UserAccountLoginResponse,
                },
            },
            repositories::{
                mdn_user_signing_pub_keys::MdnUserSigningPubKeysRepository,
                mdn_users::{CreateUserAccountDto, MdnUsersRepository},
            },
        },
    },
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use argon2::{
    password_hash::{rand_core::OsRng, SaltString},
    Argon2, PasswordHash, PasswordHasher, PasswordVerifier,
};
use mdn_identity_agent::mdn_cloud::mdn_user::auth_utils::{
    EncodeMdnCloudUserIdTokenParams, MdnCloudUserIdToken,
};
use mee_did::universal_resolver::{
    DIDResolverExt, UniversalDidResolver, VerificationRelationship,
};
use service_models::{MdnUserAccountRole, UserAccountDomainModel};
use std::sync::Arc;

pub mod service_models;

pub struct MdnUserAccountService<'a> {
    user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
    mdn_custodians_service: MdnCustodiansService<'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
    mdn_user_signing_pub_keys_repository:
        Box<dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a>,
}

impl<'a> MdnUserAccountService<'a> {
    pub fn new(
        user_account_repository: Box<dyn MdnUsersRepository + Send + Sync + 'a>,
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        mdn_custodians_service: MdnCustodiansService<'a>,
        mdn_context_scoped_ids_repository: Box<
            dyn MdnContextScopedIdsRepository + Send + Sync + 'a,
        >,
        mdn_user_signing_pub_keys_repository: Box<
            dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            mdn_custodians_service,
            user_account_repository,
            mdn_cloud_controller_authority_signature,
            mdn_context_scoped_ids_repository,
            mdn_user_signing_pub_keys_repository,
        }
    }
    pub async fn check_user_did(
        &self,
        user_did: &str,
        user_account_uid: &str,
    ) -> MdnCloudControllerResult<bool> {
        let user_account_id = self
            .get_account_by_uid_required(user_account_uid)
            .await?
            .mdn_user_id;

        let res = self
            .mdn_user_signing_pub_keys_repository
            .list_pub_keys(user_account_id)
            .await?
            .into_iter()
            .any(|k| k.mdn_user_signing_pub_key_did == user_did);

        Ok(res)
    }
    async fn make_login_response(
        &self,
        user: UserAccountDomainModel,
        // TODO validate DID key material possession proof?
        custodian_storage_did: String,
    ) -> MdnCloudControllerResult<UserAccountLoginResponse> {
        let mdn_did = self
            .mdn_cloud_controller_authority_signature
            .mee_sig_did()
            .await?;

        let db_user =
            self.get_account_by_uid_required(&user.mdn_user_uid).await?;

        let mdn_user_custodian = self
            .mdn_custodians_service
            .get_user_custodian(db_user.mdn_user_id)
            .await?;

        let mdn_user_context_scoped_uid = self
            .mdn_context_scoped_ids_repository
            .get_context_scoped_id_by_custodian_id(
                db_user.mdn_user_id,
                mdn_user_custodian.mdn_custodian_id,
            )
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MdnUserAccountManagement(format!(
                    "missing connection between user({}) and custodian({})",
                    &db_user.mdn_user_uid,
                    &mdn_user_custodian.mdn_custodian_uid,
                ))
            })?
            .mdn_context_scoped_uid;

        let auth_token =
            MdnCloudUserIdToken::encode(EncodeMdnCloudUserIdTokenParams {
                mdn_user_custodian_uid: mdn_user_custodian.mdn_custodian_uid,
                mdn_user_context_scoped_uid,
                sub: user.mdn_user_uid.clone(),
                aud: custodian_storage_did,
                mdn_user_role: user.mdn_user_role.to_string(),
                sign_key: self
                    .mdn_cloud_controller_authority_signature
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
            custodian_storage_did,
        }: UserAccountLoginRequest,
    ) -> MdnCloudControllerResult<UserAccountLoginResponse> {
        let Some(user) = self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
        else {
            return Err(MdnCloudControllerErr::MdnUserAccountNotFound(email));
        };

        let parsed_hash = PasswordHash::new(&user.password)
            .map_err(MdnCloudControllerErr::PasswordHashing)?;

        if let Err(_e) =
            Argon2::default().verify_password(password.as_bytes(), &parsed_hash)
        {
            Err(MdnCloudControllerErr::MdnUserAccountInvalidPassword)?;
        }

        let res = self
            .make_login_response(user.try_into()?, custodian_storage_did)
            .await?;

        Ok(res)
    }
    pub async fn create_customer_account(
        &self,
        CreateUserAccountRequest {
            email,
            phone,
            password,
            custodian_storage_did,
        }: CreateUserAccountRequest,
    ) -> MdnCloudControllerResult<UserAccountLoginResponse> {
        if self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
            .is_some()
        {
            return Err(MdnCloudControllerErr::MdnUserAccountAlreadyExists(
                email,
            ));
        }

        let password_salt = SaltString::generate(&mut OsRng);
        let argon2 = Argon2::default();

        let password_hash = argon2
            .hash_password(password.as_bytes(), &password_salt)
            .map_err(MdnCloudControllerErr::PasswordHashing)?
            .to_string();

        let res = self
            .user_account_repository
            .create_account(CreateUserAccountDto {
                // TODO currently used as context custodian name,
                // because we somehow need to show some readable name for custodian holding the context
                mdn_user_name: format!("Custodian public name for {}", &email),
                mdn_user_email: email,
                mdn_user_role: MdnUserAccountRole::Customer,
                mdn_user_phone: phone,
                is_user_active: true,
                is_user_verified: false,
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
                mdn_user_id: res.mdn_user_id,
                for_mdn_custodian_id: user_custodian.mdn_custodian_id,
            })
            .await?;

        self.make_login_response(res.try_into()?, custodian_storage_did)
            .await
    }
    pub async fn _authorize_user_account(
        &self,
        token: &str,
    ) -> MdnCloudControllerResult<AuthorizeUserResponse> {
        let user = self.authorize_user_token(token).await?;

        let user = self
            .user_account_repository
            .get_account_by_uid(&user.mdn_user_uid)
            .await?
            .ok_or(MdnCloudControllerErr::MdnUserAccountNotFound(
                user.mdn_user_uid,
            ))?;

        Ok(user.into())
    }
    pub async fn authorize_user_token(
        &self,
        token: &str,
    ) -> MdnCloudControllerResult<DirectlyLoggedInMdnUser> {
        let mee_sig = self
            .mdn_cloud_controller_authority_signature
            .mee_sig()
            .await?;

        let mdn_user_id_token = MdnCloudUserIdToken::decode(token, mee_sig)?;

        let user = DirectlyLoggedInMdnUser {
            mdn_user_uid: mdn_user_id_token.sub,
            _mdn_user_account_role: mdn_user_id_token.mdn_user_role.parse()?,
            mdn_user_custodian_uid: mdn_user_id_token.mdn_user_custodian_uid,
            mdn_custodian_storage_did: mdn_user_id_token.aud,
        };

        Ok(user)
    }

    pub async fn get_account_by_uid(
        &self,
        uid: &str,
    ) -> MdnCloudControllerResult<Option<crate::db_models::mdn_users::Model>>
    {
        self.user_account_repository.get_account_by_uid(uid).await
    }

    pub async fn get_account_by_uid_required(
        &self,
        uid: &str,
    ) -> MdnCloudControllerResult<crate::db_models::mdn_users::Model> {
        self.get_account_by_uid(uid).await?.ok_or_else(|| {
            MdnCloudControllerErr::MissingDbEntity(format!("{uid}"))
        })
    }
}
