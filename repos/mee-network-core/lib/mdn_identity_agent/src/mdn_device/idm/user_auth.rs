use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::user_account::{
        api_client::MdnUserAccountApiClient,
        api_types::{CreateUserAccountRequest, UserAccountLoginRequest},
    },
    mdn_device::storage::user_local_db::MdnUserLocalDb,
};
use async_trait::async_trait;
use mee_data_sync::iroh::{iroh_net, utils::create_iroh_secret_key};
use std::sync::Arc;

#[async_trait]
pub trait MdnUserAccountManager {
    async fn login(&self, email: String, password: String) -> MdnIdentityAgentResult;
    async fn register(&self, email: String, password: String) -> MdnIdentityAgentResult;
    async fn get_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn get_user_device_did(&self) -> MdnIdentityAgentResult<String>;
    async fn get_iroh_node_key(&self) -> MdnIdentityAgentResult<iroh_net::key::SecretKey>;
}

pub struct MdnUserAccountManagerDefault {
    user_local_db: Arc<dyn MdnUserLocalDb + Send + Sync>,
    mdn_user_account_api_client: Arc<dyn MdnUserAccountApiClient + Send + Sync>,
}

impl MdnUserAccountManagerDefault {
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
impl MdnUserAccountManager for MdnUserAccountManagerDefault {
    async fn login(&self, email: String, password: String) -> MdnIdentityAgentResult {
        let res = self
            .mdn_user_account_api_client
            .login(UserAccountLoginRequest { email, password })
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
    async fn get_user_device_did(&self) -> MdnIdentityAgentResult<String> {
        Ok(
            if let Some(res) = self.user_local_db.read_mdn_user_auth_token().await? {
                res
            } else {
                let did = mee_did::did_key::generate_ed25519()?;

                self.user_local_db.write_user_device_did(&did).await?;

                did
            },
        )
    }
    async fn get_iroh_node_key(&self) -> MdnIdentityAgentResult<iroh_net::key::SecretKey> {
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
}
