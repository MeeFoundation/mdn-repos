use super::api_types::*;
use super::examples::*;
use crate::app_ctl::AppCtl;
use crate::config::AppConfig;
use crate::error::ApiResult;
use  mee_storage::json_db::DB;
use  mee_storage::query_el::SelectQuery;
use serde_json::Value;
use futures::stream::{self, Skip, StreamExt};

use axum::extract::State;
use axum::Json;

#[utoipa::path(
    post,
    path = "/api/v1/select",
    request_body(content = SelectQuery,
    examples(
        ("Select all" = (value = json!(select_all()))),
        ("Get all payment cards of user" = (value = json!(get_all_payment_cards_of_user()))),
        ("Get Alice's payment card by number" = (value = json!(get_alice_payment_card_by_number()))),
        ("Get user with lastname in email" = (value = json!(get_user_with_lastname_in_email()))),
        ("Get all user over 30" = (value = json!(get_all_users_over_30()))),
        ("Get all card numbers" = (value = json!(get_all_card_numbers()))),
        ("Get all card numbers non flatten" = (value = json!(get_all_card_numbers_non_flatten()))),
        ("Get all visa card numbers" = (value = json!(get_all_visa_card_numbers()))),
        ("Get as new struct" = (value = json!(get_as_new_struct()))),
    )),
    responses(
      (status = 200, description = "Ok", body = Json<Vec<Value>>),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn select(
    State(storage): State<DB>,
    Json(query): Json<SelectQuery>,
) -> ApiResult<Json<Vec<Value>>> {
    println!("Select: {:?}", query);
    println!();
    let res = storage
            .stream("", query)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;
        Ok(Json(res))

}
