use anyhow::Context;
use chrono::{Months, Utc};
use mee_crypto::{
    josekit::jws::alg::eddsa::EddsaJwsAlgorithm,
    jwk::{Jwk, JwkOps},
    jwt::{decode_token, encode_token},
};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct MdnCustodianStorageIdToken {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub exp: i64,
    pub iat: i64,
}

impl MdnCustodianStorageIdToken {
    pub fn decode(encoded_token: &str, sign_key: Jwk) -> anyhow::Result<Self> {
        // TODO derive algo from input jwk
        let algo = EddsaJwsAlgorithm::Eddsa;

        let verifier = algo.verifier_from_jwk(&sign_key.to_public_key()?.try_into()?)?;

        let (claims, _header) = decode_token::<Self>(&verifier, &encoded_token)?;

        Ok(claims)
    }
    pub fn encode(
        EncodeMdnCustodianStorageIdTokenParams {
            iss,
            sub,
            aud,
            sign_key,
            kid,
        }: EncodeMdnCustodianStorageIdTokenParams,
    ) -> anyhow::Result<String> {
        let now = Utc::now();
        let iat = now.timestamp();
        let exp = now
            .checked_add_months(Months::new(1))
            .context("chrono time manipulation issue")?
            .timestamp();

        let claims = MdnCustodianStorageIdToken {
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
}

pub struct EncodeMdnCustodianStorageIdTokenParams {
    pub iss: String,
    pub sub: String,
    pub aud: String,
    pub sign_key: Jwk,
    pub kid: Option<String>,
}
