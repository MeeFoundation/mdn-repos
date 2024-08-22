#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use serde_json::Value;
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

#[derive(Debug, Clone)]
pub enum Expr {
    Field(String),
    Val(Value),
    Operation(Operation, Box<Expr>),
}

impl Expr {
    pub fn upper(self) -> Self {
        Expr::Operation(Operation::Upper, Box::new(self))
    }

    pub fn lower(self) -> Self {
        Expr::Operation(Operation::Lower, Box::new(self))
    }

    pub fn get_value(&self, value: &Value) -> Option<Value> {
        match self {
            Expr::Field(field) => value.x_get_property(field).cloned(),
            Expr::Val(val) => Some(val.clone()),
            Expr::Operation(op, expr) => op.apply_to(expr.get_value(value)),
        }
    }
}

#[derive(Debug, Clone)]
pub enum Operation {
    Upper,
    Lower,
}

impl Operation {
    pub fn apply_to(&self, value: Option<Value>) -> Option<Value> {
        match self {
            Operation::Upper => match value {
                Some(Value::String(s)) => Some(Value::String(s.to_uppercase())),
                Some(v) => {
                    warn!("Cannot uppercase non-string value {v}");
                    None
                }
                _ => None,
            },
            Operation::Lower => match value {
                Some(Value::String(s)) => Some(Value::String(s.to_lowercase())),
                Some(v) => {
                    warn!("Cannot lowercase non-string value {v}");
                    None
                }
                _ => None,
            },
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::*;

    #[test]
    fn expr_whole_value() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });

        let expr = Expr::Field("".to_string());
        assert_eq!(expr.get_value(&val), Some(val));
    }

    #[test]
    fn expr_upper() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let expr = Expr::Field("field1".to_string()).upper();
        assert_eq!(
            expr.get_value(&val),
            Some(Value::String("VALUE1".to_string()))
        );
        assert_ne!(
            expr.get_value(&val),
            Some(Value::String("valUe1".to_string()))
        );
    }

    #[test]
    fn expr_lower() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let expr = Expr::Field("field1".to_string()).lower();
        assert_eq!(
            expr.get_value(&val),
            Some(Value::String("value1".to_string()))
        );

        assert_ne!(
            expr.get_value(&val),
            Some(Value::String("vaLue1".to_string()))
        );
    }
}
