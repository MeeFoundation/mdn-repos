use super::{DerPrivateKey, DerPublicKey, Keypair, PemPrivateKey, PemPublicKey, Pkcs8};
use crate::{error::MeeCryptoResult, jwt::ToJwk};
use ed25519_dalek::{SigningKey, VerifyingKey};
use josekit::jwk::alg::ed::EdKeyPair;
use pkcs8::{EncodePrivateKey, EncodePublicKey};
use rand_core::OsRng;

pub const ED25519_CURVE: &str = "Ed25519";

type PRIVK = SigningKey;
type PUBK = VerifyingKey;

pub struct Ed25519Keypair {
    signing_key: PRIVK,
    verifying_key: PUBK,
}

impl Ed25519Keypair {
    pub fn new() -> Self {
        let mut csprng = OsRng {};
        let signing_key = SigningKey::generate(&mut csprng);
        let verifying_key = signing_key.verifying_key();

        Self {
            signing_key,
            verifying_key,
        }
    }
}

impl Keypair<PRIVK, PUBK> for Ed25519Keypair {
    fn private(&self) -> PRIVK {
        self.signing_key.clone()
    }

    fn public(&self) -> PUBK {
        self.verifying_key
    }
}

impl Pkcs8<PRIVK, PUBK> for Ed25519Keypair {
    fn pem_keypair(&self) -> MeeCryptoResult<(PemPrivateKey, PemPublicKey)> {
        let priv_bytes = ed25519::KeypairBytes {
            secret_key: self.private().to_bytes(),
            public_key: None,
        };
        let sec = priv_bytes.to_pkcs8_pem(pkcs8::LineEnding::LF)?;

        let ver = self
            .verifying_key
            .to_public_key_pem(pkcs8::LineEnding::LF)?;

        Ok((
            PemPrivateKey(sec.to_string()),
            PemPublicKey(ver.to_string()),
        ))
    }

    fn der_keypair(&self) -> MeeCryptoResult<(DerPrivateKey, DerPublicKey)> {
        let priv_bytes = ed25519::KeypairBytes {
            secret_key: self.private().to_bytes(),
            public_key: None,
        };
        let sec = priv_bytes.to_pkcs8_der()?;

        let ver = self.verifying_key.to_public_key_der()?;

        Ok((
            DerPrivateKey(sec.as_bytes().to_vec()),
            DerPublicKey(ver.as_ref().to_vec()),
        ))
    }
}

impl ToJwk<josekit::jwk::Jwk> for Ed25519Keypair {
    fn to_jwk(&self) -> MeeCryptoResult<josekit::jwk::Jwk> {
        let ed = EdKeyPair::from_pem(self.pem_keypair()?.0.as_bytes())?;

        Ok(ed.to_jwk_key_pair())
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<josekit::jwk::Jwk> {
        let ed = EdKeyPair::from_pem(self.pem_keypair()?.0.as_bytes())?;

        Ok(ed.to_jwk_public_key())
    }
}

impl ToJwk<crate::jwk::Jwk> for Ed25519Keypair {
    fn to_jwk(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk(self)?.try_into()?)
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk_public(self)?.try_into()?)
    }
}
