use chacha20poly1305::aead;
use mee_macro_utils::from_external_error_to_string_error;
use std::string::FromUtf8Error;

pub type MeeCryptoResult<T, E = MeeCryptoErr> = std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub enum MeeCryptoErr {
    #[error("PKCS8 specific error: {error}")]
    Pkcs8 { error: String },

    #[error("P256 specific error: {error}")]
    P256 { error: String },

    #[error("RSA specific error: {error}")]
    Rsa { error: String },

    #[error("JWT parsing error: {error}")]
    JwtParsing { error: String },

    #[error("JWK parsing error: {error}")]
    JwkParsing { error: String },

    #[error("JSON parsing error: {error}")]
    JsonParsing { error: String },

    #[error("Key derivation function error: {error}")]
    Kdf { error: String },

    #[error("Encryption error: {error}")]
    Encryption { error: String },

    #[error("josekit error: {error}")]
    JoseKit { error: String },

    #[error("Serde codec error: {error}")]
    SerdeCodec { error: String },

    #[error("SSI SDK error: {error}")]
    SsiSdk { error: String },

    #[error("JWT SDK error: {error}")]
    JsonWebToken { error: String },

    #[error("AEAD crypto error: {error}")]
    AeadCrypto { error: String },

    #[error("base64 error: {error}")]
    Base64 { error: String },

    #[error("Internal string parsing error: {error}")]
    InternalString { error: String },

    #[error("Other Mee crypto subsystem error: {error}")]
    Other { error: String },

    #[error("Biscuit auth framework format error: {error}")]
    BiscuitAuthFormat { error: String },
}

impl MeeCryptoErr {
    pub fn kdf_error_from_string(e: impl core::fmt::Display) -> Self {
        Self::Kdf {
            error: e.to_string(),
        }
    }
}

from_external_error_to_string_error!(
    identity_jose::error::Error,
    MeeCryptoErr,
    JoseKit
);
from_external_error_to_string_error!(aead::Error, MeeCryptoErr, AeadCrypto);
from_external_error_to_string_error!(pkcs8::Error, MeeCryptoErr, Pkcs8);
from_external_error_to_string_error!(pkcs8::spki::Error, MeeCryptoErr, Pkcs8);
from_external_error_to_string_error!(
    p256::elliptic_curve::Error,
    MeeCryptoErr,
    P256
);
from_external_error_to_string_error!(rsa::Error, MeeCryptoErr, Rsa);
from_external_error_to_string_error!(base64::DecodeError, MeeCryptoErr, Base64);
from_external_error_to_string_error!(
    FromUtf8Error,
    MeeCryptoErr,
    InternalString
);
from_external_error_to_string_error!(
    biscuit_auth::error::Format,
    MeeCryptoErr,
    BiscuitAuthFormat
);
