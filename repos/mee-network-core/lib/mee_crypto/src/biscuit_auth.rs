use crate::error::MeeCryptoResult;
use biscuit_auth::{KeyPair, PrivateKey, PublicKey};
use identity_jose::jwk::Jwk;

pub fn biscuit_ed_keypair_from_jwk(
    jwk: &Jwk,
) -> MeeCryptoResult<Option<KeyPair>> {
    let Some(private_str) = jwk.try_okp_params()?.d.as_ref() else {
        return Ok(None);
    };

    let private_bytes = identity_jose::jwu::decode_b64(private_str)?;
    let root_key = KeyPair::from(&PrivateKey::from_bytes(&private_bytes)?);

    Ok(Some(root_key))
}

pub fn biscuit_ed_public_key_from_jwk(jwk: &Jwk) -> MeeCryptoResult<PublicKey> {
    let public_bytes =
        identity_jose::jwu::decode_b64(&jwk.try_okp_params()?.x)?;
    let public_key = PublicKey::from_bytes(&public_bytes)?;

    Ok(public_key)
}
