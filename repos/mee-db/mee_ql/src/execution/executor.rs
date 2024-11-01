use super::*;

use std::sync::Arc;

#[async_trait::async_trait]
pub trait Executor<T, U> {
    async fn execute(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<T>,
        ctx: &mut RuntimeContext,
    ) -> Result<U, String>;
}

#[async_trait::async_trait]
pub trait ComparatorExecutor {
    async fn check(
        &'static self,
        left: &'static MeeNode<Expression>,
        source_text: &'static str,
        node: &'static MeeNode<Comparator>,
        ctx: &mut RuntimeContext,
    ) -> Result<bool, String>;
}
#[async_trait::async_trait]
pub trait IteratorExecutor {
    async fn stream(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<IteratorStmt>,
        ctx: ContextStream,
    ) -> ContextStream;
}

#[async_trait::async_trait]
pub trait QueryExecutor: Executor<Query, Value> {
    async fn stream(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Query>,
        input_ctx: ContextStream,
    ) -> JsonResultStream;
}

#[allow(unused)]
#[allow(unused)]
pub struct ExecutorList {
    pub query_stream: Arc<dyn Executor<Query, JsonResultStream> + Send + Sync>,
    pub query_executor: Arc<dyn Executor<Query, Value> + Send + Sync>,
    pub iterator_stream: Arc<dyn IteratorExecutor + Send + Sync>,
    pub delete_executor: Arc<dyn Executor<DeleteStmt, ()> + Send + Sync>,
    pub expression_executor: Arc<dyn Executor<Expression, Value> + Send + Sync>,
    pub bool_expression_executor: Arc<dyn Executor<BoolExpression, Value> + Send + Sync>,
    pub comparator_executor: Arc<dyn ComparatorExecutor + Send + Sync>,
    pub path_executor: Arc<dyn Executor<Path, Value> + Send + Sync>,
}
