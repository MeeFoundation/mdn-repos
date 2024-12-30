use super::*;
use crate::error::*;
use std::sync::Arc;

#[async_trait::async_trait]
pub trait Executor<T, U> {
    async fn execute(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<T>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<U>;
}

#[async_trait::async_trait]
pub trait ComparatorExecutor {
    async fn check(
        &self,
        left: Arc<MeeNode<Expression>>,
        source_text: Arc<String>,
        node: Arc<MeeNode<Comparator>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<bool>;
}
#[async_trait::async_trait]
pub trait IteratorExecutor {
    async fn stream(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<IteratorStmt>>,
        ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream;
}

#[async_trait::async_trait]
pub trait QueryExecutor: Executor<Query, Value> {
    async fn stream(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> JsonResultStream;
}

#[async_trait::async_trait]
pub trait PathExecutor: Executor<Path, Value> {
    async fn size(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Path>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Option<usize>>;

    async fn resolve_path(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Path>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Arc<MeeNode<Path>>>;
}

pub struct ExecutorList {
    pub ee: Arc<dyn Executor<Expression, Value> + Send + Sync>,
    pub ce: Arc<dyn ComparatorExecutor + Send + Sync>,
    pub be: Arc<dyn Executor<BoolExpression, Value> + Send + Sync>,
    pub ie: Arc<dyn IteratorExecutor + Send + Sync>,
    pub qe: Arc<dyn QueryExecutor + Send + Sync>,
    pub pe: Arc<dyn PathExecutor + Send + Sync>,
}
