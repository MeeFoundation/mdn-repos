use super::api_types::*;
use super::examples::{
    select_example_response, select_payment_card_by_number_exampel, select_payment_cards_exampel,
    select_users_by_flight_exampel,
};
use crate::app_ctl::AppCtl;
use crate::config::AppConfig;
use crate::error::ApiResult;
use crate::storage::DB;

use axum::extract::State;
use axum::Json;

#[utoipa::path(
    post,
    path = "/api/v1/select",
    request_body(content = SelectQueryRequest,
    examples(
        ("Payment cards by user" = (value = json!(select_payment_cards_exampel()))),
        ("Payment card by number" = (value = json!(select_payment_card_by_number_exampel()))),
        ("Users by flight" = (value = json!(select_users_by_flight_exampel()))),
    )),
    responses(
      (status = 200, description = "Ok", body = SelectQueryResponse),
      (status = 500, description = "Something went wrong", body = String),
  ),
)]
pub async fn select(
    State(storage): State<DB>,
    Json(query): Json<SelectQueryRequest>,
) -> ApiResult<Json<SelectQueryResponse>> {
    println!("Select: {:?}", query);
    println!();
    let res = select_example_response();
    Ok(Json(res))
}

#[utoipa::path(
    post,
    path = "/api/v1/insert",
    request_body = MergeQueryRequest
)]
pub async fn merge(
    State(storage): State<DB>,
    Json(query): Json<MergeQueryRequest>,
) -> ApiResult<()> {
    println!("Merge: {:?}", query);
    println!();
    Ok(())
}

#[utoipa::path(
    post,
    path = "/api/v1/delete",
    request_body = DeleteQueryRequest,
)]
pub async fn delete(
    State(storage): State<DB>,
    Json(query): Json<DeleteQueryRequest>,
) -> ApiResult<()> {
    println!("Delete: {:?}", query);
    println!();
    Ok(())
}

#[utoipa::path(
    post,
    path = "/api/v1/update",
    request_body = UpdateQueryRequest,
)]
pub async fn update(
    State(storage): State<DB>,
    Json(query): Json<UpdateQueryRequest>,
) -> ApiResult<()> {
    println!("Update: {:?}", query);
    println!();
    Ok(())
}
