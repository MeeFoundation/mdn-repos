use crate::error::MdnCentralResult;
use mdn_identity_agent::mdn_device::user_auth::{
    decode_mdn_device_user_id_token, MdnDeviceUserIdToken,
};
use mee_did::universal_resolver::{
    DIDResolverExt, UniversalDidResolver, VerificationRelationship,
};

pub async fn verify_device_did_signature(
    device_did: &str,
    device_did_signature: &str,
) -> MdnCentralResult<MdnDeviceUserIdToken> {
    let auth_did_id = UniversalDidResolver
        .resolve_did_for_relation(
            device_did,
            VerificationRelationship::Authentication,
        )
        .await?;

    let auth_did_jwk = UniversalDidResolver
        .get_verification_method_jwk_by_id(device_did, &auth_did_id)
        .await?;

    let device_id_token =
        decode_mdn_device_user_id_token(device_did_signature, auth_did_jwk)?;

    Ok(device_id_token)
}
