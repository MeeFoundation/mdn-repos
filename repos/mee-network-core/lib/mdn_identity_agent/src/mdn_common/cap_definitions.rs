use crate::error::MdnIdentityAgentResult;
use anyhow::Context;
use mee_crypto::{
    josekit::{jws::alg::eddsa::EddsaJwsAlgorithm, jwt::decode_header, JoseHeader},
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub enum ContextOperationsCapabilityDefinition {
    /// New identity context can be created by a user (e.g. on smart wallet) or by a provider (e.g. MDN provider custodian storage + app)
    CreateContext,

    /// Any existing identity context can be deleted by any MDN participant having this capability
    DeleteContext,

    /// Any existing identity context can be delegated with read-write access to any MDN participant
    DelegateReadWriteContextToAny,

    /// Any existing identity context can be delegated with read access to any MDN participant
    DelegateReadContextToAny,

    /// Any existing identity context can be delegated with read-write access to MDN data owner (MDN user) only
    DelegateReadWriteContextToOwner,

    /// Any operation mentioned above
    Any,
}

#[derive(Serialize, Deserialize)]
pub enum ContextDataAccessPermissions {
    Read,
    Write,
    Delete,
    Any,
}

#[derive(Serialize, Deserialize)]
pub struct ContextDataAccessDescription {
    pub paths: Vec<String>,
    pub permissions: Vec<ContextDataAccessPermissions>,
}

#[derive(Serialize, Deserialize)]
pub struct ContextDataAccessCapabilityDefinition {
    pub context_id: String,
    pub context_data_access: Vec<ContextDataAccessDescription>,
}

#[derive(Serialize, Deserialize)]
pub enum MdnCapabilityDefinition {
    ContextOperations(ContextOperationsCapabilityDefinition),
    ContextDataAccess(ContextDataAccessCapabilityDefinition),
}

#[derive(Serialize, Deserialize)]
pub struct MdnCapability {
    /// Issuer. Context-scoped user identifier
    pub from: String,

    /// Audience. MDN custodian identifier
    pub to: String,

    /// Subject. Context-scoped user identifier
    pub sub: String,

    /// Capability definition
    pub cap: MdnCapabilityDefinition,

    /// Expiration date and time
    pub exp: i64,
}

impl MdnCapability {
    pub fn encode(&self, sign_private_key: Jwk, kid: String) -> MdnIdentityAgentResult<String> {
        let algo = EddsaJwsAlgorithm::Eddsa;
        let signer = algo.signer_from_jwk(&sign_private_key.try_into()?)?;
        let encoded_token = encode_token(&signer, self, Some(kid))?;

        Ok(encoded_token)
    }
    pub fn decode_header(encoded_token: &str) -> MdnIdentityAgentResult<Box<dyn JoseHeader>> {
        Ok(decode_header(encoded_token.as_bytes())?)
    }
    pub async fn decode(encoded_token: &str) -> MdnIdentityAgentResult<(Self, String)> {
        let token_header = MdnCapability::decode_header(&encoded_token)?;

        let sign_did_id = token_header
            .claim("kid")
            .context("missing 'kid' in the MDN cap token")?
            .as_str()
            .context("invalid 'kid' format of the MDN cap token")?;

        let collect = sign_did_id.split("#").collect::<Vec<_>>();
        let sign_did = collect.first().context("missing ctx cap token did")?;

        let auth_did_jwk = UniversalDidResolver
            .get_verification_method_jwk_by_id(&sign_did, &sign_did_id)
            .await?;

        // TODO derive algo from input jwk
        let algo = EddsaJwsAlgorithm::Eddsa;

        let verifier = algo.verifier_from_jwk(&auth_did_jwk.to_public_key()?.try_into()?)?;

        let (claims, _header) = decode_token::<Self>(&verifier, &encoded_token)?;

        Ok((claims, sign_did.to_string()))
    }
}
