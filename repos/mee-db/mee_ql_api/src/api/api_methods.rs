use super::examples::*;
use crate::error::Result;
use serde_json::Value;

use mee_ql::query_executor::DB;

use axum::extract::State;
use axum::Json;

#[utoipa::path(
    post,
    path = "/api/v1/execute",
    request_body(content = String,
    examples(
        ("Get all payment cards of user" = (value = json!(get_all_payment_cards_of_user()))),
        ("Get Alice's payment card by number" = (value = json!(get_alice_payment_card_by_number()))),
        ("Get all users over 25 offset 1 limit 1" = (value = json!(get_users_over_25_offset_1_limit_1()))),
        ("Get all users over 30" = (value = json!(get_all_users_over_30()))),
        ("Get all visa card numbers" = (value = json!(get_visa_cards()))),
        ("Get users who is older then current" = (value = json!(get_users_who_is_older_then_current()))),
        ("Update name and card issuer" = (value = json!(update_name_and_card_issuer()))),
        ("Delete card" = (value = json!(delete_card()))),
        ("Delete user" = (value = json!(delete_user()))),
    )),
    responses(
      (status = 200, description = "Ok", body = Value),
      (status = 500, description = "Something went wrong", body = String),
      (status = 400, description = "Bad request", body = String),
  ),
)]
#[axum::debug_handler]
pub async fn execute(State(storage): State<DB>, query: String) -> Result<Json<Value>> {
    let res = storage.execute(query).await?;
    Ok(Json(res))
}

#[utoipa::path(
    post,
    path = "/api/v1/insert_many",
    request_body(content = Vec<Value>,
    examples(
        ("Default set" = (value = json!(mock_user_data()))),
    )),
    responses(
      (status = 200, description = "Ok", body = Vec<String>),
      (status = 500, description = "Something went wrong", body = String),
      (status = 400, description = "Bad request", body = String),
  ),
)]
#[axum::debug_handler]
pub async fn insert_many(
    State(storage): State<DB>,
    Json(data): Json<Vec<Value>>,
) -> Result<Json<Vec<String>>> {
    let res = storage.insert_many(data).await?;
    Ok(Json(res))
}
