use super::api_types::SelectingField::*;
use super::api_types::*;
use serde_json::json;
use std::collections::HashMap;

pub fn select_payment_cards_exampel() -> SelectQueryRequest {
    let mut filter = HashMap::new();
    filter.insert(
        "id".to_string(),
        CheckOperator::Eq(json!("afe4-3214-ff34-43r4".to_string())),
    );

    SelectQueryRequest {
        schema: SchemaName("http://www.its-mee.org/schema".to_string()),
        select: vec![SpecifiedField {
            field: FieldName("payment_cards".to_string()),
            operations: Some(vec![Operation::Flatten]),
            aggregation: None,
            alias: None,
        }],
        filter: Some(vec![WhereClause::Check(filter)]),
        limit: None,
        offset: None,
    }
}

pub fn select_example_response() -> SelectQueryResponse {
    let mut record1 = HashMap::new();
    record1.insert("field1".to_string(), json!("value1"));
    record1.insert("field2".to_string(), json!("value2"));

    let mut record2 = HashMap::new();
    let _embedded = json!({
        "embedded_field1": "embedded_value1",
        "embedded_field2": "embedded_value2",
    });
    record2.insert("field1".to_string(), json!("value3".to_string()));
    record2.insert("field2".to_string(), json!([_embedded.clone(), _embedded]));
    let _embedded = json!({
        "embedded_field1": "embedded_value1",
        "embedded_field2": "embedded_value2",
    });

    let mut stats = HashMap::new();
    stats.insert("execution_time_ms".to_string(), json!(4));

    SelectQueryResponse {
        result: vec![record1, record2],
        execution_stats: stats,
    }
}

pub fn select_payment_card_by_number_exampel() -> SelectQueryRequest {
    let mut filter = HashMap::new();
    filter.insert(
        "id".to_string(),
        CheckOperator::Eq(json!("afe4-3214-ff34-43r4".to_string())),
    );
    filter.insert(
        "payment_cards.number".to_string(),
        CheckOperator::Eq(json!("1111222233334444".to_string())),
    );

    SelectQueryRequest {
        schema: SchemaName("http://www.its-mee.org/schema".to_string()),
        select: vec![SpecifiedField {
            field: FieldName("payment_cards".to_string()),
            operations: Some(vec![Operation::Flatten]),
            aggregation: None,
            alias: None,
        }],
        filter: Some(vec![WhereClause::Check(filter)]),
        limit: None,
        offset: None,
    }
}

pub fn select_users_by_flight_exampel() -> SelectQueryRequest {
    let mut filter = HashMap::new();
    filter.insert(
        "tickets.flight.id".to_string(),
        CheckOperator::Eq(json!("afe4-3214-ff34-43r4".to_string())),
    );

    SelectQueryRequest {
        schema: SchemaName("http://www.its-mee.org/schema".to_string()),
        select: vec![
            OnlyName(FieldName("id".to_string())),
            SpecifiedField {
                field: FieldName("name".to_string()),
                operations: None,
                aggregation: None,
                alias: None,
            },
        ],
        filter: Some(vec![WhereClause::Check(filter)]),
        limit: None,
        offset: None,
    }
}
// #endregion
// const SELECT_EXAMPLE_1: SelectQueryRequest = select_example_1();
