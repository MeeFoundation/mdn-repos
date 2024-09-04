#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};

use super::expression::Expr;
use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};
use std::collections::HashSet;

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
    #[serde(rename = "$contains")]
    Contains(Expr),
    #[serde(rename = "$not_contains")]
    NotContains(Expr),
    #[serde(untagged)]
    Equal(Expr),
}

impl CheckOperator {
    pub fn apply_to(&self, value: Option<&Value>, expr_to_compare: &Expr) -> bool {
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

    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            CheckOperator::Equal(expr) => expr.get_using_fields(),
            CheckOperator::NotEqual(expr) => expr.get_using_fields(),
            CheckOperator::GreaterThan(expr) => expr.get_using_fields(),
            CheckOperator::GreaterThanOrEqual(expr) => expr.get_using_fields(),
            CheckOperator::LessThan(expr) => expr.get_using_fields(),
            CheckOperator::LessThanOrEqual(expr) => expr.get_using_fields(),
            CheckOperator::Contains(expr) => expr.get_using_fields(),
            CheckOperator::NotContains(expr) => expr.get_using_fields(),
            CheckOperator::Exists => HashSet::new(),
            CheckOperator::NotExists => HashSet::new(),
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::super::_test_support::*;

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
        let eq_value3 = cond(json!("value3"));
        assert!(eq_value3.apply_to(Some(&val), &de_expr(r#""@field2/field3""#)));
        assert!(!eq_value3.apply_to(Some(&val), &de_expr(r#""value2""#)));
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

        let eq_field4 = cond(json!("@field2/field4"));
        assert!(eq_field4.apply_to(Some(&val), &de_expr("4")));
        assert!(!eq_field4.apply_to(Some(&val), &de_expr("5")));
    }
}
