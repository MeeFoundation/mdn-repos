#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::{PATH_PREFIX, PATH_SEPARATOR};
use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};
use serde::de::value;
use serde::ser::{Serialize as Ser, SerializeMap, SerializeSeq, Serializer};
use serde::{Deserialize, Serialize};
use serde_json::{Map, Value};
use std::cmp::Ordering;
use std::collections::HashSet;
use std::fmt::{self, Display, Formatter};
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};
use utoipa::openapi::Array;

use super::{where_clause, WhereClause};
use utoipa::ToSchema;

#[derive(Debug, Clone, PartialEq, Eq, Hash, ToSchema)]
pub enum ConstOrField {
    Const(Value),
    Field(String),
}

impl<'a> Deserialize<'a> for ConstOrField {
    fn deserialize<D>(deserializer: D) -> Result<ConstOrField, D::Error>
    where
        D: serde::Deserializer<'a>,
    {
        let value = Value::deserialize(deserializer)?;
        match value {
            Value::String(s) if s.starts_with(PATH_PREFIX) => {
                Ok(ConstOrField::Field(s[1..].to_string()))
            }
            _ => Ok(ConstOrField::Const(value)),
        }
    }
}

impl Serialize for ConstOrField {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        match self {
            ConstOrField::Field(field) => {
                serializer.serialize_str(&format!("{}{}", PATH_PREFIX, field))
            }
            ConstOrField::Const(value) => value.serialize(serializer),
        }
    }
}

impl ConstOrField {
    pub fn get_value(&self, value: &Value) -> Option<Value> {
        match self {
            ConstOrField::Field(field) if field.contains("*") => {
                value.x_get_property_pattern(&field)
            }
            ConstOrField::Field(field) => value.x_get_property(&field).cloned(),
            ConstOrField::Const(val) => Some(val.clone()),
        }
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            ConstOrField::Field(field) => {
                let mut res = HashSet::new();
                res.insert(field.clone());
                res
            }
            ConstOrField::Const(_) => HashSet::new(),
        }
    }
}

#[derive(Debug, Clone, PartialEq, ToSchema)]
pub enum Expr {
    Operation { expr: Box<Expr>, op: Box<Operation> },
    Val(ConstOrField),
}

impl Expr {
    pub fn get_value(&self, value: Option<&Value>) -> Option<Value> {
        match self {
            Expr::Val(elem) => value.and_then(|v| elem.get_value(v)),
            Expr::Operation { expr, op } => op.get_value(expr, value),
        }
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            Expr::Val(elem) => elem.get_using_fields(),
            Expr::Operation { expr, op } => {
                let mut res = HashSet::new();
                res.extend(expr.get_using_fields());
                res.extend(op.get_using_fields());
                res
            }
        }
    }
}

impl Serialize for Expr {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        match self {
            Expr::Val(elem) => elem.serialize(serializer),
            Expr::Operation { expr, op } => {
                if let Expr::Val(const_or_field) = &**expr {
                    match const_or_field {
                        ConstOrField::Field(field) => {
                            let mut map = serializer.serialize_map(Some(1))?;
                            map.serialize_entry(&format!("{}{}", PATH_PREFIX, field), op)?;
                            map.end()
                        }
                        ConstOrField::Const(Value::String(s)) => {
                            let mut map = serializer.serialize_map(Some(1))?;
                            map.serialize_entry(s, op)?;
                            map.end()
                        }
                        _ => {
                            let mut map = serializer.serialize_map(Some(2))?;
                            map.serialize_entry("expr", expr)?;
                            map.serialize_entry("op", op)?;
                            map.end()
                        }
                    }
                } else {
                    let mut map = serializer.serialize_map(Some(2))?;
                    map.serialize_entry("expr", expr)?;
                    map.serialize_entry("op", op)?;
                    map.end()
                }
            }
        }
    }
}

impl<'a> Deserialize<'a> for Expr {
    fn deserialize<D>(deserializer: D) -> Result<Expr, D::Error>
    where
        D: serde::Deserializer<'a>,
    {
        let value = Value::deserialize(deserializer)?;
        match value {
            Value::Object(map) => {
                if map.len() == 1 {
                    if let Some((key, value)) = map.into_iter().next() {
                        let const_or_field = serde_json::from_value(Value::String(key))
                            .map_err(serde::de::Error::custom)?;
                        let op = serde_json::from_value(value).map_err(serde::de::Error::custom)?;
                        Ok(Expr::Operation {
                            expr: Box::new(Expr::Val(const_or_field)),
                            op: Box::new(op),
                        })
                    } else {
                        Err(serde::de::Error::custom("Invalid value"))
                    }
                } else {
                    if let (Some(expr), Some(op)) =
                        (map.get("expr").cloned(), map.get("op").cloned())
                    {
                        let expr =
                            serde_json::from_value(expr).map_err(serde::de::Error::custom)?;
                        let op = serde_json::from_value(op).map_err(serde::de::Error::custom)?;
                        Ok(Expr::Operation {
                            expr: Box::new(expr),
                            op: Box::new(op),
                        })
                    } else {
                        Err(serde::de::Error::custom("Invalid value"))
                    }
                }
            }
            value => {
                let const_or_field =
                    serde_json::from_value(value).map_err(serde::de::Error::custom)?;
                Ok(Expr::Val(const_or_field))
            }
            _ => Err(serde::de::Error::custom("Invalid value")),
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, ToSchema)]
pub enum Operation {
    //string operations
    #[serde(rename = "$upper")]
    Upper,
    #[serde(rename = "$lower")]
    Lower,
    // Replace(Expr, Expr),
    //array operations
    #[serde(rename = "$first")]
    First,
    #[serde(rename = "$last")]
    Last,
    #[serde(rename = "$nth")]
    Nth(Expr),
    #[serde(rename = "$find")]
    Find(WhereClause),
    // Slice(Option<Expr>, Option<Expr>),
    #[serde(rename = "$count")]
    Count,
    #[serde(rename = "$flatten")]
    Flatten,
    //commont
    #[serde(rename = "$filter")]
    Filter(Box<WhereClause>),
}

impl Display for Operation {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        match self {
            Operation::Upper => write!(f, "upper"),
            Operation::Lower => write!(f, "lower"),
            // Operation::Replace(a, b) => write!(f, "replace"),
            Operation::First => write!(f, "first"),
            Operation::Last => write!(f, "last"),
            Operation::Nth(_) => write!(f, "nth"),
            Operation::Find(_) => write!(f, "find"),
            // Operation::Slice(start, end) => write!(f, "slice"),
            Operation::Count => write!(f, "count"),
            Operation::Flatten => write!(f, "flatten"),
            Operation::Filter(_) => write!(f, "filter"),
        }
    }
}

impl Operation {
    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            Operation::Upper => HashSet::new(),
            Operation::Lower => HashSet::new(),
            // Operation::Replace(a, b) => {
            //     let mut res = HashSet::new();
            //     res.extend(a.get_using_fields());
            //     res.extend(b.get_using_fields());
            //     res
            // }
            Operation::First => HashSet::new(),
            Operation::Last => HashSet::new(),
            Operation::Nth(expr) => expr.get_using_fields(),
            //TODO use more precise fields
            Operation::Find(where_clause) => where_clause.get_using_fields(),
            // Operation::Slice(start, end) => {
            //     let mut res = HashSet::new();
            //     if let Some(start) = start {
            //         res.extend(start.get_using_fields());
            //     }
            //     if let Some(end) = end {
            //         res.extend(end.get_using_fields());
            //     }
            //     res
            // }
            Operation::Count => HashSet::new(),
            Operation::Flatten => HashSet::new(),
            //TODO use more precise fields
            Operation::Filter(where_clause) => where_clause.get_using_fields(),
        }
    }

    pub fn get_value(&self, expr: &Expr, value: Option<&Value>) -> Option<Value> {
        match self {
            Operation::Upper => match expr.get_value(value) {
                Some(Value::String(s)) => Some(Value::String(s.to_uppercase())),
                // Some(v @ Value::Array(_)) => self.get_value_recursive(Some(v.clone())),
                Some(v) => {
                    warn!("Cannot uppercase non-string value {v}");
                    None
                }
                _ => None,
            },
            Operation::Lower => match expr.get_value(value) {
                Some(Value::String(s)) => Some(Value::String(s.to_lowercase())),
                Some(v) => {
                    warn!("Cannot lowercase non-string value {v}");
                    None
                }
                _ => None,
            },
            // Operation::Replace(first, second) => match (first.get_value(value), second.get_value(value), expr.get_value(value)) {   {
            //     (Some(Value::String(first), Value::String(second))) => Some(Value::String((first.replace(first, second)))),
            //     Some(Value::String(s)) => Some(Value::String((s.replace(first, second)))),

            //     Some(v) => {
            //         warn!("Cannot replcase non-string value {v}");
            //         None
            //     }
            //     _ => None,
            // },
            Operation::First => match expr.get_value(value) {
                Some(Value::Array(arr)) => arr.first().cloned(),
                Some(v) => {
                    warn!("Cannot get first element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Last => match expr.get_value(value) {
                Some(Value::Array(arr)) => arr.last().cloned(),
                Some(v) => {
                    warn!("Cannot get last element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Nth(n) => match (n.get_value(value), expr.get_value(value)) {
                (Some(Value::Number(n)), Some(Value::Array(arr))) => {
                    n.as_i64().and_then(|i| arr.get(i as usize)).cloned()
                }
                (_, Some(v)) => {
                    warn!("Cannot get nth element of non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Find(where_clause) => match (expr.get_value(value)) {
                Some(Value::Array(arr)) => arr.iter().find(|v| where_clause.filter(v)).cloned(),
                _ => None,
            },
            // Operation::Slice(start, end) => match value {
            //     Some(Value::Array(arr)) => {
            //         let start = start.unwrap_or(0);
            //         let end = end.unwrap_or(arr.len());
            //         Some(Value::Array(arr[start..end].to_vec()))
            //     }
            //     Some(v) => {
            //         warn!("Cannot slice non-array value {v}");
            //         None
            //     }
            //     _ => None,
            // },
            Operation::Count => match expr.get_value(value) {
                Some(Value::Array(arr)) => Some(Value::Number(arr.len().into())),
                Some(v) => {
                    warn!("Cannot count non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Flatten => match expr.get_value(value) {
                Some(Value::Array(arr)) => Some(
                    arr.iter()
                        .flat_map(|v| match v {
                            Value::Array(arr) => arr.iter().cloned().collect::<Vec<Value>>(),
                            v => vec![v.clone()],
                        })
                        .collect::<Vec<Value>>()
                        .into(),
                ),
                Some(v) => {
                    warn!("Cannot flatten non-array value {v}");
                    None
                }
                _ => None,
            },
            Operation::Filter(where_clause) => match expr.get_value(value) {
                Some(Value::Array(arr)) => Some(
                    arr.into_iter()
                        .filter(|v| where_clause.filter(v))
                        .collect::<Vec<Value>>()
                        .into(),
                ),
                Some(v) => {
                    if where_clause.filter(&v) {
                        Some(v.clone())
                    } else {
                        None
                    }
                }
                _ => None,
            },
        }
    }

    fn get_value_recursive(&self, value: Option<Value>) -> Option<Value> {
        match value {
            Some(Value::Array(arr)) => arr
                .iter()
                .map(|v| self.get_value_recursive(Some(v.clone())))
                .collect(),
            Some(Value::Object(obj)) => {
                let mut result = Map::new();
                for (k, v) in obj {
                    result.insert(
                        k.clone(),
                        self.get_value_recursive(Some(v.clone())).unwrap(),
                    );
                }
                Some(Value::Object(result))
            }
            Some(v) => self.get_value(&Expr::Val(ConstOrField::Const(v.clone())), Some(&v)),
            _ => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::super::_test_support::*;
    use super::super::test_support::expr;
    use super::*;

    #[test]
    fn deserialize_op() {
        assert_eq!(Operation::Upper, de_op(r#""$upper""#));
        assert_eq!(Operation::Lower, de_op(r#""$lower""#));
        assert_eq!(Operation::First, de_op(r#""$first""#));
        assert_eq!(Operation::Last, de_op(r#""$last""#));
        assert_eq!(
            Operation::Nth(Expr::Val(ConstOrField::Const(Value::Number(1.into())))),
            de_op(r#"{"$nth":1}"#)
        );
        assert_eq!(Operation::Count, de_op(r#""$count""#));
    }

    #[test]
    fn deserialize_expr_field() {
        assert_eq!(
            Expr::Val(ConstOrField::Field("field1".to_string())),
            de_expr(r#""@field1""#)
        );
    }

    #[test]
    fn deserialize_expr_const() {
        assert_eq!(
            Expr::Val(ConstOrField::Const(json!("value1"))),
            de_expr(r#""value1""#)
        );
    }

    #[test]
    fn deserialize_expr_op() {
        let upper_const_expr = Expr::Operation {
            expr: Box::new(Expr::Val(ConstOrField::Const(Value::String(
                "value1".to_string(),
            )))),
            op: Box::new(Operation::Upper),
        };

        let nth_const_expr = Expr::Operation {
            expr: Box::new(Expr::Val(ConstOrField::Const(json!([1, 2, 3])))),
            op: Box::new(Operation::Nth(Expr::Val(ConstOrField::Const(json!(2))))),
        };

        assert_eq!(upper_const_expr, de_expr(r#"{"value1":"$upper"}"#));
        assert_eq!(
            nth_const_expr,
            de_expr(r#"{"expr":[1,2,3],"op":{"$nth":2}}"#)
        );
    }

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

        let expr = de_expr(r#""@""#);
        assert_eq!(expr.get_value(Some(&val)), Some(val));
    }

    #[test]
    fn expr_upper() {
        let val = json!({
            "field1": "ValUe1",
        });
        let expr_field = de_expr(r#"{"@field1":"$upper"}"#);
        let expr_const = de_expr(r#"{"VaLue1":"$upper"}"#);
        let expected = Some(json!("VALUE1"));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
        assert_eq!(expr_const.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_lower() {
        let val = json!({
            "field1": "ValUe1",
        });
        let expr_field = de_expr(r#"{"@field1":"$lower"}"#);
        let expr_const = de_expr(r#"{"VaLue1":"$lower"}"#);
        let expected = Some(json!("value1"));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
        assert_eq!(expr_const.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_first() {
        let val = json!({
            "field1": [1, 2, 3],
        });
        let expr_field = de_expr(r#"{"@field1":"$first"}"#);
        let expected = Some(json!(1));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_last() {
        let val = json!({
            "field1": [1, 2, 3],
        });
        let expr_field = de_expr(r#"{"@field1":"$last"}"#);
        let expected = Some(json!(3));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_nth() {
        let val = json!({
            "field1": [1, 2, 3],
        });
        let expr_field = de_expr(r#"{"@field1":{"$nth":1}}"#);
        let expected = Some(json!(2));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_count() {
        let val = json!({
            "field1": [1, 2, 3],
        });
        let expr_field = de_expr(r#"{"@field1":"$count"}"#);
        let expected = Some(json!(3));
        assert_eq!(expr_field.get_value(Some(&val)), expected);
    }

    #[test]
    fn expr_get_value_pattern() {}
}
