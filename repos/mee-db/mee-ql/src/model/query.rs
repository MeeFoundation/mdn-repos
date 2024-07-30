use super::schema::{Field, FieldType, ObjectId, Schema};
use std::collections::HashMap;

use super::data::{NewObjectFieldSet, Records};
use super::schema::SchemaName;

#[derive(Debug)]
pub struct SelectQuery {
    pub schema: Schema,
    pub select_clause: Vec<SelectClause>,
    pub where_clause: Vec<WhereClause>,
    pub limit: Option<usize>,
    pub offset: Option<usize>,
    // group_by: Vec<Expr>,
    // having: Vec<WhereClause>,
    // order_by: Vec<Expr>,
}

#[derive(Debug)]
pub struct SelectClause {
    pub value: Expr,
    pub operations: Option<Vec<Operation>>,
    pub aggr: Option<Aggregation>,
    pub alias: Option<String>,
}

#[derive(Debug)]
pub enum Aggregation {
    Count,
    CountDistinct,
    Sum,
    Avg,
    Min,
    Max,
    MakeString {
        prefix: String,
        separator: String,
        suffix: String,
    },
    ToArray,
    GroupBy,
}

#[derive(Debug)]
pub enum Operation {
    Flatten,
}

#[derive(Debug)]
pub struct SelectQueryResult {
    pub result: Records,
    pub execution_stats: Option<HashMap<String, String>>,
}

#[derive(Debug)]
pub struct InsertQuery<'a> {
    pub schema: SchemaName,
    pub values: Vec<NewObjectFieldSet<'a>>,
}

#[derive(Debug)]
pub struct InsertQueryResult {
    pub result: Vec<ObjectId>,
    pub execution_stats: Option<HashMap<String, String>>,
}

#[derive(Debug)]
pub struct DeleteQuery {
    pub schema: Schema,          //query root
    pub remove: Vec<SchemaName>, //types to delete by path from root
    pub where_clause: Vec<WhereClause>,
}

#[derive(Debug)]
pub struct DeleteQueryResult {
    pub result: Vec<ObjectId>,
    pub execution_stats: Option<HashMap<String, String>>,
}

#[derive(Debug)]
pub struct UpdateQuery {
    pub schema: Schema,
    pub select_clause: Option<Vec<SelectClause>>,
    pub update_clause: Vec<UpdateClause>,
    pub where_clause: Vec<WhereClause>,
}

#[derive(Debug)]
pub struct UpdateQueryResult {
    pub result: Option<Records>,
    pub updated: usize,
    pub execution_stats: Option<HashMap<String, String>>,
}

#[derive(Debug)]
pub struct UpdateClause {
    pub field: Field,
    pub value: Option<Expr>,
}

#[derive(Debug)]
pub enum Expr {
    FieldPath(Vec<Field>),
    Literal(String, FieldType),
}

#[derive(Debug)]
pub enum WhereClause {
    Or(Vec<WhereClause>),
    Not(Box<WhereClause>),
    Check(Expr, CheckOperator),
}

#[derive(Debug)]
pub enum CheckOperator {
    Equal(Expr),
    NotEqual(Expr),
    GreaterThan(Expr),
    GreaterThanOrEqual(Expr),
    LessThan(Expr),
    LessThanOrEqual(Expr),
    Exists,
    NotExists,
}
