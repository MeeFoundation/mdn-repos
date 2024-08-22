#![allow(unused)]
use crate::error::Result;
use crate::json_kv_store::FieldFilter;
use crate::json_kv_store::JsonStream;

use super::condition::CheckOperator;
use super::expression::Expr;
use super::select_clause::{SelectClause, SelectClauseItem};
use super::where_clause::WhereClause;
use futures::stream::StreamExt;
use serde_json::Value;
use tracing::field;

pub struct SelectQuery {
    pub(crate) select_clause: SelectClause,
    pub(crate) where_clause: WhereClause,
    pub(crate) limit: Option<usize>,
    pub(crate) offset: usize,
    pub(crate) field_filter: FieldFilter,
}

impl SelectQuery {
    pub fn new() -> Self {
        SelectQuery {
            select_clause: SelectClause::All,
            where_clause: WhereClause::True,
            limit: None,
            offset: 0,
            field_filter: FieldFilter::All,
        }
    }
}

pub struct SelectQueryBuilder {
    select_clause: SelectClause,
    where_clause: WhereClause,
    limit: Option<usize>,
    offset: usize,
}

impl SelectQueryBuilder {
    pub fn select_all_fields() -> Self {
        SelectQueryBuilder {
            select_clause: SelectClause::All,
            where_clause: WhereClause::True,
            limit: None,
            offset: 0,
        }
    }

    pub fn select(select_clause: SelectClause) -> Self {
        SelectQueryBuilder {
            select_clause,
            where_clause: WhereClause::True,
            limit: None,
            offset: 0,
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

    pub fn offset(self, offset: usize) -> Self {
        SelectQueryBuilder { offset, ..self }
    }

    pub fn build(self) -> Result<SelectQuery> {
        let SelectQueryBuilder {
            select_clause,
            where_clause,
            limit,
            offset,
        } = self;

        let field_filter = match select_clause {
            SelectClause::All => FieldFilter::All,
            SelectClause::Fields(ref fields) => {
                let field_names = fields
                    .iter()
                    .filter_map(|field| match field {
                        SelectClauseItem {
                            expr: Expr::Field(ref name),
                            ..
                        } => Some(name.to_string()),
                        _ => None,
                    })
                    .collect::<Vec<_>>();

                FieldFilter::try_from_patterns(field_names)?
            }
        };

        Ok(SelectQuery {
            select_clause,
            where_clause,
            limit,
            offset,
            field_filter,
        })
    }
}
