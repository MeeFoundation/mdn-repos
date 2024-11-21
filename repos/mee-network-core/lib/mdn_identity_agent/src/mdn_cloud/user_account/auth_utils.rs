use anyhow::Context;
use chrono::{Months, Utc};
use mee_crypto::{
    josekit::jws::alg::eddsa::EddsaJwsAlgorithm,
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

use crate::error::MdnIdentityAgentResult;

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct MdnCloudUserIdToken {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub exp: i64,
    pub iat: i64,

    pub mdn_user_role: String,
}

pub fn decode_mdn_cloud_user_id_token(
    encoded_token: &str,
    sign_key: Jwk,
) -> MdnIdentityAgentResult<MdnCloudUserIdToken> {
    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;

    let verifier = algo.verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)?;

    let (claims, _header) = decode_token::<MdnCloudUserIdToken>(&verifier, &encoded_token)?;

    Ok(claims)
}

pub struct EncodeMdnCloudUserIdTokenParams {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub mdn_user_role: String,
    pub sign_key: Jwk,
    pub kid: Option<String>,
}

pub fn encode_mdn_cloud_user_id_token(
    EncodeMdnCloudUserIdTokenParams {
        iss,
        sub,
        aud,
        mdn_user_role,
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
    };

    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;
    let signer = algo.signer_from_jwk(&sign_key.try_into()?)?;
    let encoded_token = encode_token(&signer, &claims, kid)?;

    Ok(encoded_token)
}
