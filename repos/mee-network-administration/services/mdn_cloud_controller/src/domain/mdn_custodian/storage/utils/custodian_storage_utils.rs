use crate::error::MdnCloudControllerResult;
use mdn_identity_agent::mdn_common::mdn_custodian_storage_auth::MdnCustodianStorageIdToken;
use mee_did::universal_resolver::{
    DIDResolverExt, UniversalDidResolver, VerificationRelationship,
};

pub async fn verify_custodian_storage_did_signature(
    device_did: &str,
    device_did_signature: &str,
) -> MdnCloudControllerResult<MdnCustodianStorageIdToken> {
    let auth_did_id = UniversalDidResolver
        .resolve_did_for_relation(
            device_did,
            VerificationRelationship::Authentication,
        )
        .await?;

    let auth_did_jwk = UniversalDidResolver
        .get_verification_method_jwk_by_id(device_did, &auth_did_id)
        .await?;

    let device_id_token = MdnCustodianStorageIdToken::decode(
        device_did_signature,
        auth_did_jwk,
    )?;

    Ok(device_id_token)
}
