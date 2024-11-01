mod bool_expression_execution;
mod comparator_execution;
use std::sync::Arc;

mod executor;
mod expression_execution;
mod iterator_stmt_execution;

mod path_execution;
mod query_execution;
mod support;
pub(crate) use crate::ast::*;
pub(crate) use crate::parser::TARGET_PATH_SEPARATOR as PATH_SEPARATOR;
use async_stream::{stream, try_stream};

pub(crate) use path_execution::*;
pub(crate) use serde_json::Value;

pub(crate) use bool_expression_execution::*;
pub(crate) use comparator_execution::*;

pub(crate) use expression_execution::*;
pub(crate) use iterator_stmt_execution::*;
pub(crate) use mee_storage::json_utils::*;
pub(crate) use query_execution::*;
pub(crate) use support::*;

pub(crate) use executor::*;
pub(crate) use serde_json::Map;
pub(crate) use serde_json::Number;

pub(crate) use crate::parser::Context;
pub(crate) use std::collections::HashMap;

use futures::stream::Stream;
use mee_storage::json_kv_store::Store;
use std::pin::Pin;

pub type RuntimeContext = HashMap<String, Value>;
pub type ContextStream = futures::stream::BoxStream<'static, Result<RuntimeContext, String>>;
pub type JsonResultStream = Pin<Box<dyn Stream<Item = Result<Value, String>> + Send>>;

pub fn query_executor(store: Store) -> Arc<dyn QueryExecutor + Send + Sync + 'static> {
    let path_executor = PathExecutorImpl::new();
    let bool_executor = BoolExpressionExecutorImpl::new(path_executor);
    let comparator_executor = ComparatorExecutorImpl::new(path_executor);
    let expression_executor = ExpressionExecutorImpl::new(path_executor);
    let iterator_executor = IteratorExecutorImpl::new(path_executor);
    QueryExecutorImpl::new(
        store,
        bool_executor,
        comparator_executor,
        expression_executor,
        iterator_executor,
    )
}
