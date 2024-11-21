use super::client::{SecretsManagerClient, SimpleFileSecretsManagerClient};
use clap::Parser;
use mee_crypto::{jwk::JwkOps, jwt::ToJwk};
use mee_data_sync::iroh::utils::create_iroh_secret_key;

#[derive(Debug, Clone, Parser)]
#[command(author, version, about, long_about = None)]
pub struct KeyGenInitParams {
    #[arg(env, long)]
    pub jwk_auth_signature_secret_path: String,

    #[arg(env, long)]
    pub iroh_signature_secret_path: Option<String>,

    #[arg(env, long)]
    pub did_id_secret_path: Option<String>,

    #[arg(env, long)]
    pub signatures_secret_path_test_folder: Option<String>,
}

pub async fn keygen_init(params: KeyGenInitParams) -> anyhow::Result<()> {
    let KeyGenInitParams {
        jwk_auth_signature_secret_path,
        iroh_signature_secret_path,
        signatures_secret_path_test_folder,
        did_id_secret_path,
    } = params;

    if let Some(signatures_secret_path_test_folder) = signatures_secret_path_test_folder {
        let secret_mng_client =
            SimpleFileSecretsManagerClient::new(signatures_secret_path_test_folder);

        let jwk = match secret_mng_client
            .get_secret(&jwk_auth_signature_secret_path)
            .await?
        {
            Some(jwk) => serde_json::from_slice(&jwk)?,
            None => {
                let jwk: mee_crypto::jwk::Jwk =
                    mee_crypto::asymm::ed25519::Ed25519Keypair::new().to_jwk()?;

                let jwk_bytes = serde_json::to_vec(&jwk)?;

                secret_mng_client
                    .set_secret(&jwk_auth_signature_secret_path, jwk_bytes)
                    .await?;

                jwk
            }
        };

        if let Some(did_id_secret_path) = did_id_secret_path {
            if secret_mng_client
                .get_secret(&did_id_secret_path)
                .await?
                .is_none()
            {
                let did = mee_did::did_key::generate_from_jwk(jwk.to_public_key()?)?;

                secret_mng_client
                    .set_secret(&did_id_secret_path, did.as_bytes().to_vec())
                    .await?;
            }
        }

        if let Some(iroh_signature_secret_path) = iroh_signature_secret_path {
            let iroh_sk = secret_mng_client
                .get_secret(&iroh_signature_secret_path)
                .await?;

            if iroh_sk.is_none() {
                let sk = create_iroh_secret_key();

                secret_mng_client
                    .set_secret(&iroh_signature_secret_path, sk.to_bytes().to_vec())
                    .await?;
            }
        }
    }

    Ok(())
}
