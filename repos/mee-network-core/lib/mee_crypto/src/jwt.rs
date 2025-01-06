use crate::error::MeeCryptoResult;
use josekit::{
    jwe::{JweDecrypter, JweHeader},
    jwk::Jwk,
    jws::{JwsHeader, JwsSigner, JwsVerifier},
    jwt::JwtPayload,
};
use serde::{de::DeserializeOwned, Serialize};
// use ssi::jws::Header;

pub trait ToJwk<JwkRepr> {
    fn to_jwk(&self) -> MeeCryptoResult<JwkRepr>;
    fn to_jwk_public(&self) -> MeeCryptoResult<JwkRepr>;
}

pub fn decode_token<Claims: DeserializeOwned>(
    verifier: &impl JwsVerifier,
    token: &str,
) -> MeeCryptoResult<(Claims, JwsHeader)> {
    let (p, h) = josekit::jwt::decode_with_verifier(token, verifier)?;

    let p = serde_json::from_str(&p.to_string())?;

    Ok((p, h))
}

pub fn decode_token_with_decrypter<Claims: DeserializeOwned>(
    decrypter: &impl JweDecrypter,
    token: &str,
) -> MeeCryptoResult<(Claims, JweHeader)> {
    let (p, h) = josekit::jwt::decode_with_decrypter(token, decrypter)?;
    let p = serde_json::from_str(&p.to_string())?;

    Ok((p, h))
}

// pub fn decode_token_no_verification<Claims: DeserializeOwned>(
//     token: &str,
// ) -> MeeCryptoResult<(Header, Claims)> {
//     let (head, _) = ssi::jws::decode_unverified(token)?;
//     let claims = ssi::jwt::decode_unverified::<Claims>(token)?;

//     Ok((head, claims))
// }

pub fn encode_token<Claims: Serialize>(
    signer: &impl JwsSigner,
    claims: &Claims,
    kid: Option<String>,
) -> MeeCryptoResult<String> {
    encode_token_ext(signer, claims, kid, None)
}

pub fn encode_token_ext<Claims: Serialize>(
    signer: &impl JwsSigner,
    claims: &Claims,
    kid: Option<String>,
    jwk: Option<Jwk>,
) -> MeeCryptoResult<String> {
    let mut header = JwsHeader::new();

    header.set_token_type("JWT");

    if let Some(kid) = kid {
        header.set_key_id(kid);
    }
    if let Some(jwk) = jwk {
        header.set_jwk(jwk);
    }

    let claims: serde_json::Map<String, serde_json::Value> =
        serde_json::from_value(serde_json::to_value(&claims)?)?;

    let payload = JwtPayload::from_map(claims)?;

    let token = josekit::jwt::encode_with_signer(&payload, &header, signer)?;

    Ok(token)
}
