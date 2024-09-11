use super::{
    api_types::{
        CreateProviderAccountRequest, ProviderAccountLoginRequest,
        ProviderAccountLoginResponse,
    },
    domain::ProviderAccountDomainModel,
    repository::ProviderAccountRepository,
};
use crate::{
    db_models::mee_network_providers,
    domain::provider::account::dto::CreateProviderAccountDto,
    error::{MeeProviderManagerErr, MeeProviderManagerResult},
};
use argon2::{
    password_hash::{rand_core::OsRng, SaltString},
    Argon2, PasswordHash, PasswordHasher, PasswordVerifier,
};
use biscuit_auth::macros::biscuit;
use chrono::{Duration, Utc};
use mee_crypto::biscuit_auth::biscuit_ed_keypair_from_jwk;
use mee_secrets_manager::signatures_service::SignaturesService;
use service_utils::mee_provider_manager::{
    auth::MeeProviderAuthorizer, domain::ProviderRole,
};
use std::sync::Arc;

pub struct ProviderAccountService<'a> {
    provider_account_repository:
        Box<dyn ProviderAccountRepository + Send + Sync + 'a>,
    mee_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
}

impl<'a> ProviderAccountService<'a> {
    pub fn new(
        provider_account_repository: Box<
            dyn ProviderAccountRepository + Send + Sync + 'a,
        >,
        mee_authority_signature: Arc<dyn SignaturesService + Send + Sync>,
    ) -> Self {
        Self {
            provider_account_repository,
            mee_authority_signature,
        }
    }
    pub async fn get_account_by_meeid_err(
        &self,
        meeid: &str,
    ) -> MeeProviderManagerResult<mee_network_providers::Model> {
        self.provider_account_repository
            .get_account_by_meeid_err(meeid)
            .await
    }
    async fn make_login_response(
        &self,
        provider: ProviderAccountDomainModel,
    ) -> MeeProviderManagerResult<ProviderAccountLoginResponse> {
        let mee_sig = self.mee_authority_signature.get_jwk_signature().await?;

        let root_key = mee_sig
            .as_ref()
            .and_then(|s| biscuit_ed_keypair_from_jwk(s).transpose())
            .transpose()?
            .ok_or(MeeProviderManagerErr::MeeAuthoritySignatureProblem(
                "Missing signature key pair".to_string(),
            ))?;

        // String time format is not allowed in the biscuit! macro
        // because the time is a distinct type in Datalog
        let expires: std::time::SystemTime =
            (Utc::now() + Duration::days(14)).into();

        let biscuit = biscuit!(
            r#"
            provider({provider_meeid});

            role({role});

            check if time($time), $time <= {expiration_time};
            "#,
            role = provider.provider_role.to_string(),
            provider_meeid = provider.provider_meeid.clone(),
            expiration_time = expires,
        );

        let biscuit = biscuit.build(&root_key)?;

        let res = ProviderAccountLoginResponse {
            meeid: provider.provider_meeid,
            auth_token: biscuit.to_base64()?,
        };

        Ok(res)
    }

    pub async fn provider_login(
        &self,
        ProviderAccountLoginRequest { email, password }: ProviderAccountLoginRequest,
    ) -> MeeProviderManagerResult<ProviderAccountLoginResponse> {
        let Some(provider) = self
            .provider_account_repository
            .get_account_by_email(&email)
            .await?
        else {
            return Err(MeeProviderManagerErr::ProviderAccountNotFound(email));
        };

        let parsed_hash = PasswordHash::new(&provider.password)
            .map_err(MeeProviderManagerErr::PasswordHashing)?;

        if let Err(e) =
            Argon2::default().verify_password(password.as_bytes(), &parsed_hash)
        {
            tracing::error!("Provider's password verification error: {e}");

            Err(MeeProviderManagerErr::ProviderAccountInvalidPassword)?;
        }

        let res = self.make_login_response(provider.try_into()?).await?;

        Ok(res)
    }
    pub async fn create_customer_account(
        &self,
        CreateProviderAccountRequest {
            email,
            password,
            provider_name,
        }: CreateProviderAccountRequest,
    ) -> MeeProviderManagerResult<ProviderAccountLoginResponse> {
        if self
            .provider_account_repository
            .get_account_by_email(&email)
            .await?
            .is_some()
        {
            return Err(MeeProviderManagerErr::ProviderAccountAlreadyExists(
                email,
            ));
        }

        let password_salt = SaltString::generate(&mut OsRng);
        let argon2 = Argon2::default();

        let password_hash = argon2
            .hash_password(password.as_bytes(), &password_salt)
            .map_err(MeeProviderManagerErr::PasswordHashing)?
            .to_string();

        let res = self
            .provider_account_repository
            .create_account(CreateProviderAccountDto {
                provider_meeid: format!(
                    "meeid_provider_{}",
                    uuid::Uuid::new_v4()
                ),
                provider_email: email,
                provider_name,
                provider_role: ProviderRole::Customer,
                is_active: true,
                salt: password_salt.to_string(),
                password: password_hash,
            })
            .await?;

        self.make_login_response(res.try_into()?).await
    }
}

impl<'a> MeeProviderAuthorizer for ProviderAccountService<'a> {
    fn mee_authority_signature(
        &self,
    ) -> Arc<dyn SignaturesService + Send + Sync> {
        self.mee_authority_signature.clone()
    }
}
