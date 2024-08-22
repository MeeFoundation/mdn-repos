#![allow(dead_code)]
#![allow(unused)]

use crate::binary_kv_store::PATH_SEPARATOR;
use serde_json::Value;
use std::cmp::Ordering;
use tracing::{error, warn};
use tracing_subscriber::filter::combinator::{And, Or};

use crate::{json_kv_store::FieldFilter, json_utils::JsonExt};

use super::condition::CheckOperator;
use super::expression::Expr;

#[derive(Debug, Clone)]
pub enum WhereClause {
    True,
    False,
    Or(Vec<WhereClause>),
    And(Vec<WhereClause>),
    Not(Box<WhereClause>),
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
            WhereClause::And(clauses) => clauses.iter().all(|clause| clause.filter(value)),
            WhereClause::Not(clause) => !clause.filter(value),
            WhereClause::Check(expr, op) => op.apply_to(value, expr),
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
        let clause = WhereClause::True;
        assert!(clause.filter(&val));
    }

    #[test]
    fn where_clause_false() {
        let val = json!({});
        let clause = WhereClause::False;
        assert!(!clause.filter(&val));
    }

    #[test]
    fn where_clause_or() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let clause = WhereClause::Check(
            Expr::Field(format!("field2{PATH_SEPARATOR}field4")),
            CheckOperator::Equal(Expr::Val(Value::Number(5.into()))),
        );
        assert!(!clause.filter(&val));
        assert!(clause.or(WhereClause::True).filter(&val));
    }

    #[test]
    fn where_clause_and() {
        let val = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": 4,
                "field5": ["value4", "value5"]
            }
        });
        let clause1 = WhereClause::Check(
            Expr::Field(format!("field2{PATH_SEPARATOR}field4")),
            CheckOperator::Equal(Expr::Val(Value::Number(4.into()))),
        );
        let clause2 = WhereClause::Check(
            Expr::Field(format!("field1")),
            CheckOperator::Equal(Expr::Val(Value::String("value1".to_string()))),
        );
        assert!(clause1.clone().and(clause2.clone()).filter(&val));
        assert!(!clause1.and(clause2).and(WhereClause::False).filter(&val));
    }
}
