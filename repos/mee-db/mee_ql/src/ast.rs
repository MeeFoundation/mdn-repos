use std::boxed::Box;
use std::collections::HashMap;
// ast.rs

use crate::visitor::{Visitable, Visitor};

// region Visitable implementations
impl<T> Visitable<T> for Query {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_query(self)
    }
}

impl<T> Visitable<T> for QueryBody {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_query_body(self)
    }
}

impl<T> Visitable<T> for IteratorStmt {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_iterator_stmt(self)
    }
}

impl<T> Visitable<T> for Assignment {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_assignment(self)
    }
}

impl<T> Visitable<T> for UpdateStmt {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_update_stmt(self)
    }
}

impl<T> Visitable<T> for DeleteStmt {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_delete_stmt(self)
    }
}

impl<T> Visitable<T> for BoolExpression {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_bool_expression(self)
    }
}

impl<T> Visitable<T> for Comparator {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_comparator(self)
    }
}

impl<T> Visitable<T> for Source {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_source(self)
    }
}

impl<T> Visitable<T> for Expression {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_expression(self)
    }
}

impl<T> Visitable<T> for Value {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_value(self)
    }
}

impl<T> Visitable<T> for Path {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_path(self)
    }
}
// endregion

#[derive(Debug, Clone, PartialEq)]
pub enum Query {
    ArrayQuery { body: QueryBody },
    ElementQuery { body: QueryBody },
}

#[derive(Debug, Clone, PartialEq)]
pub struct QueryBody {
    pub result: Option<Value>,
    pub iterators: Vec<IteratorStmt>,
    pub updates: Vec<UpdateStmt>,
    pub deletes: Vec<DeleteStmt>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct IteratorStmt {
    pub item: String,
    pub source: Source,
    pub assignments: HashMap<String, Expression>,
    pub filter: Option<BoolExpression>,
    pub offset: Option<usize>,
    pub limit: Option<usize>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Assignment {
    pub var: String,
    pub expr: Expression,
}

#[derive(Debug, Clone, PartialEq)]
pub struct UpdateStmt {
    pub field: Path,
    pub expr: Expression,
}

#[derive(Debug, Clone, PartialEq)]
pub struct DeleteStmt {
    pub path: Option<Path>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum BoolExpression {
    Comparison { val: Value, comparator: Comparator },
    And(Vec<BoolExpression>),
    Or(Vec<BoolExpression>),
    Not(Box<BoolExpression>),
    BoolPath(Path),
    True,
    False,
}
// region: BoolExpression implementations
impl From<bool> for BoolExpression {
    fn from(value: bool) -> Self {
        if value {
            BoolExpression::True
        } else {
            BoolExpression::False
        }
    }
}

impl From<&str> for BoolExpression {
    fn from(value: &str) -> Self {
        BoolExpression::BoolPath(Path(vec![value.to_string()]))
    }
}

impl From<Path> for BoolExpression {
    fn from(value: Path) -> Self {
        BoolExpression::BoolPath(value)
    }
}

impl BoolExpression {
    pub fn and<T>(self, other: T) -> Self
    where
        T: Into<BoolExpression>,
    {
        match self {
            BoolExpression::And(mut exprs) => {
                exprs.push(other.into());
                BoolExpression::And(exprs)
            }
            expr => BoolExpression::And(vec![expr, other.into()]),
        }
    }

    pub fn or<T>(self, other: T) -> Self
    where
        T: Into<BoolExpression>,
    {
        match self {
            BoolExpression::Or(mut exprs) => {
                exprs.push(other.into());
                BoolExpression::Or(exprs)
            }
            expr => BoolExpression::Or(vec![expr, other.into()]),
        }
    }

    pub fn not(self) -> Self {
        BoolExpression::Not(Box::new(self))
    }
}
// endregion

#[derive(Debug, Clone, PartialEq)]
pub enum Comparator {
    Eq(Expression),
    Ne(Expression),
    Gt(Expression),
    Lt(Expression),
    Ge(Expression),
    Le(Expression),
    Matches(Expression),
    Exists,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Source {
    PathSource(Path),
    ArraySource(Vec<Value>),
}

#[derive(Debug, Clone, PartialEq)]
pub enum Expression {
    Value(Value),
    Query(Box<Query>),
    BoolExpression(Box<BoolExpression>),
}

// region: Expression implementations
impl<T> From<T> for Expression
where
    T: Into<Value>,
{
    fn from(value: T) -> Self {
        Expression::Value(value.into())
    }
}
// endregion

#[derive(Debug, Clone, PartialEq)]
pub enum Value {
    Path(Path),
    Object(ValueMap),
    Array(Vec<Value>),
    Number(f64),
    String(String),
    Bool(bool),
    Null,
}

// region: Value implementations
impl From<bool> for Value {
    fn from(value: bool) -> Self {
        Value::Bool(value)
    }
}

impl From<&str> for Value {
    fn from(value: &str) -> Self {
        Value::String(value.to_string())
    }
}

impl From<isize> for Value {
    fn from(value: isize) -> Self {
        Value::Number(value as f64)
    }
}

impl From<f64> for Value {
    fn from(value: f64) -> Self {
        Value::Number(value)
    }
}

impl<T> From<Vec<T>> for Value
where
    T: Into<Value>,
{
    fn from(value: Vec<T>) -> Self {
        Value::Array(value.into_iter().map(|e| e.into()).collect::<Vec<_>>())
    }
}

impl From<Path> for Value {
    fn from(value: Path) -> Self {
        Value::Path(value)
    }
}

impl<T> From<HashMap<String, T>> for Value
where
    T: Into<Value>,
{
    fn from(value: HashMap<String, T>) -> Self {
        Value::Object(value.into_iter().map(|(k, v)| (k, v.into())).collect())
    }
}

impl Value {
    pub fn exists(self) -> BoolExpression {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Exists,
        }
    }
    pub fn matches<T>(self, pattern: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Matches(pattern.into()),
        }
    }

    pub fn eq<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Eq(other.into()),
        }
    }

    pub fn ne<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Ne(other.into()),
        }
    }

    pub fn gt<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Gt(other.into()),
        }
    }

    pub fn lt<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Lt(other.into()),
        }
    }

    pub fn ge<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Ge(other.into()),
        }
    }

    pub fn le<T>(self, other: T) -> BoolExpression
    where
        T: Into<Expression>,
    {
        BoolExpression::Comparison {
            val: self,
            comparator: Comparator::Le(other.into()),
        }
    }
}
// endregion

pub type ValueMap = HashMap<String, Value>;

#[derive(Debug, Clone, PartialEq)]
pub struct Path(pub Vec<String>);

impl<T> From<T> for Path
where
    T: Into<String>,
{
    fn from(value: T) -> Self {
        let str = value.into();
        let parts = str.split('.').map(|s| s.to_string()).collect();
        Path(parts)
    }
}
