#![allow(unused)]
use serde::Serialize;
use serde_json::Value;

use super::{
    derive_clause::DeriveClause, query::SelectQuery, where_clause::WhereClause, CheckOperator,
    Expr, Operation, SelectClause, SelectClauseItem,
};

pub fn de_expr(serialized: &str) -> Expr {
    serde_json::from_str(serialized).unwrap()
}

pub fn de_select_item(serialized: &str) -> SelectClauseItem {
    serde_json::from_str(serialized).unwrap()
}

pub fn de_select_clause(serialized: &str) -> SelectClause {
    let sc: SelectClause = serde_json::from_str(serialized).unwrap();
    sc.pack()
}

pub fn de_derive_clause(serialized: &str) -> DeriveClause {
    serde_json::from_str(serialized).unwrap()
}

pub fn de_select_query(serialized: &str) -> SelectQuery {
    serde_json::from_str(serialized).unwrap()
}

pub fn de_op(serialized: &str) -> Operation {
    serde_json::from_str(serialized).unwrap()
}

pub fn de_where_clause(serialized: &str) -> WhereClause {
    serde_json::from_str(serialized).unwrap()
}

pub fn print_json<T: Serialize>(v: &T) {
    println!("{}", serde_json::to_string_pretty(v).unwrap());
}

pub fn expr(v: Value) -> Expr {
    serde_json::from_value(v).unwrap()
}

pub fn cond(v: Value) -> CheckOperator {
    serde_json::from_value(v).unwrap()
}
