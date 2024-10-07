use crate::client::SecretsManagerClient;
use biscuit_auth::KeyPair;
use identity_jose::jwk::Jwk;
use mee_crypto::biscuit_auth::biscuit_ed_keypair_from_jwk;
use mee_data_sync::iroh::iroh_net::key::SecretKey;
use std::sync::Arc;

// TODO decouple iroh signature
#[async_trait::async_trait]
pub trait SignaturesService {
    async fn get_iroh_signature(&self) -> anyhow::Result<Option<SecretKey>>;
    async fn get_jwk_signature(&self) -> anyhow::Result<Option<Jwk>>;
    async fn get_biscuit_signature(&self) -> anyhow::Result<Option<KeyPair>>;
}

#[derive(Clone)]
pub struct SignaturesServiceDefault {
    secret_path: String,
    iroh_key_secret_path: Option<String>,
    secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
}

impl SignaturesServiceDefault {
    pub fn new(
        secret_path: String,
        iroh_key_secret_path: Option<String>,
        secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
    ) -> Self {
        Self {
            iroh_key_secret_path,
            secret_path,
            secrets_manager,
        }
    }
}

#[async_trait::async_trait]
impl SignaturesService for SignaturesServiceDefault {
    async fn get_jwk_signature(&self) -> anyhow::Result<Option<Jwk>> {
        let Some(jwk) = self.secrets_manager.get_secret(&self.secret_path).await? else {
            return Ok(None);
        };

        let jwk: Jwk = serde_json::from_slice(&jwk)?;

        Ok(Some(jwk))
    }
    async fn get_iroh_signature(&self) -> anyhow::Result<Option<SecretKey>> {
        if let Some(iroh_key_secret_path) = &self.iroh_key_secret_path {
            if let Some(iroh_sk) = self
                .secrets_manager
                .get_secret(&iroh_key_secret_path)
                .await?
            {
                let iroh_s = SecretKey::from_bytes(iroh_sk.as_slice().try_into()?);
                return Ok(Some(iroh_s));
            }
        }

        Ok(None)
    }
    async fn get_biscuit_signature(&self) -> anyhow::Result<Option<KeyPair>> {
        let keypair = self.get_jwk_signature().await?;

        let keypair = keypair
            .as_ref()
            .and_then(|k| biscuit_ed_keypair_from_jwk(k).transpose())
            .transpose()?;

        Ok(keypair)
    }
}
