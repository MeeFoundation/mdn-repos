use super::{
    api_middlewares::LoggedInUser,
    api_types::{
        CreateUserAccountRequest, UserAccountLoginRequest,
        UserAccountLoginResponse,
    },
    domain::{UserAccountDomainModel, UserRole},
    repository::UserAccountRepository,
};
use crate::{
    domain::user::account::dto::CreateUserAccountDto,
    error::{MeeUserManagerErr, MeeUserManagerResult},
};
use argon2::{
    password_hash::{rand_core::OsRng, SaltString},
    Argon2, PasswordHash, PasswordHasher, PasswordVerifier,
};
use biscuit_auth::{macros::biscuit, Authorizer, AuthorizerLimits, Biscuit};
use chrono::{Duration, Utc};
use mee_crypto::biscuit_auth::biscuit_ed_keypair_from_jwk;
use mee_authority_secrets::MeeAuthoritySignatureService;
use service_utils::mee_user_manager::api_types::AuthorizeUserResponse;
use std::sync::Arc;

pub struct UserAccountService<'a> {
    user_account_repository: Box<dyn UserAccountRepository + Send + Sync + 'a>,
    mee_authority_signature:
        Arc<dyn MeeAuthoritySignatureService + Send + Sync>,
}

impl<'a> UserAccountService<'a> {
    pub fn new(
        user_account_repository: Box<
            dyn UserAccountRepository + Send + Sync + 'a,
        >,
        mee_authority_signature: Arc<
            dyn MeeAuthoritySignatureService + Send + Sync,
        >,
    ) -> Self {
        Self {
            user_account_repository,
            mee_authority_signature,
        }
    }
    async fn make_login_response(
        &self,
        user: UserAccountDomainModel,
    ) -> MeeUserManagerResult<UserAccountLoginResponse> {
        let mee_sig = self.mee_authority_signature.get_signature().await?;

        let root_key = mee_sig
            .as_ref()
            .and_then(|s| biscuit_ed_keypair_from_jwk(s).transpose())
            .transpose()?
            .ok_or(MeeUserManagerErr::MissingMeeAuthoritySignature)?;

        // String time format is not allowed in the biscuit! macro
        // because the time is a distinct type in Datalog
        let expires: std::time::SystemTime =
            (Utc::now() + Duration::days(14)).into();

        let biscuit = biscuit!(
            r#"
            user({user_meeid});

            role({role});

            check if time($time), $time <= {expiration_time};
            "#,
            role = user.user_role.to_string(),
            user_meeid = user.user_meeid.clone(),
            expiration_time = expires,
        );

        let biscuit = biscuit.build(&root_key)?;

        let res = UserAccountLoginResponse {
            meeid: user.user_meeid,
            auth_token: biscuit.to_base64()?,
        };

        Ok(res)
    }

    pub async fn user_login(
        &self,
        UserAccountLoginRequest { email, password }: UserAccountLoginRequest,
    ) -> MeeUserManagerResult<UserAccountLoginResponse> {
        let Some(user) = self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
        else {
            return Err(MeeUserManagerErr::UserAccountNotFound(email));
        };

        let parsed_hash = PasswordHash::new(&user.password)
            .map_err(MeeUserManagerErr::PasswordHashing)?;

        if let Err(_e) =
            Argon2::default().verify_password(password.as_bytes(), &parsed_hash)
        {
            Err(MeeUserManagerErr::UserAccountInvalidPassword)?;
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
    ) -> MeeUserManagerResult<UserAccountLoginResponse> {
        if self
            .user_account_repository
            .get_account_by_email(&email)
            .await?
            .is_some()
        {
            return Err(MeeUserManagerErr::UserAccountAlreadyExists(email));
        }

        let password_salt = SaltString::generate(&mut OsRng);
        let argon2 = Argon2::default();

        let password_hash = argon2
            .hash_password(password.as_bytes(), &password_salt)
            .map_err(MeeUserManagerErr::PasswordHashing)?
            .to_string();

        let res = self
            .user_account_repository
            .create_account(CreateUserAccountDto {
                user_meeid: format!("meeid_user_{}", uuid::Uuid::new_v4()),
                user_email: email,
                user_role: UserRole::Customer,
                user_phone: phone,
                is_active: true,
                salt: password_salt.to_string(),
                password: password_hash,
            })
            .await?;

        self.make_login_response(res.try_into()?).await
    }
    pub async fn authorize_user_account(
        &self,
        token: &str,
    ) -> MeeUserManagerResult<AuthorizeUserResponse> {
        let user = self.authorize_user_token(token).await?;

        let user = self
            .user_account_repository
            .get_account_by_meeid(&user.meeid)
            .await?
            .ok_or(MeeUserManagerErr::UserAccountNotFound(user.meeid))?;

        Ok(user.into())
    }
    pub async fn authorize_user_token(
        &self,
        token: &str,
    ) -> MeeUserManagerResult<LoggedInUser> {
        let pkey = self
            .mee_authority_signature
            .get_signature_for_biscuit()
            .await?
            .ok_or(MeeUserManagerErr::MissingMeeAuthoritySignature)?;

        let biscuit = Biscuit::from_base64(token, pkey.public())?;

        let mut users: Vec<(String, String)> = {
            let mut authorizer = Authorizer::new();

            authorizer.add_policy(
                format!(
                    r#"
                    allow if user($id), role($r), ["{}", "{}"].contains($r)
                "#,
                    UserRole::Admin,
                    UserRole::Customer
                )
                .as_str(),
            )?;

            authorizer.set_limits(AuthorizerLimits {
                max_time: std::time::Duration::from_millis(500),
                ..Default::default()
            });
            authorizer.set_time();
            authorizer.add_token(&biscuit)?;
            authorizer.authorize()?;

            authorizer.query("data($id, $rol) <- user($id), role($rol)")?
        };

        let (meeid, role) =
            users.pop().ok_or(MeeUserManagerErr::InvalidUserAuthToken)?;

        let user = LoggedInUser {
            meeid,
            role: role.parse()?,
        };

        Ok(user)
    }
}
