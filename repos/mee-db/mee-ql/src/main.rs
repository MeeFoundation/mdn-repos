mod api;
mod app_ctl;
pub mod config;
mod error;
mod model;
mod storage;

use api::api_types::SelectQueryRequest;
use api::api_types::*;
use app_ctl::AppCtl;
use error::*;
use serde_json::{json, Value};
use std::collections::HashMap;

#[tokio::main]
async fn main() -> ApiResult<()> {
    let mut check_map = HashMap::new();
    check_map.insert(
        "name".to_string(),
        CheckOperator::Eq(Value::String("John".to_string())),
    );
    check_map.insert("age".to_string(), CheckOperator::Gt(json!(18)));

    let se = SelectQueryRequest {
        schema: SchemaName("users".to_string()),
        select: vec![
            SelectingField::SpecifiedField {
                field: FieldName("name".to_string()),
                operations: Some(vec![Operation::Upper]),
                aggregation: None,
                alias: Some("UpperName".to_string()),
            },
            SelectingField::OnlyName(FieldName("age".to_string())),
        ],
        filter: Some(vec![WhereClause::Check(check_map)]),
        limit: Some(10),
        offset: Some(0),
    };

    let json = serde_json::to_string_pretty(&se)?;
    println!("Select as JSON: {}", json);

    AppCtl::try_new().await?.run().await
}
