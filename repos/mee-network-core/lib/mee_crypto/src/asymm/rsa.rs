use super::{DerPrivateKey, DerPublicKey, Keypair, PemPrivateKey, PemPublicKey, Pkcs8};
use crate::{error::MeeCryptoResult, jwt::ToJwk};
use josekit::jwk::Jwk;
use rand_core::OsRng;
use rsa::{
    pkcs8::{EncodePrivateKey, EncodePublicKey},
    RsaPrivateKey, RsaPublicKey,
};

pub struct RsaKeyPair {
    private: RsaPrivateKey,
    public: RsaPublicKey,
}

impl RsaKeyPair {
    pub fn new(bits: usize) -> MeeCryptoResult<Self> {
        let private = RsaPrivateKey::new(&mut OsRng, bits)?;

        let public = RsaPublicKey::from(&private);

        Ok(Self { private, public })
    }
    pub fn new_2048() -> MeeCryptoResult<Self> {
        Self::new(2048)
    }
}

impl Keypair<RsaPrivateKey, RsaPublicKey> for RsaKeyPair {
    fn private(&self) -> RsaPrivateKey {
        self.private.clone()
    }

    fn public(&self) -> RsaPublicKey {
        self.public.clone()
    }
}

impl Pkcs8<RsaPrivateKey, RsaPublicKey> for RsaKeyPair {
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

impl ToJwk<Jwk> for RsaKeyPair {
    fn to_jwk(&self) -> MeeCryptoResult<Jwk> {
        Ok(josekit::jwk::alg::rsa::RsaKeyPair::from_pem(
            self.private.to_pkcs8_pem(pkcs8::LineEnding::LF)?.as_bytes(),
        )?
        .to_jwk_key_pair())
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<Jwk> {
        Ok(josekit::jwk::alg::rsa::RsaKeyPair::from_pem(
            self.public
                .to_public_key_pem(pkcs8::LineEnding::LF)?
                .as_bytes(),
        )?
        .to_jwk_public_key())
    }
}

impl ToJwk<crate::jwk::Jwk> for RsaKeyPair {
    fn to_jwk(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk(self)?.try_into()?)
    }

    fn to_jwk_public(&self) -> MeeCryptoResult<crate::jwk::Jwk> {
        Ok(ToJwk::<josekit::jwk::Jwk>::to_jwk_public(self)?.try_into()?)
    }
}
