use super::{DerPrivateKey, DerPublicKey, Keypair, PemPrivateKey, PemPublicKey, Pkcs8};
use crate::{error::MeeCryptoResult, jwt::ToJwk};
use josekit::jwk::alg::ec::{EcCurve, EcKeyPair};
use p256::{
    pkcs8::{EncodePrivateKey, EncodePublicKey},
    PublicKey, SecretKey,
};
use rand_core::OsRng;

pub const P256_CURVE: &str = "P-256";

pub struct P256KeyPair {
    private: SecretKey,
    public: PublicKey,
}

impl P256KeyPair {
    pub fn new() -> Self {
        let private = SecretKey::random(&mut OsRng);
        let public = private.public_key();

        Self { private, public }
    }
}

impl Keypair<SecretKey, PublicKey> for P256KeyPair {
    fn private(&self) -> SecretKey {
        self.private.clone()
    }

    fn public(&self) -> PublicKey {
        self.public
    }
}

impl Pkcs8<SecretKey, PublicKey> for P256KeyPair {
    fn pem_keypair(&self) -> MeeCryptoResult<(PemPrivateKey, PemPublicKey)> {
        let privk = self.private.to_pkcs8_pem(pkcs8::LineEnding::LF)?;
        let pubk = self.public.to_public_key_pem(pkcs8::LineEnding::LF)?;

        Ok((PemPrivateKey(privk.to_string()), PemPublicKey(pubk)))
    }

    fn der_keypair(&self) -> MeeCryptoResult<(DerPrivateKey, DerPublicKey)> {
        let privk = self.private.to_pkcs8_der()?;
        let pubk = self.public.to_public_key_der()?;

        Ok((
            DerPrivateKey(privk.as_bytes().to_vec()),
            DerPublicKey(pubk.as_ref().to_vec()),
        ))
    }
}

impl ToJwk<josekit::jwk::Jwk> for P256KeyPair {
    fn to_jwk(&self) -> MeeCryptoResult<josekit::jwk::Jwk> {
        let ec = EcKeyPair::from_pem(
            self.private().to_sec1_pem(Default::default())?.as_bytes(),
            Some(EcCurve::P256),
        )?;
        Ok(ec.to_jwk_key_pair())
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<josekit::jwk::Jwk> {
        let ec = EcKeyPair::from_pem(
            self.private().to_sec1_pem(Default::default())?.as_bytes(),
            Some(EcCurve::P256),
        )?;
        Ok(ec.to_jwk_public_key())
    }
}

impl ToJwk<crate::jwk::Jwk> for P256KeyPair {
    fn to_jwk(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk(self)?.try_into()?)
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk_public(self)?.try_into()?)
    }
}
