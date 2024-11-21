use crate::client::SecretsManagerClient;
use async_trait::async_trait;
use biscuit_auth::KeyPair;
use derive_builder::Builder;
use identity_jose::jwk::Jwk;
use mee_crypto::biscuit_auth::biscuit_ed_keypair_from_jwk;
use mee_data_sync::iroh::iroh_net::key::SecretKey;
use std::sync::Arc;

#[async_trait::async_trait]
pub trait SignaturesService {
    async fn get_iroh_signature(&self) -> anyhow::Result<Option<SecretKey>>;
    async fn get_source_jwk_signature(&self) -> anyhow::Result<Option<Jwk>>;
    async fn get_did_id_from_source_jwk(&self) -> anyhow::Result<Option<String>>;
    async fn get_biscuit_signature_from_source_jwk(&self) -> anyhow::Result<Option<KeyPair>>;
}

#[derive(Clone, Builder)]
pub struct SignaturesServiceConfig {
    jwk_secret_path: Option<String>,
    iroh_key_secret_path: Option<String>,
    did_id_secret_path: Option<String>,
}

#[derive(Clone, Builder)]
pub struct SignaturesServiceDefault {
    signatures_service_config: SignaturesServiceConfig,
    secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
}

impl SignaturesServiceDefault {
    pub fn new(
        signatures_service_config: SignaturesServiceConfig,
        secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
    ) -> Self {
        Self {
            signatures_service_config,
            secrets_manager,
        }
    }
}

#[async_trait]
impl SignaturesService for SignaturesServiceDefault {
    async fn get_source_jwk_signature(&self) -> anyhow::Result<Option<Jwk>> {
        if let Some(jwk_secret_path) = &self.signatures_service_config.jwk_secret_path {
            if let Some(jwk) = self.secrets_manager.get_secret(&jwk_secret_path).await? {
                return Ok(Some(serde_json::from_slice(&jwk)?));
            }
        }

        Ok(None)
    }
    async fn get_iroh_signature(&self) -> anyhow::Result<Option<SecretKey>> {
        if let Some(iroh_key_secret_path) = &self.signatures_service_config.iroh_key_secret_path {
            if let Some(iroh_sk) = self
                .secrets_manager
                .get_secret(&iroh_key_secret_path)
                .await?
            {
                return Ok(Some(SecretKey::from_bytes(iroh_sk.as_slice().try_into()?)));
            }
        }

        Ok(None)
    }
    async fn get_biscuit_signature_from_source_jwk(&self) -> anyhow::Result<Option<KeyPair>> {
        let Some(keypair) = &self.get_source_jwk_signature().await? else {
            return Ok(None);
        };

        Ok(biscuit_ed_keypair_from_jwk(keypair)?)
    }

    async fn get_did_id_from_source_jwk(&self) -> anyhow::Result<Option<String>> {
        if let Some(did_id_secret_path) = &self.signatures_service_config.did_id_secret_path {
            if let Some(did) = self.secrets_manager.get_secret(&did_id_secret_path).await? {
                return Ok(Some(String::from_utf8(did)?));
            }
        }

        Ok(None)
    }
}
