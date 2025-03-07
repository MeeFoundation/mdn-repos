use crate::error::*;
use mee_storage::json_kv_store::JsonStoreRecord;
use std::boxed::Box;
use std::collections::HashMap;

pub const TARGET_PATH_SEPARATOR: char = mee_storage::PATH_SEPARATOR;

/* #region AST */
#[derive(Debug, Clone, PartialEq)]
pub enum QueryType {
    FirstOrNull,
    All,
}

#[derive(Debug, Clone, PartialEq, Hash, Eq)]
pub enum NodeTypes {
    Number,
    String,
    Bool,
    Array,
    Object,
    Users,
    AbsolutePath,
    DateTime,
    Null,
}

#[derive(Debug, Clone, PartialEq, Hash, Eq)]
pub struct Position(pub usize, pub usize);

#[derive(Debug, Clone, PartialEq, Hash, Eq)]
pub struct MeeNode<T> {
    pub value: T,
    pub position: Position,
    pub expected_type: Option<NodeTypes>,
}

impl<T> MeeNode<T> {
    pub fn new(value: T, start: usize, end: usize) -> Self {
        Self {
            value,
            position: Position(start, end),
            expected_type: None,
        }
    }

    pub fn with_type(self, expected_type: NodeTypes) -> Self {
        Self {
            expected_type: Some(expected_type),
            ..self
        }
    }

    pub fn with_optional_type(self, expected_type: Option<NodeTypes>) -> Self {
        Self {
            expected_type,
            ..self
        }
    }

    pub fn map<F, U>(&self, f: F) -> MeeNode<U>
    where
        F: FnOnce(&T) -> U,
    {
        MeeNode::new(f(&self.value), self.position.0, self.position.1)
    }

    pub fn check_type(&self, expected_type: &NodeTypes, source_code: &str) -> Result<&Self> {
        if let Some(inner_type) = self.expected_type.as_ref() {
            match (inner_type, expected_type) {
                (NodeTypes::AbsolutePath, NodeTypes::AbsolutePath) => Ok(self),
                (NodeTypes::AbsolutePath, _) => Ok(self),
                (t, u) if t == u => Ok(self),
                _ => {
                    let reason = format!(
                        "Expected type: {:?}, found: {:?}",
                        expected_type, inner_type
                    );
                    Err(Error::validation_error(
                        self.position.clone(),
                        source_code,
                        reason,
                    ))
                }
            }
        } else {
            Ok(self)
        }
    }

    pub fn check_optional_type(
        &self,
        expected_type: &Option<NodeTypes>,
        source_code: &str,
    ) -> Result<&Self> {
        if let Some(inner_type) = expected_type.as_ref() {
            self.check_type(inner_type, source_code)
        } else {
            Ok(self)
        }
    }
}

#[derive(Debug, Clone)]
pub struct Query {
    pub result: Option<MeeNode<Expression>>,
    pub main_iterator: MeeNode<IteratorStmt>,
    pub statements: Vec<MeeNode<Statement>>,
    pub query_type: QueryType,
}

#[derive(Debug, Clone)]
pub enum Statement {
    Iterator(IteratorStmt),
    Assignment((MeeNode<String>, MeeNode<Expression>)),
    Update((MeeNode<Path>, MeeNode<Expression>)),
    Delete(MeeNode<Path>),
    AppendMany((MeeNode<Path>, MeeNode<Expression>)),
    Filter(MeeNode<BoolExpression>),
    Offset(usize),
    Limit(usize),
}

#[derive(Debug, Clone)]
pub struct IteratorStmt {
    pub item: MeeNode<String>,
    pub source: MeeNode<Expression>,
}

#[derive(Debug, Clone)]
pub enum BoolExpression {
    Comparison {
        val: MeeNode<Expression>,
        comparator: MeeNode<Comparator>,
    },
    And(Vec<MeeNode<BoolExpression>>),
    Or(Vec<MeeNode<BoolExpression>>),
    Not(Box<MeeNode<BoolExpression>>),
    Expression(MeeNode<Expression>),
    True,
    False,
}

#[derive(Debug, Clone)]
pub enum Comparator {
    Eq(MeeNode<Expression>),
    Ne(MeeNode<Expression>),
    Gt(MeeNode<Expression>),
    Lt(MeeNode<Expression>),
    Ge(MeeNode<Expression>),
    Le(MeeNode<Expression>),
    Matches(MeeNode<Expression>),
    After(MeeNode<Expression>),
    Before(MeeNode<Expression>),
    Between(MeeNode<Expression>, MeeNode<Expression>),
    Contains(MeeNode<Expression>),
    Exists,
}

#[derive(Debug, Clone)]
pub enum Expression {
    User(JsonStoreRecord),
    //complex
    Query(Box<MeeNode<Query>>),
    BoolExpression(Box<MeeNode<BoolExpression>>),
    Link(MeeNode<Path>),
    //simple
    Object(HashMap<String, MeeNode<Expression>>),
    Array(Vec<MeeNode<Expression>>),
    Number(f64),
    String(String),
    Bool(bool),
    Null,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct Path {
    pub root: String,
    pub field: Option<String>,
}

impl Path {
    pub fn combine(&self, path: Path) -> Self {
        let field = match (self.field.as_ref(), path.field.as_ref()) {
            (Some(field1), Some(field2)) => {
                Some(format!("{field1}{TARGET_PATH_SEPARATOR}{field2}"))
            }
            (Some(field), Option::None) => Some(field.clone()),
            (Option::None, Some(field)) => Some(field.clone()),
            (Option::None, Option::None) => None,
        };

        Path {
            root: self.root.clone(),
            field,
        }
    }

    pub fn new<T>(value: T) -> Self
    where
        T: Into<String>,
    {
        let str = value.into();
        let parts = str.split(".").collect::<Vec<_>>();
        if parts.len() == 1 {
            Path {
                root: parts.first().unwrap_or(&"").to_string(),
                field: None,
            }
        } else if parts.is_empty() {
            Path {
                root: "".to_string(),
                field: None,
            }
        } else {
            Path {
                root: parts[0].to_string(),
                field: Some(parts[1..].join(&TARGET_PATH_SEPARATOR.to_string())),
            }
        }
    }
}
/* #endregion */
