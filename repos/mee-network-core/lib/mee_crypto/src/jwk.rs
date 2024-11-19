use crate::error::{MeeCryptoErr, MeeCryptoResult};
use serde::{Deserialize, Serialize};
use std::str::FromStr;

#[derive(Debug, Serialize, Deserialize)]
pub struct JwkSet {
    pub keys: Vec<Jwk>,
}

pub trait JwkOps: FromStr {
    fn from_slice(slice: &[u8]) -> MeeCryptoResult<Self>
    where
        Self: Sized;
    fn key_operations(&self) -> Option<Vec<&str>>;
    fn set_key_operations(&mut self, values: Vec<impl Into<String>>);
    fn to_public_key(&self) -> MeeCryptoResult<Self>
    where
        Self: Sized;
    fn thumbprint(&self) -> MeeCryptoResult<String>;
    fn to_string(&self) -> MeeCryptoResult<String>;
}

#[derive(Serialize, Deserialize, Debug, PartialEq, Eq, Clone)]
pub struct JwkContainer<T>(T);

pub type Jwk = JwkContainer<josekit::jwk::Jwk>;

impl FromStr for Jwk {
    type Err = MeeCryptoErr;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Ok(serde_json::from_str(s)?)
    }
}

impl JwkOps for Jwk {
    fn key_operations(&self) -> Option<Vec<&str>> {
        josekit::jwk::Jwk::key_operations(&self.0)
    }

    fn to_public_key(&self) -> MeeCryptoResult<Self>
    where
        Self: Sized,
    {
        Ok(Self(josekit::jwk::Jwk::to_public_key(&self.0)?))
    }

    fn set_key_operations(&mut self, values: Vec<impl Into<String>>) {
        josekit::jwk::Jwk::set_key_operations(&mut self.0, values);
    }

    fn from_slice(slice: &[u8]) -> MeeCryptoResult<Self> {
        Ok(serde_json::from_slice(slice)?)
    }

    fn thumbprint(&self) -> MeeCryptoResult<String> {
        let jwk: identity_jose::jwk::Jwk = serde_json::from_str(&serde_json::to_string(&self.0)?)?;
        Ok(jwk.thumbprint_sha256_b64())
    }

    fn to_string(&self) -> MeeCryptoResult<String> {
        Ok(serde_json::to_string(&self.0)?)
    }
}

macro_rules! impl_try_from_jwk {
    ($from: path, $to: path) => {
        impl TryFrom<$from> for $to {
            type Error = MeeCryptoErr;

            fn try_from(value: $from) -> Result<Self, Self::Error> {
                Ok(serde_json::from_value(serde_json::to_value(&value)?)?)
            }
        }
    };
}

macro_rules! impl_try_from_jwk_ref {
    ($from: path, $to: path) => {
        impl TryFrom<&$from> for $to {
            type Error = MeeCryptoErr;

            fn try_from(value: &$from) -> Result<Self, Self::Error> {
                Ok(serde_json::from_value(serde_json::to_value(value)?)?)
            }
        }
    };
}

impl_try_from_jwk!(Jwk, josekit::jwk::Jwk);
impl_try_from_jwk_ref!(Jwk, josekit::jwk::Jwk);

impl_try_from_jwk!(josekit::jwk::Jwk, Jwk);
impl_try_from_jwk_ref!(josekit::jwk::Jwk, Jwk);

impl_try_from_jwk!(identity_jose::jwk::Jwk, Jwk);
impl_try_from_jwk_ref!(identity_jose::jwk::Jwk, Jwk);

impl_try_from_jwk!(didkit::JWK, Jwk);
impl_try_from_jwk_ref!(didkit::JWK, Jwk);

impl_try_from_jwk!(Jwk, didkit::JWK);
impl_try_from_jwk_ref!(Jwk, didkit::JWK);

/// Operations that the key is intended to be used for. This enum is serialized `untagged`
#[derive(Serialize, Deserialize, Clone, Debug, Eq, PartialEq, Hash)]
#[serde(rename_all = "camelCase")]
pub enum KeyOperations {
    /// Computer digital signature or MAC
    Sign,
    /// Verify digital signature or MAC
    Verify,
    /// Encrypt content
    Encrypt,
    /// Decrypt content and validate decryption, if applicable
    Decrypt,
    /// Encrypt key
    WrapKey,
    /// Decrypt key and validate decryption, if applicable
    UnwrapKey,
    /// Derive key
    DeriveKey,
    /// Derive bits not to be used as a key
    DeriveBits,
    /// Other operation
    Other(String),
}

pub struct KeyOps(pub KeyOperations);

impl From<&KeyOps> for String {
    fn from(value: &KeyOps) -> Self {
        serde_json::from_value::<String>(
            serde_json::to_value(&value.0)
                .unwrap_or(serde_json::Value::String("unknown keyops".into())),
        )
        .unwrap_or("unknown keyops".into())
    }
}

impl From<KeyOps> for String {
    fn from(value: KeyOps) -> Self {
        (&value).into()
    }
}

impl core::fmt::Display for KeyOps {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        let s: String = self.into();
        write!(f, "{}", s)
    }
}

impl From<&str> for KeyOps {
    fn from(value: &str) -> Self {
        KeyOps(serde_json::from_str(value).unwrap_or(KeyOperations::Other(value.into())))
    }
}
