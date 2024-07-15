use crate::{
    error::{MeeDidErr, MeeDidResult},
    universal_resolver::{DIDResolverExt, UniversalDidResolver},
};
use didkit::JWK;
use ssi::did::{DIDMethodError, VerificationMethod};

pub fn did_method_error_from_str(
    err: impl core::fmt::Display,
) -> DIDMethodError {
    DIDMethodError::Other(anyhow::anyhow!("{err}"))
}
pub fn did_method_error_from_dbg(err: impl core::fmt::Debug) -> DIDMethodError {
    DIDMethodError::Other(anyhow::anyhow!("{err:?}"))
}

fn did_verification_method_error() -> MeeDidErr {
    MeeDidErr::other("DID embedded verification method must exists")
}

pub async fn extract_did_public_jwk(kid: Option<&str>) -> MeeDidResult<JWK> {
    let kid = (|| {
        kid?.split("#")
            .collect::<Vec<_>>()
            .get(0)
            .map(ToString::to_string)
    })()
    .ok_or(MeeDidErr::other("JWT header kid is required"))?;

    let (_, diddoc, _) = UniversalDidResolver
        .resolve_err(&kid, &Default::default())
        .await?;

    let verification_methods = (|| diddoc?.verification_method)()
        .ok_or_else(did_verification_method_error)?;

    let vmethod = verification_methods
        .get(0)
        .ok_or_else(did_verification_method_error)?;

    let VerificationMethod::Map(vmap) = &vmethod else {
        return Err(did_verification_method_error())?;
    };

    let public_jwk = vmap
        .public_key_jwk
        .clone()
        .ok_or_else(did_verification_method_error)?;

    Ok(public_jwk)
}
