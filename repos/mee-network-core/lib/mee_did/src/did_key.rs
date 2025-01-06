use crate::error::{MeeDidErr, MeeDidResult};
use didkit::{Source, DID_METHODS};
use mee_crypto::{
    jwk::{Jwk, JwkOps},
    jwt::ToJwk,
};

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

pub fn generate_ed25519() -> MeeDidResult<(String, Jwk)> {
    let jwk: Jwk = mee_crypto::asymm::ed25519::Ed25519Keypair::new().to_jwk()?;

    let did = generate_from_jwk(jwk.to_public_key()?)?;

    Ok((did, jwk))
}

#[cfg(test)]
mod tests {
    use crate::{
        did_key::generate_ed25519,
        universal_resolver::{DIDResolverExt, UniversalDidResolver},
    };
    use didkit::VerificationRelationship;

    #[test]
    fn generate_did_key_from_jwk_ed25519() {
        println!("{}", generate_ed25519().unwrap().0);
    }

    #[tokio::test]
    async fn get_did_key_id() {
        let (did, _) = generate_ed25519().unwrap();

        let d = UniversalDidResolver
            .resolve_did_for_relation(&did, VerificationRelationship::Authentication)
            .await
            .unwrap();

        println!("{d}");

        assert_eq!(format!("{}#{}", did, did.split(":").last().unwrap()), d);
    }
}
