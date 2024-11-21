use crate::error::{MdnCentralErr, MdnCentralResult};
use mee_crypto::jwk::Jwk;
use mee_secrets_manager::signatures_service::{
    SignaturesService, SignaturesServiceDefault,
};

#[async_trait::async_trait]
pub trait MdnSignaturesService: SignaturesService {
    async fn mee_sig(&self) -> MdnCentralResult<Jwk> {
        Ok(self
            .get_source_jwk_signature()
            .await?
            .ok_or_else(|| MdnCentralErr::MissingMdnCentralAuthoritySignature)?
            .try_into()?)
    }
    async fn mee_sig_did(&self) -> MdnCentralResult<String> {
        Ok(self
            .get_did_id_from_source_jwk()
            .await?
            .ok_or_else(|| MdnCentralErr::MissingMdnCentralAuthorityDid)?)
    }
}

impl MdnSignaturesService for SignaturesServiceDefault {}
