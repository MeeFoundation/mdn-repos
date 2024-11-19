use anyhow::Context;
use chrono::{Months, Utc};
use mee_crypto::{
    josekit::jws::alg::eddsa::EddsaJwsAlgorithm,
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct MdnDeviceUserIdToken {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub exp: i64,
    pub iat: i64,
}

pub fn decode_mdn_device_user_id_token(
    encoded_token: &str,
    sign_key: Jwk,
) -> anyhow::Result<MdnDeviceUserIdToken> {
    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;

    let verifier = algo
        .verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)
        .unwrap();

    let (claims, _header) = decode_token::<MdnDeviceUserIdToken>(&verifier, &encoded_token)?;

    Ok(claims)
}

pub fn encode_mdn_device_user_id_token(
    iss: String,
    sub: String,
    sign_key: Jwk,
) -> anyhow::Result<String> {
    let now = Utc::now();
    let iat = now.timestamp();
    let exp = now
        .checked_add_months(Months::new(1))
        .context("chrono time manipulation issue")?
        .timestamp();

    let claims = MdnDeviceUserIdToken {
        iss,
        aud: sub.clone(),
        sub,
        exp,
        iat,
    };

    // TODO derive algo from input jwk
    let algo = EddsaJwsAlgorithm::Eddsa;
    let signer = algo.signer_from_jwk(&sign_key.try_into()?)?;
    let encoded_token = encode_token(&signer, &claims, None)?;

    Ok(encoded_token)
}
