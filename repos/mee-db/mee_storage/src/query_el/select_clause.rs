use super::{is_false, ConstOrField};

use regex::Regex;
use serde::de::Deserializer;
use serde::ser::{SerializeMap, Serializer};

use serde::{Deserialize, Serialize};

use serde_json::{json, Value};

use std::collections::hash_map::Entry::Vacant;
use std::collections::HashMap;
use std::collections::HashSet;
use tracing::warn;

use utoipa::ToSchema;

use crate::json_utils::JsonExt;

use super::expression::Expr;

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
        let map: HashMap<String, Value> = HashMap::deserialize(deserializer)?;
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
        Expr::Val(_) => "val".to_string(),
    }
}

impl SelectClause {
    pub(crate) fn pack(self) -> Self {
        match self {
            SelectClause::All => SelectClause::All,
            SelectClause::Fields(items) => {
                let mut map = HashMap::new();
                for item in items {
                    let alias = match item.clone() {
                        SelectClauseItem::SelectItem(expr) => generate_alias(&expr),
                        SelectClauseItem::NamedSelectItem { select, .. } => select.alias,
                    };
                    if let Vacant(e) = map.entry(alias.clone()) {
                        e.insert(item);
                    } else {
                        for i in 1.. {
                            let new_alias = format!("{}_{}", alias, i);
                            if let Vacant(e) = map.entry(new_alias) {
                                e.insert(item);
                                break;
                            }
                        }
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
    use serde_json::json;

    use super::super::_test_support::*;

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