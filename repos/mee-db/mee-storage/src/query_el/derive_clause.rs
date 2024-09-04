#![allow(unused)]

use super::{is_false, ConstOrField, Operation};
use crate::binary_kv_store::{PATH_PREFIX, PATH_SEPARATOR};
use clap::builder::Str;
use regex::Regex;
use serde::de::{Deserializer, MapAccess, Visitor};
use serde::ser::{SerializeMap, SerializeSeq, Serializer};

use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use serde_json::{map, Map};
use std::cmp::Ordering;
use std::collections::HashMap;
use std::collections::HashSet;
use tracing::{error, warn};
use tracing_subscriber::{
    filter::combinator::{And, Or},
    fmt::format,
};
use uuid::Uuid;

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::expression::Expr;

const EMPTY_STRING: &str = "";

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Default)]
pub struct DeriveClause(HashMap<String, Expr>);

impl DeriveClause {
    pub fn get_value(&self, value: &Value) -> Value {
        self.0.iter().fold(Value::Null, |mut acc, (k, v)| {
            if let Some(v) = v.get_value(Some(value)) {
                acc.x_set_property(k, v);
            }
            acc
        })
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        self.0.iter().fold(HashSet::new(), |mut acc, (_, v)| {
            acc.extend(v.get_using_fields());
            acc
        })
    }

    pub fn is_empty(&self) -> bool {
        self.0.is_empty()
    }
}

#[cfg(test)]
mod tests {
    use assert_json_diff::assert_json_eq;
    use serde::de;
    use serde_json::json;

    use super::super::_test_support::*;
    use crate::query_el::Operation;

    use super::*;

    #[test]
    fn derive_clause_item_named_select_item() {
        let val = json!({
            "field1": "value1"
        });
        let json = r#"{"new_field1": "a","new_field2": { "@field1": "$upper"}}"#;
        let item: DeriveClause = serde_json::from_str(json).unwrap();
        assert_eq!(
            item.get_value(&val),
            json!({
                "new_field1": "a",
                "new_field2": "VALUE1"
            })
        );
    }
}
