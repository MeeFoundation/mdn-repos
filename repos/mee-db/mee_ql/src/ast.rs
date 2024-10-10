use std::boxed::Box;

// ast.rs

use crate::visitor::{Visitable, Visitor};

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

impl<T> Visitable<T> for Object {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_object(self)
    }
}

impl<T> Visitable<T> for Pair {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_pair(self)
    }
}

impl<T> Visitable<T> for Array {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_array(self)
    }
}

impl<T> Visitable<T> for Path {
    fn accept(&self, visitor: &mut dyn Visitor<T>) -> T {
        visitor.visit_path(self)
    }
}

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
    pub assignments: Vec<Assignment>,
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
    ArraySource(Array),
}

#[derive(Debug, Clone, PartialEq)]
pub enum Expression {
    Value(Value),
    Query(Box<Query>),
    BoolExpression(Box<BoolExpression>),
}

#[derive(Debug, Clone, PartialEq)]
pub enum Value {
    Path(Path),
    Object(Object),
    Array(Array),
    Number(f64),
    String(String),
    Bool(bool),
    Null,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Object {
    pub pairs: Vec<Pair>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Pair {
    pub key: String,
    pub value: Value,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Array(pub Vec<Expression>);

#[derive(Debug, Clone, PartialEq)]
pub struct Path(pub Vec<String>);
