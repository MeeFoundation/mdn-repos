use biscuit_auth::KeyPair;
use clap::Parser;
use identity_jose::{
    jwk::{EdCurve, Jwk, JwkParamsOkp, JwkType, JwkUse},
    jws::JwsAlgorithm,
};
use mee_secrets_manager::client::{
    SecretsManagerClient, SimpleFileSecretsManagerClient,
};

#[derive(Debug, Clone, Parser)]
#[command(author, version, about, long_about = None)]
pub struct CliArgs {
    #[arg(env, long)]
    pub mee_signature_secret_path: String,

    #[arg(env, long)]
    pub mee_signature_secret_path_test_folder: Option<String>,
}

#[tokio::main(flavor = "current_thread")]
async fn main() {
    let CliArgs {
        mee_signature_secret_path,
        mee_signature_secret_path_test_folder,
    } = CliArgs::parse();

    if let Some(mee_signature_secret_path_test_folder) =
        mee_signature_secret_path_test_folder
    {
        let secret_mng_client = SimpleFileSecretsManagerClient::new(
            mee_signature_secret_path_test_folder,
        );

        let jwk = secret_mng_client
            .get_secret(&mee_signature_secret_path)
            .await
            .unwrap();

        if jwk.is_none() {
            let ed25519_keypair = KeyPair::new();

            let mut keypair_jwk = Jwk::new(JwkType::Okp);

            keypair_jwk.set_kid(uuid::Uuid::new_v4().to_string());
            keypair_jwk.set_use(JwkUse::Signature);

            keypair_jwk
                .set_params(JwkParamsOkp {
                    crv: EdCurve::Ed25519.name().to_owned(),
                    x: identity_jose::jwu::encode_b64(
                        ed25519_keypair.public().to_bytes(),
                    ),
                    d: Some(identity_jose::jwu::encode_b64(
                        ed25519_keypair.private().to_bytes(),
                    )),
                })
                .unwrap();

            keypair_jwk.set_alg(JwsAlgorithm::EdDSA.to_string());

            let jwk = serde_json::to_vec(&keypair_jwk).unwrap();

            secret_mng_client
                .set_secret(&mee_signature_secret_path, jwk)
                .await
                .unwrap();
        }
    }
}
