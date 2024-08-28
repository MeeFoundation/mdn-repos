#![allow(unused)]

use super::is_false;
use crate::binary_kv_store::PATH_SEPARATOR;
use clap::builder::Str;
use regex::Regex;
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use std::cmp::Ordering;
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

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
#[serde(untagged)]
pub enum SelectClauseItem {
    Extended {
        expr: Expr,
        #[serde(default, skip_serializing_if = "is_false")]
        show_nulls: bool,
        #[serde(default, skip_serializing_if = "String::is_empty")]
        alias: String,
    },
    Simple(Expr),
}

impl SelectClauseItem {
    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            SelectClauseItem::Simple(expr) => expr.get_using_fields(),
            SelectClauseItem::Extended { expr, .. } => expr.get_using_fields(),
        }
    }

    pub fn get_value(&self, value: &Value) -> Option<Value> {
        match self {
            SelectClauseItem::Simple(expr) => expr.get_value(value),
            SelectClauseItem::Extended {
                expr,
                show_nulls: skip_nulls,
                alias,
            } => {
                let v = expr.get_value(value);
                if v.is_none() && !*skip_nulls {
                    Some(Value::Null)
                } else {
                    v
                }
            }
        }
    }

    pub fn alias(&self) -> &str {
        match self {
            SelectClauseItem::Simple(expr) => EMPTY_STRING,
            SelectClauseItem::Extended { alias, .. } => alias,
        }
    }

    pub fn skip_nulls(&self) -> bool {
        match self {
            SelectClauseItem::Simple(_) => false,
            SelectClauseItem::Extended {
                show_nulls: skip_nulls,
                ..
            } => *skip_nulls,
        }
    }
}

#[derive(Debug, Clone, Default, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub enum SelectClause {
    #[default]
    All,
    #[serde(untagged)]
    Fields(Vec<SelectClauseItem>),
}

#[derive(Debug, Clone)]
pub struct SelectClauseBuilder {
    items: Vec<SelectClauseItem>,
}

impl SelectClauseBuilder {
    pub fn new() -> Self {
        SelectClauseBuilder { items: Vec::new() }
    }

    pub fn add_field(mut self, expr: Expr) -> Self {
        self.specify_field(expr, None, true)
    }

    pub fn add_field_as(mut self, expr: Expr, alias: String) -> Self {
        self.specify_field(expr, Some(alias), true)
    }

    pub fn specify_field(mut self, expr: Expr, alias: Option<String>, skip_nulls: bool) -> Self {
        let item = if alias.is_none() && !skip_nulls {
            SelectClauseItem::Simple(expr)
        } else {
            SelectClauseItem::Extended {
                expr,
                show_nulls: skip_nulls,
                alias: alias.unwrap_or(EMPTY_STRING.to_string()),
            }
        };

        self.items.push(item);
        self
    }

    pub fn build(self) -> SelectClause {
        if self.items.is_empty() {
            SelectClause::All
        } else {
            SelectClause::Fields(self.items)
        }
    }
}

fn generate_alias(expt: &Expr, field_index: usize) -> String {
    match expt {
        Expr::Field(field) => {
            let re = Regex::new(r"[\W]+").unwrap();
            re.replace_all(&field, "_").to_string()
        }
        _ => format!("field_{}", field_index + 1),
    }
}

impl SelectClause {
    pub(crate) fn pack(self) -> Self {
        match self {
            SelectClause::All => SelectClause::All,
            SelectClause::Fields(items) => SelectClause::Fields(
                items
                    .into_iter()
                    .enumerate()
                    .map(|(i, item)| match item {
                        SelectClauseItem::Simple(expr) => SelectClauseItem::Extended {
                            show_nulls: false,
                            alias: generate_alias(&expr, i),
                            expr,
                        },
                        SelectClauseItem::Extended {
                            expr,
                            show_nulls: skip_nulls,
                            alias,
                        } => SelectClauseItem::Extended {
                            alias: if alias.is_empty() {
                                generate_alias(&expr, i)
                            } else {
                                alias
                            },
                            expr,
                            show_nulls: skip_nulls,
                        },
                    })
                    .collect(),
            ),
        }
    }

    pub fn get_value(&self, value: Value) -> Value {
        match self {
            SelectClause::All => value,
            SelectClause::Fields(item) => item.iter().fold(json!({}), |mut acc, select_item| {
                if let Some(v) = select_item.get_value(&value) {
                    acc.x_set_property(&select_item.alias(), v);
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
    use serde_json::json;

    use crate::query_el::Operation;

    use super::*;

    #[test]
    fn select_all() {
        let select = SelectClause::All;
        let value = json!({
            "field1": "value1",
            "field2": "value2",
        });
        let result = select.get_value(value.clone());
        assert_eq!(result, value);
    }

    #[test]
    fn select_fields() {
        let select = SelectClauseBuilder::new()
            .add_field_as(Expr::Field("field1".to_string()), "f1".to_string())
            .add_field_as(Expr::Field("field2".to_string()), "f2".to_string())
            .build()
            .pack();
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });

        let result = select.get_value(value.clone());
        assert_eq!(result, json!({"f1": "value1", "f2": "value2"}));
    }

    #[test]
    fn select_fields_with_expression() {
        let select = SelectClauseBuilder::new()
            .add_field_as(Expr::Field("field1".to_string()), "f1".to_string())
            .add_field_as(
                Expr::op(Operation::Upper, Expr::Field("field2".to_string())),
                "upper_f2".to_string(),
            )
            .build()
            .pack();
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });
        let result = select.get_value(value.clone());
        assert_eq!(result, json!({"f1": "value1", "upper_f2": "VALUE2"}));
    }

    #[test]
    fn select_nulls() {
        let select = SelectClauseBuilder::new()
            .add_field_as(Expr::Field("field1".to_string()), "f1".to_string())
            .specify_field(
                Expr::Field("non_existing_field".to_string()),
                Some("f2".to_string()),
                false,
            )
            .build()
            .pack();

        let value = json!({});
        let result = select.get_value(value.clone());
        assert_eq!(result, json!({"f2": Value::Null}));
    }

    #[test]
    fn select_auto_alias() {
        let select = SelectClauseBuilder::new()
            .add_field(Expr::Field("field1".to_string()))
            .add_field(Expr::Field("field2".to_string()))
            .add_field(Expr::op(
                Operation::Upper,
                Expr::Field("field2".to_string()),
            ))
            .build()
            .pack();
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });
        let select = select.pack();
        let result = select.get_value(value.clone());
        assert_eq!(
            result,
            json!({"field1": "value1", "field2": "value2", "field_3": "VALUE2"})
        );
    }

    #[test]
    fn select_with_specific_shape() {
        let select = SelectClauseBuilder::new()
            .add_field_as(
                Expr::Field("field1".to_string()),
                format!("f{PATH_SEPARATOR}f1"),
            )
            .add_field_as(
                Expr::Field("field2".to_string()),
                format!("f{PATH_SEPARATOR}f2{PATH_SEPARATOR}0"),
            )
            .add_field_as(Expr::Field("field3".to_string()), "f3".to_string())
            .build()
            .pack();
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });
        let result = select.get_value(value.clone());
        assert_eq!(
            result,
            json!({"f": {"f1":"value1", "f2": ["value2"]}, "f3": "value3"})
        );
    }
}
