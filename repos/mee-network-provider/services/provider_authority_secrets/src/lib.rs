use biscuit_auth::KeyPair;
use identity_jose::jwk::Jwk;
use mee_crypto::biscuit_auth::biscuit_ed_keypair_from_jwk;
use mee_secrets_manager::client::SecretsManagerClient;
use std::sync::Arc;

#[async_trait::async_trait]
pub trait ProviderAuthoritySignatureService {
    async fn get_signature(&self) -> anyhow::Result<Option<Jwk>>;
    async fn get_signature_for_biscuit(
        &self,
    ) -> anyhow::Result<Option<KeyPair>>;
}

#[derive(Clone)]
pub struct ProviderAuthoritySignatureServiceDefault {
    secret_path: String,
    secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
}

impl ProviderAuthoritySignatureServiceDefault {
    pub fn new(
        secret_path: String,
        secrets_manager: Arc<dyn SecretsManagerClient + Send + Sync>,
    ) -> Self {
        Self {
            secret_path,
            secrets_manager,
        }
    }
}

#[async_trait::async_trait]
impl ProviderAuthoritySignatureService
    for ProviderAuthoritySignatureServiceDefault
{
    async fn get_signature(&self) -> anyhow::Result<Option<Jwk>> {
        let Some(jwk) =
            self.secrets_manager.get_secret(&self.secret_path).await?
        else {
            return Ok(None);
        };

        let jwk: Jwk = serde_json::from_slice(&jwk)?;

        Ok(Some(jwk))
    }
    async fn get_signature_for_biscuit(
        &self,
    ) -> anyhow::Result<Option<KeyPair>> {
        let keypair = self.get_signature().await?;

        let keypair = keypair
            .as_ref()
            .and_then(|k| biscuit_ed_keypair_from_jwk(k).transpose())
            .transpose()?;

        Ok(keypair)
    }
}
