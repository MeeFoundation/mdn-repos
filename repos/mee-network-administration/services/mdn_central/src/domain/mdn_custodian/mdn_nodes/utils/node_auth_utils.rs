use crate::error::MdnCentralResult;
use mdn_identity_agent::mdn_common::mdn_node_auth::{
    decode_user_node_id_token, MdnUserNodeIdToken,
};
use mee_did::universal_resolver::{
    DIDResolverExt, UniversalDidResolver, VerificationRelationship,
};

pub async fn verify_mdn_node_did_signature(
    device_did: &str,
    device_did_signature: &str,
) -> MdnCentralResult<MdnUserNodeIdToken> {
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
        decode_user_node_id_token(device_did_signature, auth_did_jwk)?;

    Ok(device_id_token)
}
