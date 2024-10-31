use serde_json::{Map, Value};

use crate::ast::Expression;

pub trait CastValue {
    fn cast_to_number(&self) -> Result<f64, String>;

    fn cast_to_bool(&self) -> Result<bool, String>;

    fn cast_to_string(&self) -> Result<String, String>;

    fn cast_to_array(&self) -> Result<Vec<Value>, String>;

    fn cast_to_object(&self) -> Result<Map<String, Value>, String>;
}

impl CastValue for Value {
    fn cast_to_number(&self) -> Result<f64, String> {
        self.as_f64()
            .ok_or(format!("Expected number at {:?}", &self))
    }

    fn cast_to_bool(&self) -> Result<bool, String> {
        self.as_bool()
            .ok_or(format!("Expected boolean at {:?}", &self))
    }

    fn cast_to_string(&self) -> Result<String, String> {
        self.as_str()
            .map(|s| s.to_string())
            .ok_or(format!("Expected string at {:?}", &self))
    }

    fn cast_to_array(&self) -> Result<Vec<Value>, String> {
        self.as_array()
            .map(|a| a.to_vec())
            .ok_or(format!("Expected array at {:?}", &self))
    }

    fn cast_to_object(&self) -> Result<Map<String, Value>, String> {
        self.as_object()
            .map(|o| o.clone())
            .ok_or(format!("Expected object at {:?}", &self))
    }
}

impl CastValue for Result<Value, String> {
    fn cast_to_number(&self) -> Result<f64, String> {
        match self {
            Ok(v) => v.cast_to_number(),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_bool(&self) -> Result<bool, String> {
        match self {
            Ok(v) => v.cast_to_bool(),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_string(&self) -> Result<String, String> {
        match self {
            Ok(v) => v.cast_to_string(),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_array(&self) -> Result<Vec<Value>, String> {
        match self {
            Ok(v) => v.cast_to_array(),
            Err(e) => Err(e.clone()),
        }
    }

    fn cast_to_object(&self) -> Result<Map<String, Value>, String> {
        match self {
            Ok(v) => v.cast_to_object(),
            Err(e) => Err(e.clone()),
        }
    }
}
