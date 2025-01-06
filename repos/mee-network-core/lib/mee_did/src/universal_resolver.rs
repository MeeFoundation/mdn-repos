use crate::error::{MeeDidErr, MeeDidResult};
use async_trait::async_trait;
pub use didkit::{
    ssi::did::{DIDMethods, VerificationMethod},
    DIDResolver, Document, DocumentMetadata, ResolutionInputMetadata, ResolutionMetadata,
    VerificationRelationship, DID_METHODS,
};
use lazy_static::lazy_static;
use mee_crypto::jwk::Jwk;

lazy_static! {
    pub static ref UNIVERSAL_DID_METHOD: DIDMethods<'static> = {
        let methods = DIDMethods::default();

        methods
    };
}

pub struct UniversalDidResolver;

#[async_trait]
impl DIDResolver for UniversalDidResolver {
    async fn resolve(
        &self,
        did: &str,
        input_metadata: &ResolutionInputMetadata,
    ) -> (
        ResolutionMetadata,
        Option<Document>,
        Option<DocumentMetadata>,
    ) {
        let did_meth = DID_METHODS.get_method(did);

        if let Ok(_) = did_meth {
            DID_METHODS.resolve(did, input_metadata).await
        } else {
            UNIVERSAL_DID_METHOD.resolve(did, input_metadata).await
        }
    }
}

impl DIDResolverExt for UniversalDidResolver {}

#[async_trait]
pub trait DIDResolverExt: DIDResolver {
    async fn resolve_did_for_relation(
        &self,
        did: &str,
        relation: VerificationRelationship,
    ) -> MeeDidResult<String> {
        let (_, doc, _) = self
            .resolve_err(did, &ResolutionInputMetadata::default())
            .await?;

        let did_id = doc
            .ok_or(MeeDidErr::other(format!(
                "Missing DID document for {}",
                did
            )))?
            .get_verification_method_ids(relation)
            .map_err(MeeDidErr::other)?
            .pop()
            .ok_or(MeeDidErr::other(format!(
                "Missing DID Authentication for {}",
                did
            )))?;

        Ok(did_id)
    }
    async fn get_verification_method_jwk_by_id(
        &self,
        did: &str,
        method_id: &str,
    ) -> MeeDidResult<Jwk> {
        let (_, doc, _) = self
            .resolve_err(did, &ResolutionInputMetadata::default())
            .await?;

        let jwk = doc
            .ok_or(MeeDidErr::other(format!(
                "Missing DID document for {}",
                did
            )))?
            .verification_method
            .ok_or(MeeDidErr::other(format!(
                "Missing DID document verification method map for {}",
                did
            )))?
            .into_iter()
            .find_map(|vm| match vm {
                VerificationMethod::Map(vmap) => {
                    if vmap.id == method_id {
                        Some(vmap.get_jwk())
                    } else {
                        None
                    }
                }
                _ => unimplemented!(),
            });

        Ok(match jwk {
            Some(jwk) => jwk?.try_into()?,
            None => Err(MeeDidErr::DidResolver {
                error: format!("No matching JWKs for {}", did),
            })?,
        })
    }
    async fn resolve_err(
        &self,
        did: &str,
        input_metadata: &ResolutionInputMetadata,
    ) -> MeeDidResult<(
        ResolutionMetadata,
        Option<Document>,
        Option<DocumentMetadata>,
    )> {
        let res = self.resolve(did, input_metadata).await;

        if let Some(err) = &res.0.error {
            Err(MeeDidErr::other(err))?;
        }

        Ok(res)
    }
}
