use super::client::{SecretsManagerClient, SimpleFileSecretsManagerClient};
use biscuit_auth::KeyPair;
use clap::Parser;
use identity_jose::{
    jwk::{EdCurve, Jwk, JwkParamsOkp, JwkType, JwkUse},
    jws::JwsAlgorithm,
};
use mee_data_sync::iroh::utils::create_iroh_secret_key;

#[derive(Debug, Clone, Parser)]
#[command(author, version, about, long_about = None)]
pub struct KeyGenInitParams {
    #[arg(env, long)]
    pub jwk_auth_signature_secret_path: String,

    #[arg(env, long)]
    pub iroh_signature_secret_path: Option<String>,

    #[arg(env, long)]
    pub signatures_secret_path_test_folder: Option<String>,
}

pub async fn keygen_init(params: KeyGenInitParams) -> anyhow::Result<()> {
    let KeyGenInitParams {
        jwk_auth_signature_secret_path,
        iroh_signature_secret_path,
        signatures_secret_path_test_folder,
    } = params;

    if let Some(signatures_secret_path_test_folder) = signatures_secret_path_test_folder {
        let secret_mng_client =
            SimpleFileSecretsManagerClient::new(signatures_secret_path_test_folder);

        let jwk = secret_mng_client
            .get_secret(&jwk_auth_signature_secret_path)
            .await?;

        if jwk.is_none() {
            let ed25519_keypair = KeyPair::new();

            let mut keypair_jwk = Jwk::new(JwkType::Okp);

            keypair_jwk.set_kid(uuid::Uuid::new_v4().to_string());
            keypair_jwk.set_use(JwkUse::Signature);

            keypair_jwk.set_params(JwkParamsOkp {
                crv: EdCurve::Ed25519.name().to_owned(),
                x: identity_jose::jwu::encode_b64(ed25519_keypair.public().to_bytes()),
                d: Some(identity_jose::jwu::encode_b64(
                    ed25519_keypair.private().to_bytes(),
                )),
            })?;

            keypair_jwk.set_alg(JwsAlgorithm::EdDSA.to_string());

            let jwk = serde_json::to_vec(&keypair_jwk)?;

            secret_mng_client
                .set_secret(&jwk_auth_signature_secret_path, jwk)
                .await?;
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
