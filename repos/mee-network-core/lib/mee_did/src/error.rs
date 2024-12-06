use didkit::ssi::did::DIDMethodError;
use mee_macro_utils::from_external_error_to_string_error;

pub type MeeDidResult<T, E = MeeDidErr> = std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub enum MeeDidErr {
    #[error("SSI SDK DID method error: {error}")]
    DidMethod { error: String },

    #[error("DID resolver error: {error}")]
    DidResolver { error: String },

    #[error("SSI SDK DID error: {error}")]
    SsiSdkDid { error: String },

    #[error("Serde codec error: {error}")]
    SerdeCodec { error: String },

    #[error("Mee crypto utils error: {error}")]
    MeeCryptoUtils { error: String },

    #[error("Other unspecified error: {error}")]
    Other { error: String },
}
impl MeeDidErr {
    pub fn other(error: impl core::fmt::Display) -> Self {
        Self::Other {
            error: error.to_string(),
        }
    }
}

from_external_error_to_string_error!(DIDMethodError, MeeDidErr, DidMethod);
from_external_error_to_string_error!(didkit::ssi::did::Error, MeeDidErr, SsiSdkDid);
from_external_error_to_string_error!(serde_json::Error, MeeDidErr, SerdeCodec);
from_external_error_to_string_error!(mee_crypto::error::MeeCryptoErr, MeeDidErr, MeeCryptoUtils);
