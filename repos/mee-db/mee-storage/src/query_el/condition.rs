#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::expression::Expr;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub enum CheckOperator {
    #[serde(rename = "$ne")]
    NotEqual(Expr),
    #[serde(rename = "$gt")]
    GreaterThan(Expr),
    #[serde(rename = "$ge")]
    GreaterThanOrEqual(Expr),
    #[serde(rename = "$lt")]
    LessThan(Expr),
    #[serde(rename = "$le")]
    LessThanOrEqual(Expr),
    #[serde(rename = "$exists")]
    Exists,
    #[serde(rename = "$not_exists")]
    NotExists,
    #[serde(rename = "$in")]
    Contains(Expr),
    #[serde(rename = "$nin")]
    NotContains(Expr),
    #[serde(untagged)]
    Equal(Expr),
}

impl CheckOperator {
    pub fn apply_to(&self, value: &Value, expr_to_compare: &Expr) -> bool {
        match self {
            CheckOperator::Equal(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Number(n1)), Some(Value::Number(n2))) => n1 == n2,
                    (Some(Value::String(s1)), Some(Value::String(s2))) => s1 == s2,
                    (Some(v1), Some(v2)) => v1 == v2,
                    _ => false,
                }
            }
            CheckOperator::NotEqual(expr) => {
                expr.get_value(value) != expr_to_compare.get_value(value)
            }
            CheckOperator::GreaterThan(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Number(n1)), Some(Value::Number(n2))) => {
                        n1.as_f64().unwrap_or(f64::MIN) > n2.as_f64().unwrap_or(f64::MIN)
                    }
                    (Some(Value::String(s1)), Some(Value::String(s2))) => s1 > s2,
                    (Some(v1), Some(v2)) => {
                        warn!("Cannot compare {v1} with {v2}");
                        false
                    }
                    _ => false,
                }
            }
            CheckOperator::GreaterThanOrEqual(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Number(n1)), Some(Value::Number(n2))) => {
                        n1.as_f64().unwrap_or(f64::MIN) >= n2.as_f64().unwrap_or(f64::MIN)
                    }
                    (Some(Value::String(s1)), Some(Value::String(s2))) => s1 >= s2,
                    (Some(v1), Some(v2)) => {
                        warn!("Cannot compare {v1} with {v2}");
                        false
                    }
                    _ => false,
                }
            }
            CheckOperator::LessThan(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Number(n1)), Some(Value::Number(n2))) => {
                        n1.as_f64().unwrap_or(f64::MIN) < n2.as_f64().unwrap_or(f64::MIN)
                    }
                    (Some(Value::String(s1)), Some(Value::String(s2))) => s1 < s2,
                    (Some(v1), Some(v2)) => {
                        warn!("Cannot compare {v1} with {v2}");
                        false
                    }
                    _ => false,
                }
            }
            CheckOperator::LessThanOrEqual(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Number(n1)), Some(Value::Number(n2))) => {
                        n1.as_f64().unwrap_or(f64::MIN) <= n2.as_f64().unwrap_or(f64::MIN)
                    }
                    (Some(Value::String(s1)), Some(Value::String(s2))) => s1 <= s2,
                    (Some(v1), Some(v2)) => {
                        warn!("Cannot compare {v1} with {v2}");
                        false
                    }
                    _ => false,
                }
            }
            CheckOperator::Contains(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Array(array)), Some(item)) => {
                        let res = array.iter().any(|i| *i == item);
                        res
                    }
                    (Some(Value::String(str)), Some(Value::String(substring))) => {
                        str.contains(substring.as_str())
                    }
                    _ => {
                        warn!("Operation {self:?} works only for arrays and strings");
                        false
                    }
                }
            }
            CheckOperator::NotContains(expr) => {
                match (expr_to_compare.get_value(value), expr.get_value(value)) {
                    (Some(Value::Array(array)), Some(item)) => array.iter().all(|i| *i != item),
                    (Some(Value::String(str)), Some(Value::String(substring))) => {
                        !str.contains(substring.as_str())
                    }
                    _ => {
                        warn!("Operation {self:?} works only for arrays and strings");
                        false
                    }
                }
            }
            CheckOperator::Exists => expr_to_compare.get_value(value).is_some(),
            CheckOperator::NotExists => expr_to_compare.get_value(value).is_none(),
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::*;

    #[test]
    fn check_operator_equal_str() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::Equal(Expr::Val(Value::String("value3".to_string())));
        assert!(op.apply_to(&val, &Expr::Field(format!("field2{PATH_SEPARATOR}field3"))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::String("value2".to_string()))));
    }

    #[test]
    fn check_operator_equal_num() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::Equal(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(5.into()))));
    }

    #[test]
    fn check_operator_equal_object() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::Equal(Expr::Field(format!("field2")));
        assert!(op.apply_to(&val, &Expr::Val(val.get("field2").unwrap().clone())));
        assert!(!op.apply_to(&val, &Expr::Val(json!({}))));
    }

    #[test]
    fn check_operator_equal_different_types() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::Equal(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(!op.apply_to(&val, &Expr::Val(Value::String("4".to_string()))));
    }

    #[test]
    fn check_operator_not_equal() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::NotEqual(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(5.into()))));
    }

    #[test]
    fn check_operator_greater_than() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::GreaterThan(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(5.into()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
    }

    #[test]
    fn check_operator_greater_than_string() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::GreaterThan(Expr::Field(format!("field2{PATH_SEPARATOR}field3")));
        assert!(op.apply_to(&val, &Expr::Val(Value::String("value4".to_string()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::String("value3".to_string()))));
    }

    #[test]
    fn check_operator_greater_than_different_types() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::GreaterThan(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(!op.apply_to(&val, &Expr::Val(Value::String("4".to_string()))));
    }

    #[test]
    fn check_operator_greater_than_or_equal() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op =
            CheckOperator::GreaterThanOrEqual(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(5.into()))));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(3.into()))));
    }

    #[test]
    fn check_operator_less_than() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::LessThan(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(3.into()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
    }

    #[test]
    fn check_operator_less_than_or_equal() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op =
            CheckOperator::LessThanOrEqual(Expr::Field(format!("field2{PATH_SEPARATOR}field4")));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(3.into()))));
        assert!(op.apply_to(&val, &Expr::Val(Value::Number(4.into()))));
        assert!(!op.apply_to(&val, &Expr::Val(Value::Number(5.into()))));
    }

    #[test]
    fn check_operator_exists() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::Exists;
        assert!(op.apply_to(&val, &Expr::Field(format!("field2{PATH_SEPARATOR}field4"))));
        assert!(!op.apply_to(&val, &Expr::Field(format!("field2{PATH_SEPARATOR}field6"))));
    }

    #[test]
    fn check_operator_not_exists() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let op = CheckOperator::NotExists;
        assert!(!op.apply_to(&val, &Expr::Field(format!("field2{PATH_SEPARATOR}field4"))));
        assert!(op.apply_to(&val, &Expr::Field(format!("field2{PATH_SEPARATOR}field6"))));
    }

    #[test]
    fn check_operator_contains_array() {
        let val = json!({
                "field1":["value1", "value2"],
                "field2":["value3"],
                "field3":"value2"
        });

        let op = CheckOperator::Contains(Expr::Val(Value::String("value2".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field1".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field2".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field3".to_string())));
    }

    #[test]
    fn check_operator_not_contains_array() {
        let val = json!({
                "field1":["value1", "value2"],
                "field2":["value3"],
                "field3":"value1"
        });

        let op = CheckOperator::NotContains(Expr::Val(Value::String("value2".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field1".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field2".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field3".to_string())));
    }

    #[test]
    fn check_operator_contains_str() {
        let val = json!({
                "field1":"12",
                "field2":"3",
                "field3":2
        });

        let op = CheckOperator::Contains(Expr::Val(Value::String("2".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field1".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field2".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field3".to_string())));
    }

    #[test]
    fn check_operator_not_contains_str() {
        let val = json!({
                "field1":"12",
                "field2":"3",
                "field3":1
        });

        let op = CheckOperator::NotContains(Expr::Val(Value::String("2".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field1".to_string())));
        assert!(op.apply_to(&val, &Expr::Field("field2".to_string())));
        assert!(!op.apply_to(&val, &Expr::Field("field3".to_string())));
    }

    #[test]
    fn check_operator_contains_with_pattern() {
        let val = json!({
            "name": "Alice",
            "last_name": "Walker",
            "age": 30,
            "email": "awalker@gmail.com",
            "payment_cards": [
                {
                    "holder": "Alice Walker",
                    "number": "1234 5678 9011 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Alice Walker",
                    "number": "9999 5678 9012 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                }
            ]
        });

        let field = Expr::Field(format!(
            "payment_cards{PATH_SEPARATOR}*{PATH_SEPARATOR}isssuer"
        ));

        assert!(CheckOperator::Contains(Expr::Val(json!("Visa"))).apply_to(&val, &field));
        assert!(!CheckOperator::NotContains(Expr::Val(json!("Visa"))).apply_to(&val, &field));
        assert!(!CheckOperator::Contains(Expr::Val(json!("Mm"))).apply_to(&val, &field));
        assert!(CheckOperator::NotContains(Expr::Val(json!("Mm"))).apply_to(&val, &field));
    }
}
