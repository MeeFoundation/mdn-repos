use crate::error::{MeeDidErr, MeeDidResult};
use didkit::{Source, DID_METHODS};
use mee_crypto::{jwk::Jwk, jwt::ToJwk};

pub fn generate_from_jwk(public_key: Jwk) -> MeeDidResult<String> {
    let didkey = DID_METHODS.get("key").ok_or_else(|| MeeDidErr::DidMethod {
        error: "Missing did:key generator".to_string(),
    })?;

    let jwk = public_key.try_into()?;
    let did_source = Source::Key(&jwk);

    let did = didkey
        .generate(&did_source)
        .ok_or_else(|| MeeDidErr::DidMethod {
            error: "Missing did:key generation result".to_string(),
        })?;

    Ok(did)
}

pub fn generate_ed25519() -> MeeDidResult<String> {
    let jwk = mee_crypto::asymm::ed25519::Ed25519Keypair::new().to_jwk_public()?;

    Ok(generate_from_jwk(jwk)?)
}

#[test]
fn generate_did_key_from_jwk_ed25519() {
    println!("{}", generate_ed25519().unwrap());
}
