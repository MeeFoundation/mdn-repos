#![allow(unused)]

use super::{is_false, ConstOrField, Operation};
use crate::binary_kv_store::{PATH_PREFIX, PATH_SEPARATOR};
use clap::builder::Str;
use regex::Regex;
use serde::de::{Deserializer, MapAccess, Visitor};
use serde::ser::{SerializeMap, SerializeSeq, Serializer};

use serde::{Deserialize, Serialize};
use serde_json::map;
use serde_json::{json, Value};
use std::cmp::Ordering;
use std::collections::HashMap;
use std::collections::HashSet;
use tracing::{error, warn};
use tracing_subscriber::{
    filter::combinator::{And, Or},
    fmt::format,
};
use utoipa::ToSchema;
use uuid::Uuid;

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::expression::Expr;

const EMPTY_STRING: &str = "";

#[derive(Debug, Clone, PartialEq, ToSchema)]
pub struct NamedField {
    pub alias: String,
    pub expr: Expr,
}

impl Serialize for NamedField {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut state = serializer.serialize_map(Some(1))?;
        state.serialize_entry(&self.alias, &self.expr)?;
        state.end()
    }
}

impl<'de> Deserialize<'de> for NamedField {
    fn deserialize<D>(deserializer: D) -> Result<NamedField, D::Error>
    where
        D: Deserializer<'de>,
    {
        let mut map: HashMap<String, Value> = HashMap::deserialize(deserializer)?;
        if let Some((alias, expr)) = map.into_iter().next() {
            let expr = serde_json::from_value(expr).map_err(serde::de::Error::custom)?;
            Ok(NamedField { alias, expr })
        } else {
            Err(serde::de::Error::custom(
                "NamedField should have one alias : value",
            ))
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, ToSchema)]
#[serde(rename_all = "snake_case")]
#[serde(untagged)]
pub enum SelectClauseItem {
    NamedSelectItem {
        #[serde(flatten)]
        select: NamedField,
        #[serde(default, skip_serializing_if = "is_false")]
        show_nulls: bool,
    },
    SelectItem(Expr),
}

impl SelectClauseItem {
    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            SelectClauseItem::SelectItem(expr) => expr.get_using_fields(),
            SelectClauseItem::NamedSelectItem { select, .. } => select.expr.get_using_fields(),
        }
    }

    pub fn get_value(&self, value: &Value) -> Option<Value> {
        match self {
            SelectClauseItem::SelectItem(expr) => expr.get_value(Some(value)),
            SelectClauseItem::NamedSelectItem {
                select,
                show_nulls: skip_nulls,
            } => {
                let v = select.expr.get_value(Some(value));
                if v.is_none() && !*skip_nulls {
                    Some(Value::Null)
                } else {
                    v
                }
            }
        }
    }
}

#[derive(Debug, Clone, Default, Serialize, Deserialize, PartialEq, ToSchema)]
#[serde(rename_all = "snake_case")]
pub enum SelectClause {
    #[default]
    #[serde(rename = "$all")]
    All,
    #[serde(untagged)]
    Fields(Vec<SelectClauseItem>),
}

fn sanitize_alias(alias: &str) -> String {
    let re = Regex::new(r"[\W]+").unwrap();
    re.replace_all(alias, "_").to_string()
}

fn generate_alias(expr: &Expr) -> String {
    match expr {
        Expr::Val(ConstOrField::Field(field)) => sanitize_alias(field),
        Expr::Operation { expr, op } => {
            format!("{}_{}", op, generate_alias(expr))
        }
        _ => "expr".to_string(),
    }
}

impl SelectClause {
    pub(crate) fn pack(self) -> Self {
        match self {
            SelectClause::All => SelectClause::All,
            SelectClause::Fields(items) => {
                let mut map = HashMap::new();
                for item in items.into_iter() {
                    let alias = match item.clone() {
                        SelectClauseItem::SelectItem(expr) => generate_alias(&expr),
                        SelectClauseItem::NamedSelectItem { select, .. } => select.alias,
                    };
                    if map.contains_key(&alias) {
                        for i in 1.. {
                            let new_alias = format!("{}_{}", &alias, i);
                            if !map.contains_key(&new_alias) {
                                map.insert(new_alias, item);
                                break;
                            }
                        }
                    } else {
                        map.insert(alias, item);
                    }
                }

                let items = map
                    .into_iter()
                    .map(|(alias, item)| match item {
                        SelectClauseItem::SelectItem(expr) => SelectClauseItem::NamedSelectItem {
                            select: NamedField { alias, expr },
                            show_nulls: false,
                        },
                        SelectClauseItem::NamedSelectItem { select, show_nulls } => {
                            SelectClauseItem::NamedSelectItem {
                                select: NamedField {
                                    alias,
                                    expr: select.expr,
                                },
                                show_nulls,
                            }
                        }
                    })
                    .collect::<Vec<_>>();

                SelectClause::Fields(items)
            }
        }
    }

    pub fn get_value(&self, value: Value) -> Value {
        match self {
            SelectClause::All => value,
            SelectClause::Fields(item) => item.iter().fold(json!({}), |mut acc, select_item| {
                if let Some(v) = select_item.get_value(&value) {
                    match select_item {
                        SelectClauseItem::SelectItem(_) => {
                            warn!("SelectItem should not be present in SelectClause::Fields");
                        }
                        SelectClauseItem::NamedSelectItem { select, .. } => {
                            acc.x_set_property(&select.alias, v);
                        }
                    }
                }
                acc
            }),
        }
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            SelectClause::All => HashSet::new(),
            SelectClause::Fields(items) => items.iter().fold(HashSet::new(), |mut acc, item| {
                acc.extend(item.get_using_fields());
                acc
            }),
        }
    }

    pub fn is_all(&self) -> bool {
        matches!(self, SelectClause::All)
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
    fn select_all() {
        let select = de_select_clause(r#""$all""#);
        let value = json!({
            "field1": "value1",
            "field2": "value2",
        });
        let result = select.get_value(value.clone());
        assert_eq!(result, value);
    }

    #[test]
    fn select_fields() {
        let select = de_select_clause(r#"[{"f1": "@field1"}, {"f2": "@field2"}, "@field3"]"#);
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });

        let result = select.get_value(value.clone());
        assert_json_eq!(
            result,
            json!({"f1": "value1", "f2": "value2", "field3": "value3"})
        );
    }
}
