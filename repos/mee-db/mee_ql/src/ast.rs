use crate::error::*;
use mee_storage::json_utils::ID_PREFIX;
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

#[derive(Debug, Clone, PartialEq)]
pub struct Query {
    pub result: Option<MeeNode<Expression>>,
    pub main_iterator: MeeNode<IteratorStmt>,
    pub statements: Vec<MeeNode<Statement>>,
    pub query_type: QueryType,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Statement {
    Iterator(IteratorStmt),
    Assignment((MeeNode<String>, MeeNode<Expression>)),
    Update((MeeNode<Path>, MeeNode<Expression>)),
    Delete(MeeNode<Path>),
    Filter(MeeNode<BoolExpression>),
    Offset(usize),
    Limit(usize),
}

#[derive(Debug, Clone, PartialEq)]
pub struct IteratorStmt {
    pub item: MeeNode<String>,
    pub source: MeeNode<Source>,
}

#[derive(Debug, Clone, PartialEq)]
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

#[derive(Debug, Clone, PartialEq)]
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

#[derive(Debug, Clone, PartialEq)]
pub enum Source {
    PathSource(MeeNode<Path>),
    ArraySource(Vec<MeeNode<Expression>>),
}

#[derive(Debug, Clone, PartialEq)]
pub enum Expression {
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
        let rest = if let Some(field) = path.field {
            format!("{}{TARGET_PATH_SEPARATOR}{field}", path.root)
        } else {
            path.root
        };
        let field = if let Some(field) = self.field.as_ref() {
            format!("{}{TARGET_PATH_SEPARATOR}{field}", field)
        } else {
            rest
        };
        Path {
            root: self.root.clone(),
            field: Some(field),
        }
    }

    pub fn to_store_path(&self, id: &str) -> String {
        let root = if &self.root == "users" {
            "".to_string()
        } else {
            format!("{TARGET_PATH_SEPARATOR}{}", self.root)
        };
        if let Some(field) = &self.field {
            format!("{ID_PREFIX}{id}{root}{TARGET_PATH_SEPARATOR}{field}")
        } else {
            format!("{ID_PREFIX}{id}{root}{TARGET_PATH_SEPARATOR}{root}")
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
