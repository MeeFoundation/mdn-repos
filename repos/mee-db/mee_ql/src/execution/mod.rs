mod bool_expression_execution;
mod comparator_execution;
pub mod context;

mod expression_execution;
mod iterator_stmt_execution;
mod mee_value_execution;
mod path_execution;
mod query_execution;
mod support;

pub(crate) use crate::ast::*;
pub(crate) use crate::parser::TARGET_PATH_SEPARATOR as PATH_SEPARATOR;
pub(crate) use context::*;
pub(crate) use mee_value_execution::*;
pub(crate) use path_execution::*;
pub(crate) use serde_json::Value;

pub(crate) use bool_expression_execution::*;
pub(crate) use comparator_execution::*;
pub(crate) use context::*;
pub(crate) use expression_execution::*;
pub(crate) use iterator_stmt_execution::*;
pub(crate) use mee_storage::json_utils::*;
pub(crate) use query_execution::*;
pub(crate) use support::*;

pub(crate) use serde_json::Map;
pub(crate) use serde_json::Number;

pub(crate) use std::collections::HashMap;

pub type ContextStream =
    futures::stream::BoxStream<'static, Result<HashMap<String, Value>, String>>;
