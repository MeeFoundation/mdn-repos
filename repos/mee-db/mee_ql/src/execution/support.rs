use serde_json::{Map, Value};

use super::MeeNode;
use crate::ast::*;
use crate::error::*;
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
}
