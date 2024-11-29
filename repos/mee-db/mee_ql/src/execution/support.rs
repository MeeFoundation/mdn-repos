use serde_json::{Map, Value};

use super::MeeNode;
use crate::ast::*;
use crate::error::*;
use chrono::{DateTime, NaiveDate, NaiveDateTime, Utc};
use std::sync::Arc;

pub trait CastValue {
    fn actual_type(&self) -> NodeTypes;

    fn cast_to_number<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<f64>;

    fn cast_to_bool<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<bool>;

    fn cast_to_string<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<String>;

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>>;

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>>;

    fn cast_to_date<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<DateTime<Utc>>;
}

fn runtime_type_error_msg<T>(
    node: Arc<MeeNode<T>>,
    source_text: Arc<String>,
    expected: NodeTypes,
    found: NodeTypes,
) -> Error {
    Error::runtime_error(
        node.position.clone(),
        source_text.as_str(),
        format!("Expected type: {:?}, found: {:?}", expected, found),
    )
}

fn cast_runtime_type_error_msg<T>(
    node: Arc<MeeNode<T>>,
    source_text: Arc<String>,
    expected: NodeTypes,
    reason: &str,
) -> Error {
    Error::runtime_error(
        node.position.clone(),
        source_text.as_str(),
        format!("Casting to {:?} failed: {}", expected, reason),
    )
}
impl CastValue for Value {
    fn actual_type(&self) -> NodeTypes {
        match self {
            Value::Number(_) => NodeTypes::Number,
            Value::Bool(_) => NodeTypes::Bool,
            Value::String(_) => NodeTypes::String,
            Value::Array(_) => NodeTypes::Array,
            Value::Object(_) => NodeTypes::Object,
            Value::Null => NodeTypes::Null,
        }
    }
    fn cast_to_number<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<f64> {
        self.as_f64().ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Number, self.actual_type())
        })
    }

    fn cast_to_bool<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<bool> {
        self.as_bool().ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Bool, self.actual_type())
        })
    }

    fn cast_to_string<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<String> {
        self.as_str().map(|s| s.to_string()).ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::String, self.actual_type())
        })
    }

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>> {
        self.as_array().map(|a| a.to_vec()).ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Array, self.actual_type())
        })
    }

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>> {
        self.as_object().cloned().ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Object, self.actual_type())
        })
    }

    fn cast_to_date<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<DateTime<Utc>> {
        match self {
            Value::Number(v) if v.is_i64() && v.as_i64().unwrap() > 0 => {
                let date = DateTime::from_timestamp(v.as_i64().unwrap(), 0);
                date.ok_or(cast_runtime_type_error_msg(
                    node,
                    source_text,
                    NodeTypes::DateTime,
                    "Invalid timestamp",
                ))
            }
            Value::String(v) => {
                let str = v.as_str();
                let date = parse_date(str).ok_or(cast_runtime_type_error_msg(
                    node,
                    source_text,
                    NodeTypes::DateTime,
                    "Invalid date value",
                ))?;
                Ok(date)
            }
            _ => Err(cast_runtime_type_error_msg(
                node,
                source_text,
                NodeTypes::DateTime,
                "Invalid date value",
            )),
        }
    }
}

impl CastValue for Result<Value> {
    fn actual_type(&self) -> NodeTypes {
        match self {
            Ok(v) => v.actual_type(),
            Err(_) => NodeTypes::Null,
        }
    }
    fn cast_to_number<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<f64> {
        match self {
            Ok(v) => v.cast_to_number(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to number failed",
            )),
        }
    }

    fn cast_to_bool<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<bool> {
        match self {
            Ok(v) => v.cast_to_bool(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to bool failed",
            )),
        }
    }

    fn cast_to_string<T>(&self, node: Arc<MeeNode<T>>, source_text: Arc<String>) -> Result<String> {
        match self {
            Ok(v) => v.cast_to_string(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to string failed",
            )),
        }
    }

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>> {
        match self {
            Ok(v) => v.cast_to_array(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to array failed",
            )),
        }
    }

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>> {
        match self {
            Ok(v) => v.cast_to_object(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to object failed",
            )),
        }
    }

    fn cast_to_date<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<DateTime<Utc>> {
        match self {
            Ok(v) => v.cast_to_date(node, source_text),
            Err(_) => Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                "Casting to date failed",
            )),
        }
    }
}

fn parse_date(v: &str) -> Option<DateTime<Utc>> {
    if let Ok(dt) = DateTime::parse_from_str(v, "%Y-%m-%dT%H:%M:%S.%f %z")
        .or_else(|_| DateTime::parse_from_str(v, "%Y-%m-%dT%H:%M:%S %z"))
        .or_else(|_| DateTime::parse_from_str(v, "%Y-%m-%dT%H:%M %z"))
    {
        Some(dt.with_timezone(&Utc))
    } else if let Ok(dt) = NaiveDateTime::parse_from_str(v, "%Y-%m-%dT%H:%M:%S.%f")
        .or_else(|_| NaiveDateTime::parse_from_str(v, "%Y-%m-%dT%H:%M:%S"))
        .or_else(|_| NaiveDateTime::parse_from_str(v, "%Y-%m-%dT%H:%M"))
    {
        Some(DateTime::<Utc>::from_naive_utc_and_offset(dt, Utc))
    } else if let Ok(dt) = NaiveDate::parse_from_str(v, "%Y-%m-%d") {
        Some(DateTime::<Utc>::from_naive_utc_and_offset(
            dt.and_hms_opt(0, 0, 0).unwrap(),
            Utc,
        ))
    } else {
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use chrono::TimeZone;

    #[test]
    fn test_parse_date_with_timezone() {
        let date_str = "2024-11-25T14:48:00.000 +0000";
        let expected_date = Utc.with_ymd_and_hms(2024, 11, 25, 14, 48, 0).unwrap();
        assert_eq!(parse_date(date_str), Some(expected_date));
    }

    #[test]
    fn test_parse_date_without_timezone() {
        let date_str = "2024-11-25T14:48:00.000";
        let expected_date = Utc.with_ymd_and_hms(2024, 11, 25, 14, 48, 0).unwrap();
        assert_eq!(parse_date(date_str), Some(expected_date));
    }

    #[test]
    fn test_parse_date_with_seconds() {
        let date_str = "2024-11-25T14:48:00 +0000";
        let expected_date = Utc.with_ymd_and_hms(2024, 11, 25, 14, 48, 0).unwrap();
        assert_eq!(parse_date(date_str), Some(expected_date));
    }

    #[test]
    fn test_parse_date_with_minutes() {
        let date_str = "2024-11-25T14:48 +0000";
        let expected_date = Utc.with_ymd_and_hms(2024, 11, 25, 14, 48, 0).unwrap();
        assert_eq!(parse_date(date_str), Some(expected_date));
    }

    #[test]
    fn test_parse_date_only_date() {
        let date_str = "2024-11-25";
        let expected_date = Utc.with_ymd_and_hms(2024, 11, 25, 0, 0, 0).unwrap();
        assert_eq!(parse_date(date_str), Some(expected_date));
    }

    #[test]
    fn test_parse_date_invalid_format() {
        let date_str = "invalid-date";
        assert_eq!(parse_date(date_str), None);
    }
}
