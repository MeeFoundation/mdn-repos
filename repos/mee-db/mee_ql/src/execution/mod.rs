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

pub(crate) use std::collections::HashMap;

use futures::stream::Stream;
use mee_storage::json_kv_store::Store;
use std::pin::Pin;

pub type RuntimeContext = HashMap<String, Value>;
pub type ContextStream = futures::stream::BoxStream<'static, Result<RuntimeContext, String>>;
pub type JsonResultStream = Pin<Box<dyn Stream<Item = Result<Value, String>> + Send>>;

pub fn query_executor(store: Store) -> Arc<ExecutorList> {
    let pe = Arc::new(PathExecutorImpl::new());

    let ee = Arc::new(ExpressionExecutorImpl::new());

    let ce = Arc::new(ComparatorExecutorImpl::new());

    let be = Arc::new(BoolExpressionExecutorImpl::new());

    let ie = Arc::new(IteratorExecutorImpl::new(store.clone()));

    let qe = Arc::new(QueryExecutorImpl::new(store.clone()));

    

    Arc::new(ExecutorList {
        pe,
        ee,
        ce,
        be,
        ie,
        qe,
    })
}
