use crate::{
    error::{MdnIdentityAgentErr, MdnIdentityAgentResult},
    mdn_cloud::mdn_user::{
        api_client::MdnUserAccountApiClient,
        api_types::{CreateUserAccountRequest, UserAccountLoginRequest},
        auth_utils::MdnCloudUserIdToken,
    },
    native_agent::local_storage::user_local_db::MdnUserLocalDb,
};
use async_trait::async_trait;
use mee_crypto::{
    jwk::{Jwk, JwkOps},
    jwt::ToJwk,
};
use mee_data_sync::iroh::{key::SecretKey, utils::create_iroh_secret_key};
use std::sync::Arc;

#[async_trait]
pub trait MdnUserAccountManager {
    // signatures
    async fn login(&self, email: String, password: String) -> MdnIdentityAgentResult;
    async fn register(&self, email: String, password: String) -> MdnIdentityAgentResult;
    async fn get_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn get_user_device_did(&self) -> MdnIdentityAgentResult<String>;
    async fn get_user_device_secret_key(&self) -> MdnIdentityAgentResult<Jwk>;
    async fn get_mdn_cloud_controller_signature_key(&self) -> MdnIdentityAgentResult<Jwk>;
    async fn get_iroh_node_key(&self) -> MdnIdentityAgentResult<SecretKey>;

    // defaults
    async fn get_user_auth_token_required(&self) -> MdnIdentityAgentResult<String> {
        Ok(self.get_user_auth_token().await?.ok_or_else(|| {
            MdnIdentityAgentErr::MdnUserIdm("Missing user auth token".to_string())
        })?)
    }
    async fn get_user_auth_decoded_token_required(
        &self,
    ) -> MdnIdentityAgentResult<MdnCloudUserIdToken> {
        let token = self.get_user_auth_token_required().await?;
        let jwk = self.get_mdn_cloud_controller_signature_key().await?;
        let token = MdnCloudUserIdToken::decode(&token, jwk)?;

        Ok(token)
    }
}

pub struct MdnUserAccountManagerDefaultImpl {
    user_local_db: Arc<dyn MdnUserLocalDb + Send + Sync>,
    mdn_user_account_api_client: Arc<dyn MdnUserAccountApiClient + Send + Sync>,
}

impl MdnUserAccountManagerDefaultImpl {
    pub fn new(
        user_local_db: Arc<dyn MdnUserLocalDb + Send + Sync>,
        mdn_user_account_api_client: Arc<dyn MdnUserAccountApiClient + Send + Sync>,
    ) -> Self {
        Self {
            user_local_db,
            mdn_user_account_api_client,
        }
    }
}

#[async_trait]
impl MdnUserAccountManager for MdnUserAccountManagerDefaultImpl {
    async fn login(&self, email: String, password: String) -> MdnIdentityAgentResult {
        let res = self
            .mdn_user_account_api_client
            .login(UserAccountLoginRequest {
                email,
                password,
                custodian_storage_did: self.get_user_device_did().await?,
            })
            .await?;

        self.user_local_db
            .write_mdn_user_auth_token(&res.auth_token)
            .await?;

        Ok(())
    }
    async fn register(&self, email: String, password: String) -> MdnIdentityAgentResult {
        let res = self
            .mdn_user_account_api_client
            .register(CreateUserAccountRequest {
                email,
                password,
                phone: None,
                custodian_storage_did: self.get_user_device_did().await?,
            })
            .await?;

        self.user_local_db
            .write_mdn_user_auth_token(&res.auth_token)
            .await?;

        Ok(())
    }
    async fn get_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>> {
        Ok(self.user_local_db.read_mdn_user_auth_token().await?)
    }
    async fn get_user_device_secret_key(&self) -> MdnIdentityAgentResult<Jwk> {
        Ok(
            if let Some(res) = self.user_local_db.read_user_device_secret_key().await? {
                res
            } else {
                let jwk: Jwk = mee_crypto::asymm::ed25519::Ed25519Keypair::new().to_jwk()?;

                self.user_local_db
                    .write_user_device_secret_key(jwk.clone())
                    .await?;

                jwk
            },
        )
    }
    async fn get_user_device_did(&self) -> MdnIdentityAgentResult<String> {
        Ok(
            if let Some(res) = self.user_local_db.read_user_device_did().await? {
                res
            } else {
                let did = mee_did::did_key::generate_from_jwk(
                    self.get_user_device_secret_key().await?.to_public_key()?,
                )?;

                self.user_local_db.write_user_device_did(&did).await?;

                did
            },
        )
    }
    async fn get_iroh_node_key(&self) -> MdnIdentityAgentResult<SecretKey> {
        Ok(
            if let Some(res) = self.user_local_db.read_iroh_node_secret_key().await? {
                res
            } else {
                let sk = create_iroh_secret_key();

                self.user_local_db
                    .write_iroh_node_secret_key(sk.clone())
                    .await?;

                sk
            },
        )
    }
    async fn get_mdn_cloud_controller_signature_key(&self) -> MdnIdentityAgentResult<Jwk> {
        // TODO check JWK key operation
        let jwk = self
            .mdn_user_account_api_client
            .mdn_jwks()
            .await?
            .keys
            .pop()
            .ok_or_else(|| {
                MdnIdentityAgentErr::MdnUserIdm("Missing MDN authority signature key".to_string())
            })?;

        Ok(jwk)
    }
}
