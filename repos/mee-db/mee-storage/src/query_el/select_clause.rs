#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use regex::Regex;
use serde_json::{json, Value};
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::{
    filter::combinator::{And, Or},
    fmt::format,
};
use uuid::Uuid;

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::expression::Expr;

#[derive(Debug, Clone)]
pub struct SelectClauseItem {
    pub(crate) expr: Expr,
    skip_nulls: bool,
    alias: String,
}

impl SelectClauseItem {
    pub fn get_value(&self, value: &Value) -> Option<Value> {
        self.expr.get_value(value)
    }
}

#[derive(Debug, Clone)]
pub enum SelectClause {
    All,
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
        let alias = alias.unwrap_or_else(|| {
            if let Expr::Field(field) = &expr {
                field.clone()
            } else {
                format!("field_{}", self.items.len() + 1)
            }
        });
        self.items.push(SelectClauseItem {
            expr,
            skip_nulls,
            alias,
        });
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

impl SelectClause {
    pub fn get_value(&self, value: Value) -> Value {
        match self {
            SelectClause::All => value,
            SelectClause::Fields(item) => item.iter().fold(json!({}), |mut acc, select_item| {
                match select_item.get_value(&value) {
                    Some(v) => {
                        acc.x_set_property(&select_item.alias, v);
                    }
                    _ => {
                        if !select_item.skip_nulls {
                            acc.x_set_property(&select_item.alias, Value::Null);
                        }
                    }
                }
                acc
            }),
        }
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
            .build();
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
                Expr::Operation(
                    Operation::Upper,
                    Box::new(Expr::Field("field2".to_string())),
                ),
                "upper_f2".to_string(),
            )
            .build();
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
            .build();

        let value = json!({});
        let result = select.get_value(value.clone());
        assert_eq!(result, json!({"f2": Value::Null}));
    }

    #[test]
    fn select_auto_alias() {
        let select = SelectClauseBuilder::new()
            .add_field(Expr::Field("field1".to_string()))
            .add_field(Expr::Field("field2".to_string()))
            .add_field(Expr::Operation(
                Operation::Upper,
                Box::new(Expr::Field("field2".to_string())),
            ))
            .build();
        let value = json!({
            "field1": "value1",
            "field2": "value2",
            "field3": "value3",
        });
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
            .build();
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
