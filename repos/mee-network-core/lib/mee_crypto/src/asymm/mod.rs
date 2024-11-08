use crate::error::MeeCryptoResult;

pub mod ed25519;
pub mod p256;
pub mod rsa;

#[derive(Debug)]
pub struct PemPrivateKey(String);

impl PemPrivateKey {
    pub fn inner(self) -> String {
        self.0
    }
    pub fn inner_ref(&self) -> &str {
        &self.0
    }
    pub fn as_bytes(&self) -> &[u8] {
        self.0.as_bytes()
    }
}

impl core::fmt::Display for PemPrivateKey {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "{}", self.0)
    }
}

#[derive(Debug)]
pub struct PemPublicKey(String);

impl PemPublicKey {
    pub fn inner(self) -> String {
        self.0
    }
    pub fn inner_ref(&self) -> &str {
        &self.0
    }
    pub fn as_bytes(&self) -> &[u8] {
        self.0.as_bytes()
    }
}

impl core::fmt::Display for PemPublicKey {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "{}", self.0)
    }
}

#[derive(Debug)]
pub struct DerPrivateKey(pub Vec<u8>);
#[derive(Debug)]
pub struct DerPublicKey(pub Vec<u8>);

pub trait Keypair<PRIVK, PUBK> {
    fn private(&self) -> PRIVK;
    fn public(&self) -> PUBK;
}

pub trait Pkcs8<PRIVK, PUBK>: Keypair<PRIVK, PUBK> {
    fn pem_keypair(&self) -> MeeCryptoResult<(PemPrivateKey, PemPublicKey)>;
    fn der_keypair(&self) -> MeeCryptoResult<(DerPrivateKey, DerPublicKey)>;
}
