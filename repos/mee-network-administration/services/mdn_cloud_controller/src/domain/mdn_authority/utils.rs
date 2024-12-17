use crate::error::{MdnCloudControllerErr, MdnCloudControllerResult};
use mee_crypto::jwk::Jwk;
use mee_secrets_manager::signatures_service::{
    SignaturesService, SignaturesServiceDefault,
};

#[async_trait::async_trait]
pub trait MdnSignaturesService: SignaturesService {
    async fn mee_sig(&self) -> MdnCloudControllerResult<Jwk> {
        Ok(self
            .get_source_jwk_signature()
            .await?
            .ok_or_else(|| MdnCloudControllerErr::MissingMdnCentralAuthoritySignature)?
            .try_into()?)
    }
    async fn mee_sig_did(&self) -> MdnCloudControllerResult<String> {
        Ok(self
            .get_did_id_from_source_jwk()
            .await?
            .ok_or_else(|| MdnCloudControllerErr::MissingMdnCentralAuthorityDid)?)
    }
}

impl MdnSignaturesService for SignaturesServiceDefault {}
