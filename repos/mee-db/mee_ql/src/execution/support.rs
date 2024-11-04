use serde_json::{Map, Value};

use crate::ast::*;

use super::MeeNode;
use std::sync::Arc;

pub trait CastValue {
    fn actual_type(&self) -> NodeTypes;

    fn cast_to_number<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<f64, String>;

    fn cast_to_bool<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<bool, String>;

    fn cast_to_string<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<String, String>;

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>, String>;

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>, String>;
}

fn runtime_type_error_msg<T>(
    node: Arc<MeeNode<T>>,
    source_text: Arc<String>,
    expected: NodeTypes,
    found: NodeTypes,
) -> String {
    //only for testing
    // let error_place = format!("\x1b[31m{}\x1b[0m", &source_text[node.start..node.end]);
    let error_place = format!("<!{}!>", &source_text[node.start..node.end]);
    format!(
        "Runtime error at position ({}, {}) (wrapped in '<!_!>') {}{}{} -  Expected type: {:?}, found: {:?}",
        node.start,
        node.end,
        &source_text[..node.start],
        error_place,
        &source_text[node.end..],
        expected,
        found
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
    fn cast_to_number<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<f64, String> {
        self.as_f64().ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Number, self.actual_type())
        })
    }

    fn cast_to_bool<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<bool, String> {
        self.as_bool().ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Bool, self.actual_type())
        })
    }

    fn cast_to_string<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<String, String> {
        self.as_str().map(|s| s.to_string()).ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::String, self.actual_type())
        })
    }

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>, String> {
        self.as_array().map(|a| a.to_vec()).ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Array, self.actual_type())
        })
    }

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>, String> {
        self.as_object().map(|o| o.clone()).ok_or({
            runtime_type_error_msg(node, source_text, NodeTypes::Object, self.actual_type())
        })
    }
}

impl CastValue for Result<Value, String> {
    fn actual_type(&self) -> NodeTypes {
        match self {
            Ok(v) => v.actual_type(),
            Err(_) => NodeTypes::Null,
        }
    }
    fn cast_to_number<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<f64, String> {
        match self {
            Ok(v) => v.cast_to_number(node, source_text),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_bool<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<bool, String> {
        match self {
            Ok(v) => v.cast_to_bool(node, source_text),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_string<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<String, String> {
        match self {
            Ok(v) => v.cast_to_string(node, source_text),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_array<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Vec<Value>, String> {
        match self {
            Ok(v) => v.cast_to_array(node, source_text),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_object<T>(
        &self,
        node: Arc<MeeNode<T>>,
        source_text: Arc<String>,
    ) -> Result<Map<String, Value>, String> {
        match self {
            Ok(v) => v.cast_to_object(node, source_text),
            Err(e) => Err(e.clone()),
        }
    }
}
