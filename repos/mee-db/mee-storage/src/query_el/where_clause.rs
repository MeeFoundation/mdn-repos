#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::condition::CheckOperator;
use super::expression::Expr;
use std::collections::HashSet;

#[derive(Debug, Clone, Deserialize, Serialize, PartialEq)]
#[serde(rename_all = "snake_case")]
pub enum WhereClause {
    True,
    False,
    Or(Vec<WhereClause>),
    Nor(Vec<WhereClause>),
    Not(Box<WhereClause>),
    #[serde(untagged)]
    And(Vec<WhereClause>),
    #[serde(untagged)]
    Check(Expr, CheckOperator),
}

impl WhereClause {
    pub fn check(expr: Expr, op: CheckOperator) -> Self {
        WhereClause::Check(expr, op)
    }

    pub fn or(self, other: WhereClause) -> Self {
        match self {
            WhereClause::Or(mut clauses) => {
                clauses.push(other);
                WhereClause::Or(clauses)
            }
            _ => WhereClause::Or(vec![self, other]),
        }
    }

    pub fn nor(self, other: WhereClause) -> Self {
        match self {
            WhereClause::Nor(mut clauses) => {
                clauses.push(other);
                WhereClause::Nor(clauses)
            }
            _ => WhereClause::Nor(vec![self, other]),
        }
    }

    pub fn and(self, other: WhereClause) -> Self {
        match self {
            WhereClause::And(mut clauses) => {
                clauses.push(other);
                WhereClause::And(clauses)
            }
            _ => WhereClause::And(vec![self, other]),
        }
    }

    pub fn not(self) -> Self {
        WhereClause::Not(Box::new(self))
    }

    pub fn filter(&self, value: &Value) -> bool {
        match self {
            WhereClause::True => true,
            WhereClause::False => false,
            WhereClause::Or(clauses) => clauses.iter().any(|clause| clause.filter(value)),
            WhereClause::Nor(clauses) => {
                clauses.iter().filter(|clause| clause.filter(value)).count() == 1
            }
            WhereClause::And(clauses) => clauses.iter().all(|clause| clause.filter(value)),
            WhereClause::Not(clause) => !clause.filter(value),
            WhereClause::Check(expr, op) => op.apply_to(value, expr),
        }
    }
    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            WhereClause::Check(expr, _) => expr.get_using_fields(),
            WhereClause::Or(clauses) => clauses
                .iter()
                .flat_map(|clause| clause.get_using_fields())
                .collect(),
            WhereClause::Nor(clauses) => clauses
                .iter()
                .flat_map(|clause| clause.get_using_fields())
                .collect(),
            WhereClause::And(clauses) => clauses
                .iter()
                .flat_map(|clause| clause.get_using_fields())
                .collect(),
            WhereClause::Not(clause) => clause.get_using_fields(),
            _ => HashSet::new(),
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::*;

    #[test]
    fn where_clause_true() {
        let val = json!({});
        assert!(WhereClause::True.filter(&val));
    }

    #[test]
    fn where_clause_false() {
        let val = json!({});
        assert!(!WhereClause::False.filter(&val));
    }

    #[test]
    fn where_clause_or() {
        let val = json!({});
        assert!(WhereClause::True.or(WhereClause::True).filter(&val));
        assert!(WhereClause::False.or(WhereClause::True).filter(&val));
        assert!(!WhereClause::False.or(WhereClause::False).filter(&val));
    }

    #[test]
    fn where_clause_and() {
        let val = json!({});
        assert!(!WhereClause::False.and(WhereClause::True).filter(&val));
        assert!(!WhereClause::False.and(WhereClause::False).filter(&val));
        assert!(WhereClause::True.and(WhereClause::True).filter(&val));
    }

    #[test]
    fn where_clause_not() {
        let val = json!({});
        assert!(WhereClause::False.not().filter(&val));
        assert!(!WhereClause::True.not().filter(&val));
    }

    #[test]
    fn where_clause_nor() {
        let val = json!({});
        assert!(WhereClause::False.nor(WhereClause::True).filter(&val));
        assert!(!WhereClause::False.nor(WhereClause::False).filter(&val));
        assert!(!WhereClause::True.nor(WhereClause::True).filter(&val));
    }
}
