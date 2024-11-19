use crate::{
    error::{MeeDidErr, MeeDidResult},
    universal_resolver::{DIDResolverExt, UniversalDidResolver},
};
use didkit::ssi::did::VerificationMethod;
use mee_crypto::jwk::Jwk;

fn did_verification_method_error() -> MeeDidErr {
    MeeDidErr::other("DID embedded verification method must exists")
}

pub async fn extract_did_public_jwk(kid: Option<&str>) -> MeeDidResult<Jwk> {
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

    let verification_methods =
        (|| diddoc?.verification_method)().ok_or_else(did_verification_method_error)?;

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

    Ok(public_jwk.try_into()?)
}
