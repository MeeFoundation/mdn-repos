use crate::{app_ctl::AppCtl, error::MdnCentralResult};
use axum::{extract::State, Json};
use mee_crypto::jwk::{JwkOps, JwkSet};

/// OIDC provider JWK set
# [utoipa::path(
    get,
    path = "/jwks.json",
    responses(
        (status = 200, description = "JWK set", body = Object),
        (status = 500, description = "Something went wrong", body = String),
    )
)]
pub async fn jwks(
    State(app_ctl): State<AppCtl>,
) -> MdnCentralResult<Json<JwkSet>> {
    let sig = app_ctl.mdn_central_authority_signature.mee_sig().await?;

    let set = JwkSet {
        keys: vec![sig.to_public_key()?],
    };

    Ok(Json(set))
}
