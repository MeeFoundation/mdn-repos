use crate::error::MdnIdentityAgentResult;
use anyhow::Context;
use chrono::{Months, Utc};
use mee_crypto::{
    josekit::jws::alg::eddsa::EddsaJwsAlgorithm,
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct MdnCloudUserIdToken {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub exp: i64,
    pub iat: i64,

    pub mdn_user_role: String,
    pub mdn_user_custodian_uid: String,
    pub mdn_custodian_storage_did: String,
    pub mdn_user_context_scoped_uid: String,
}

impl MdnCloudUserIdToken {
    pub fn decode(encoded_token: &str, sign_key: Jwk) -> MdnIdentityAgentResult<Self> {
        // TODO derive algo from input jwk
        let algo = EddsaJwsAlgorithm::Eddsa;

        let verifier = algo.verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)?;

        let (claims, _header) = decode_token::<Self>(&verifier, &encoded_token)?;

        Ok(claims)
    }
    pub fn encode(
        EncodeMdnCloudUserIdTokenParams {
            iss,
            sub,
            aud,
            mdn_user_role,
            mdn_user_custodian_uid,
            mdn_custodian_storage_did,
            mdn_user_context_scoped_uid,
            sign_key,
            kid,
        }: EncodeMdnCloudUserIdTokenParams,
    ) -> MdnIdentityAgentResult<String> {
        let now = Utc::now();
        let iat = now.timestamp();
        let exp = now
            .checked_add_months(Months::new(1))
            .context("chrono time manipulation issue")?
            .timestamp();

        let claims = MdnCloudUserIdToken {
            iss,
            aud,
            sub,
            exp,
            iat,
            mdn_user_role,
            mdn_user_custodian_uid,
            mdn_custodian_storage_did,
            mdn_user_context_scoped_uid,
        };

        // TODO derive algo from input jwk
        let algo = EddsaJwsAlgorithm::Eddsa;
        let signer = algo.signer_from_jwk(&sign_key.try_into()?)?;
        let encoded_token = encode_token(&signer, &claims, kid)?;

        Ok(encoded_token)
    }
}

pub struct EncodeMdnCloudUserIdTokenParams {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub mdn_user_role: String,
    pub mdn_user_custodian_uid: String,
    pub mdn_custodian_storage_did: String,
    pub mdn_user_context_scoped_uid: String,
    pub sign_key: Jwk,
    pub kid: Option<String>,
}
