#![allow(unused)]
use crate::error::Result;
use crate::json_kv_store::FieldFilter;
use crate::json_kv_store::JsonStream;

use super::condition::CheckOperator;
use super::expression::Expr;
use super::select_clause::{SelectClause, SelectClauseItem};
use super::where_clause::WhereClause;
use futures::stream::StreamExt;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use tracing::field;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub struct SelectQuery {
    #[serde(
        default,
        skip_serializing_if = "SelectClause::is_all",
        rename = "select"
    )]
    pub(crate) select_clause: SelectClause,
    // #[serde(flatten)]
    pub(crate) where_clause: WhereClause,

    // pub(crate) filters: Map<Expr,CheckOperator>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub(crate) limit: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub(crate) offset: Option<usize>,
}

impl SelectQuery {
    pub fn new() -> Self {
        SelectQuery {
            select_clause: SelectClause::All,
            where_clause: WhereClause::True,
            limit: None,
            offset: None,
        }
    }

    pub fn get_field_filter(&self) -> Result<FieldFilter> {
        if self.select_clause == SelectClause::All {
            Ok(FieldFilter::All)
        } else {
            let mut field_names = self.select_clause.get_using_fields();
            field_names.extend(self.where_clause.get_using_fields());
            let field_names = field_names.into_iter().collect();

            FieldFilter::try_from_patterns(field_names)
        }
    }
}

pub struct SelectQueryBuilder {
    select_clause: SelectClause,
    where_clause: WhereClause,
    limit: Option<usize>,
    offset: Option<usize>,
}

impl SelectQueryBuilder {
    pub fn select_all_fields() -> Self {
        SelectQueryBuilder {
            select_clause: SelectClause::All,
            where_clause: WhereClause::True,
            limit: None,
            offset: None,
        }
    }

    pub fn select(select_clause: SelectClause) -> Self {
        SelectQueryBuilder {
            select_clause,
            where_clause: WhereClause::True,
            limit: None,
            offset: None,
        }
    }

    pub fn where_clause(self, where_clause: WhereClause) -> Self {
        SelectQueryBuilder {
            where_clause,
            ..self
        }
    }

    pub fn limit(self, limit: usize) -> Self {
        SelectQueryBuilder {
            limit: Some(limit),
            ..self
        }
    }

    pub fn offset(self, offset: Option<usize>) -> Self {
        SelectQueryBuilder { offset, ..self }
    }

    pub fn build(self) -> Result<SelectQuery> {
        let SelectQueryBuilder {
            select_clause,
            where_clause,
            limit,
            offset,
        } = self;

        Ok(SelectQuery {
            select_clause,
            where_clause,
            limit,
            offset,
        })
    }
}

#[cfg(test)]
mod test {

    use crate::query_el::SelectClauseBuilder;

    use super::super::{
        expression::Expr::*, expression::Operation::*, select_clause::SelectClause,
        where_clause::WhereClause, CheckOperator::*,
    };

    use super::*;
    use assert_json_diff::assert_json_eq;
    use serde_json::json;
    use tracing_subscriber::fmt::FormatFields;

    #[test]
    fn serialize_default_select_query() {
        let query = SelectQuery {
            select_clause: SelectClause::All,
            where_clause: WhereClause::True,
            limit: None,
            offset: None,
        };
        let json = serde_json::to_string(&query).unwrap();
        assert_json_eq!(json, r#"{"where_clause":"true"}"#);
        let parsed_query: SelectQuery = serde_json::from_str(&json).unwrap();
        assert_eq!(parsed_query, query);
    }

    #[test]
    #[ignore = "reason"]
    fn serialize_complicated_select_query() {
        let query = SelectQueryBuilder::select(SelectClause::Fields(vec![
            SelectClauseItem::Simple(Field("name".to_string())),
            SelectClauseItem::Extended {
                expr: Field("field1".to_string()),
                show_nulls: true,
                alias: "f1".to_string(),
            },
            SelectClauseItem::Extended {
                expr: Field("field2".to_string()),
                show_nulls: false,
                alias: "f2".to_string(),
            },
        ]))
        .where_clause(
            WhereClause::Check(
                Field("field1".to_string()),
                CheckOperator::Equal(Expr::Val(json!("value1"))),
            )
            .and(WhereClause::Check(
                Operation {
                    ex: Box::new(Field("field2".to_string())),
                    op: Upper,
                },
                CheckOperator::Equal(Expr::Val(json!("VALUE2"))),
            )),
        )
        .limit(10)
        .offset(Some(5))
        .build()
        .unwrap();
        let json = serde_json::to_string(&query).unwrap();
        println!("{}", serde_json::to_string_pretty(&query).unwrap());
        assert_json_eq!(
            json,
            r#"{"select":["name",{"expr":"field1","show_nulls":true,"alias":"f1"},{"expr":"field2","alias":"f2"}],"check":["field1","value1"],"limit":10,"offset":5}"#
        );
        let parsed_query: SelectQuery = serde_json::from_str(&json).unwrap();
        assert_eq!(parsed_query, query);
    }
}
