use anyhow::Context;
use chrono::{Months, Utc};
use mee_crypto::{
    josekit::jws::alg::eddsa::EddsaJwsAlgorithm,
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct MdnUserNodeIdToken {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub exp: i64,
    pub iat: i64,
}

pub fn decode_user_node_id_token(
    encoded_token: &str,
    sign_key: Jwk,
) -> anyhow::Result<MdnUserNodeIdToken> {
    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;

    let verifier = algo.verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)?;

    let (claims, _header) = decode_token::<MdnUserNodeIdToken>(&verifier, &encoded_token)?;

    Ok(claims)
}

pub struct EncodeMdnNodeUserIdTokenParams {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub sign_key: Jwk,
    pub kid: Option<String>,
}

pub fn encode_user_node_id_token(
    EncodeMdnNodeUserIdTokenParams {
        iss,
        sub,
        aud,
        sign_key,
        kid,
    }: EncodeMdnNodeUserIdTokenParams,
) -> anyhow::Result<String> {
    let now = Utc::now();
    let iat = now.timestamp();
    let exp = now
        .checked_add_months(Months::new(1))
        .context("chrono time manipulation issue")?
        .timestamp();

    let claims = MdnUserNodeIdToken {
        iss,
        aud,
        sub,
        exp,
        iat,
    };

    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;
    let signer = algo.signer_from_jwk(&sign_key.try_into()?)?;
    let encoded_token = encode_token(&signer, &claims, kid)?;

    Ok(encoded_token)
}
