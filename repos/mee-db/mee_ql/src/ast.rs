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
    Null,
}

#[derive(Debug, Clone, PartialEq, Hash, Eq)]
pub struct MeeNode<T> {
    pub value: T,
    pub start: usize,
    pub end: usize,
    pub expected_type: Option<NodeTypes>,
}

impl<T> MeeNode<T> {
    pub fn new(value: T, start: usize, end: usize) -> Self {
        Self {
            value,
            start,
            end,
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
        MeeNode::new(f(&self.value), self.start, self.end)
    }

    pub fn check_type(
        &self,
        expected_type: &NodeTypes,
        source_code: &str,
    ) -> Result<&Self, String> {
        if let Some(inner_type) = self.expected_type.as_ref() {
            match (inner_type, expected_type) {
                (NodeTypes::AbsolutePath, NodeTypes::AbsolutePath) => Ok(self),
                (NodeTypes::AbsolutePath, _) => Ok(self),
                (t, u) if t == u => Ok(self),
                _ => {
                    //only for testing
                    // let error_place = format!("\x1b[31m{}\x1b[0m", &source_code[self.start..self.end]);
                    let error_place = format!("<!{}!>", &source_code[self.start..self.end]);
                    let msg = format!(
                    "Position ({}, {}) (wrapped in '<!_!>') {}{}{} -  Expected type: {:?}, found: {:?}",
                    self.start,
                    self.end,
                    &source_code[..self.start],
                    error_place,
                    &source_code[self.end..],
                    expected_type,
                    inner_type
                );
                    Err(msg)
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
    ) -> Result<&Self, String> {
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
    pub embedded_iterators: Vec<MeeNode<IteratorStmt>>,
    pub updates: HashMap<MeeNode<Path>, MeeNode<Expression>>,
    pub deletes: MeeNode<DeleteStmt>,
    pub query_type: QueryType,
}

#[derive(Debug, Clone, PartialEq)]
pub enum DeleteStmt {
    Paths(Vec<MeeNode<Path>>),
    All,
    None,
}

#[derive(Debug, Clone, PartialEq)]
pub struct IteratorStmt {
    pub item: MeeNode<String>,
    pub source: MeeNode<Source>,
    pub assignments: HashMap<MeeNode<String>, MeeNode<Expression>>,
    pub filter: Option<MeeNode<BoolExpression>>,
    pub offset: Option<usize>,
    pub limit: Option<usize>,
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
                root: parts.first().unwrap().to_string(),
                field: None,
            }
        } else if parts.len() == 0 {
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

// #[cfg(test)]
// pub mod test_support_impls {
//     use super::*;

//     impl Path {
//         pub fn from_dot_separated<T>(str: T) -> Self
//         where
//             T: Into<String>,
//         {
//             str.into().into()
//         }
//     }

//     impl<T> From<T> for Path
//     where
//         T: Into<String>,
//     {
//         fn from(value: T) -> Self {
//             Path::new(value)
//         }
//     }

//     // region: BoolExpression implementations
//     impl From<bool> for BoolExpression {
//         fn from(value: bool) -> Self {
//             if value {
//                 BoolExpression::True
//             } else {
//                 BoolExpression::False
//             }
//         }
//     }

//     impl From<&str> for BoolExpression {
//         fn from(value: &str) -> Self {
//             BoolExpression::Expression(Expression::Link(Path::from(value)))
//         }
//     }

//     impl From<Path> for BoolExpression {
//         fn from(value: Path) -> Self {
//             BoolExpression::Expression(Expression::Link(value))
//         }
//     }

//     impl BoolExpression {
//         pub fn and<T>(self, other: T) -> Self
//         where
//             T: Into<BoolExpression>,
//         {
//             match self {
//                 BoolExpression::And(mut exprs) => {
//                     exprs.push(other.into());
//                     BoolExpression::And(exprs)
//                 }
//                 expr => BoolExpression::And(vec![expr, other.into()]),
//             }
//         }

//         pub fn or<T>(self, other: T) -> Self
//         where
//             T: Into<BoolExpression>,
//         {
//             match self {
//                 BoolExpression::Or(mut exprs) => {
//                     exprs.push(other.into());
//                     BoolExpression::Or(exprs)
//                 }
//                 expr => BoolExpression::Or(vec![expr, other.into()]),
//             }
//         }

//         pub fn not(self) -> Self {
//             BoolExpression::Not(Box::new(self))
//         }
//     }
//     // endregion

//     // region: Value implementations
//     impl From<bool> for Expression {
//         fn from(value: bool) -> Self {
//             Expression::Bool(value)
//         }
//     }

//     impl From<&str> for Expression {
//         fn from(value: &str) -> Self {
//             Expression::String(value.to_string())
//         }
//     }

//     impl From<isize> for Expression {
//         fn from(value: isize) -> Self {
//             Expression::Number(value as f64)
//         }
//     }

//     impl From<f64> for Expression {
//         fn from(value: f64) -> Self {
//             Expression::Number(value)
//         }
//     }

//     impl<T> From<Vec<T>> for Expression
//     where
//         T: Into<Expression>,
//     {
//         fn from(value: Vec<T>) -> Self {
//             Expression::Array(value.into_iter().map(|e| e.into()).collect::<Vec<_>>())
//         }
//     }

//     impl From<Path> for Expression {
//         fn from(value: Path) -> Self {
//             Expression::Link(value)
//         }
//     }

//     impl<S, T> From<HashMap<S, T>> for Expression
//     where
//         T: Into<Expression>,
//         S: Into<String>,
//     {
//         fn from(value: HashMap<S, T>) -> Self {
//             Expression::Object(
//                 value
//                     .into_iter()
//                     .map(|(k, v)| (k.into(), v.into()))
//                     .collect(),
//             )
//         }
//     }

//     impl Expression {
//         pub fn exists(self) -> BoolExpression {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Exists,
//             }
//         }
//         pub fn matches<T>(self, pattern: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Matches(pattern.into()),
//             }
//         }

//         pub fn eq<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Eq(other.into()),
//             }
//         }

//         pub fn ne<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Ne(other.into()),
//             }
//         }

//         pub fn gt<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Gt(other.into()),
//             }
//         }

//         pub fn lt<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Lt(other.into()),
//             }
//         }

//         pub fn ge<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Ge(other.into()),
//             }
//         }

//         pub fn le<T>(self, other: T) -> BoolExpression
//         where
//             T: Into<Expression>,
//         {
//             BoolExpression::Comparison {
//                 val: self,
//                 comparator: Comparator::Le(other.into()),
//             }
//         }
//     }
//     // endregion
// }
