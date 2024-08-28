#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};
use serde::de::value;
use serde::{Deserialize, Serialize, Serializer};
use serde_json::{Map, Value};
use std::cmp::Ordering;
use std::collections::HashSet;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};
use utoipa::openapi::Array;

use super::WhereClause;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
#[serde(untagged)]
pub enum Expr {
    #[serde(rename = "$val")]
    Val(Value),
    #[serde(untagged)]
    Operation { op: Operation, ex: Box<Expr> },
    #[serde(untagged)]
    Field(String),
}

impl Expr {
    pub fn op(op: Operation, ex: Expr) -> Self {
        Expr::Operation {
            op,
            ex: Box::new(ex),
        }
    }
    pub fn upper(self) -> Self {
        Expr::op(Operation::Upper, self)
    }

    pub fn lower(self) -> Self {
        Expr::op(Operation::Lower, self)
    }

    pub fn get_value(&self, value: &Value) -> Option<Value> {
        match self {
            Expr::Field(field) if field.contains("*") => value.x_get_property_pattern(field),
            Expr::Field(field) => value.x_get_property(field).cloned(),
            Expr::Val(val) => Some(val.clone()),
            Expr::Operation { op, ex } => op.apply_to(ex.get_value(value)),
        }
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            Expr::Field(field) => {
                let mut res = HashSet::new();
                res.insert(field.clone());
                res
            }
            Expr::Val(_) => HashSet::new(),
            Expr::Operation { op, ex } => {
                let mut res = ex.get_using_fields();
                res.extend(op.get_using_fields());
                res
            }
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub enum Operation {
    //string operations
    Upper,
    Lower,
    Replace(String, String),
    //array operations
    First,
    Last,
    Nth(usize),
    Slice(Option<usize>, Option<usize>),
    Count,
    Flatten,
    //commont
    Filter(Box<WhereClause>),
}

impl Operation {
    fn apply_to_recursive(&self, value: Option<Value>) -> Option<Value> {
        match value {
            Some(Value::Array(arr)) => arr
                .iter()
                .map(|v| self.apply_to_recursive(Some(v.clone())))
                .collect(),
            Some(Value::Object(obj)) => {
                let mut result = Map::new();
                for (k, v) in obj {
                    result.insert(k.clone(), self.apply_to_recursive(Some(v.clone())).unwrap());
                }
                Some(Value::Object(result))
            }
            Some(v) => self.apply_to(Some(v)),
            _ => None,
        }
    }

    fn get_using_fields(&self) -> HashSet<String> {
        HashSet::new()
    }

    pub fn apply_to(&self, value: Option<Value>) -> Option<Value> {
        match self {
            Operation::Upper => match value {
                Some(Value::String(s)) => Some(Value::String(s.to_uppercase())),
                Some(v @ Value::Array(_)) => self.apply_to_recursive(Some(v.clone())),
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
            Operation::Replace(first, second) => match value {
                Some(Value::String(s)) => Some(Value::String((s.replace(first, second)))),

                Some(v) => {
                    warn!("Cannot replcase non-string value {v}");
                    None
                }
                _ => None,
            },
            Operation::First => match value {
                Some(Value::Array(arr)) => arr.first().cloned(),
                Some(v) => {
                    warn!("Cannot get first element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Last => match value {
                Some(Value::Array(arr)) => arr.last().cloned(),
                Some(v) => {
                    warn!("Cannot get last element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Nth(n) => match value {
                Some(Value::Array(arr)) => arr.get(*n).cloned(),
                Some(v) => {
                    warn!("Cannot get nth element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Slice(start, end) => match value {
                Some(Value::Array(arr)) => {
                    let start = start.unwrap_or(0);
                    let end = end.unwrap_or(arr.len());
                    Some(Value::Array(arr[start..end].to_vec()))
                }
                Some(v) => {
                    warn!("Cannot slice non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Count => match value {
                Some(Value::Array(arr)) => Some(Value::Number(arr.len().into())),
                Some(v) => {
                    warn!("Cannot count non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Flatten => match value {
                Some(Value::Array(arr)) => {
                    let mut result = vec![];
                    for v in arr {
                        match v {
                            Value::Array(arr) => result.extend(arr),
                            v => result.push(v),
                        }
                    }
                    Some(Value::Array(result))
                }
                Some(v) => {
                    warn!("Cannot flatten non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Filter(where_clause) => match value {
                Some(Value::Array(arr)) => {
                    let mut result = vec![];
                    for v in arr {
                        if where_clause.filter(&v) {
                            result.push(v);
                        }
                    }
                    Some(Value::Array(result))
                }
                Some(v) => {
                    if where_clause.filter(&v) {
                        Some(v)
                    } else {
                        None
                    }
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
            "field1": "ValUe1",
        });
        let expr_field = Expr::Field("field1".to_string()).upper();
        let expr_val = Expr::Val(json!("vAluE1")).upper();
        let expected = Some(Value::String("VALUE1".to_string()));
        assert_eq!(expr_field.get_value(&val), expected);
        assert_eq!(expr_val.get_value(&val), expected);
    }

    #[test]
    fn expr_lower() {
        let val = json!({
            "field1": "ValUe1",
        });
        let expr_field = Expr::Field("field1".to_string()).lower();
        let expr_val = Expr::Val(json!("vAluE1")).lower();
        let expected = Some(Value::String("value1".to_string()));
        assert_eq!(expr_field.get_value(&val), expected);
        assert_eq!(expr_val.get_value(&val), expected);
    }

    // /* #region serialize/deserialize */
    // #[test]
    // fn serialize_expr_operation() {
    //     let expr = Expr::Field("field1".to_string()).upper().lower();
    //     let serialized = serde_json::to_string(&expr).unwrap();
    //     assert_eq!(
    //         serialized,
    //         r#"{"op":"lower","ex":{"op":"upper","ex":"field1"}}"#
    //     );
    // }

    // #[test]
    // fn deserialize_expr_operation() {
    //     let serialized = r#"{"op":"lower","ex":{"op":"upper","ex":"field1"}}"#;
    //     let expr: Expr = serde_json::from_str(serialized).unwrap();
    //     assert_eq!(expr, Expr::Field("field1".to_string()).upper().lower());
    // }

    // #[test]
    // fn serialize_expr_field() {
    //     let expr = Expr::Field("field1".to_string());
    //     let serialized = serde_json::to_string(&expr).unwrap();
    //     assert_eq!(serialized, r#""field1""#);
    // }

    // #[test]
    // fn deserialize_expr_field() {
    //     let serialized = r#""field1""#;
    //     let expr: Expr = serde_json::from_str(serialized).unwrap();
    //     assert_eq!(expr, Expr::Field("field1".to_string()));
    // }

    // #[test]
    // fn serialize_expr_val() {
    //     let expr = Expr::Val(json!("value1"));
    //     let serialized = serde_json::to_string(&expr).unwrap();
    //     assert_eq!(serialized, r#"{"$val":"value1"}"#);
    // }

    // #[test]
    // fn deserialize_expr_val() {
    //     let serialized = r#"{"$val":"value1"}"#;
    //     let expr: Expr = serde_json::from_str(serialized).unwrap();
    //     assert_eq!(expr, Expr::Val(json!("value1")));
    // }

    /* #endregion */
}
