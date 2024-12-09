use crate::error::MdnIdentityAgentResult;
use mee_crypto::{
    josekit::{jws::alg::eddsa::EddsaJwsAlgorithm, jwt::decode_header, JoseHeader},
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub enum ContextOperationsCapabilityDefinition {
    /// Identity context can be created by a user (e.g. on smart wallet) or by a provider (e.g. MDN provider custodian storage + app)
    CreateContext,

    /// Identity context can be deleted by any MDN participant having this capability
    DeleteContext,

    /// Identity context can be revoked by any MDN participant having this capability
    RevokeContext,

    /// Identity context can be delegated with read-write access to any MDN participant
    DelegateReadWriteContextToAny,

    /// Identity context can be delegated with read-write access to MDN data owner (MDN user) only
    DelegateReadWriteContextToOwner,

    /// Identity context can be delegated with read access to any MDN participant
    DelegateReadContextToAny,

    /// Any operation
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
    pub fn encode(&self, sign_key: Jwk, kid: String) -> MdnIdentityAgentResult<String> {
        let algo = EddsaJwsAlgorithm::Eddsa;
        let signer = algo.signer_from_jwk(&sign_key.try_into()?)?;
        let encoded_token = encode_token(&signer, self, Some(kid))?;

        Ok(encoded_token)
    }
    pub fn decode_header(encoded_token: &str) -> MdnIdentityAgentResult<Box<dyn JoseHeader>> {
        Ok(decode_header(encoded_token.as_bytes())?)
    }
    pub fn decode(encoded_token: &str, sign_key: Jwk) -> MdnIdentityAgentResult<Self> {
        // TODO derive algo from input jwk
        let algo = EddsaJwsAlgorithm::Eddsa;

        let verifier = algo.verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)?;

        let (claims, _header) = decode_token::<Self>(&verifier, &encoded_token)?;

        Ok(claims)
    }
}
