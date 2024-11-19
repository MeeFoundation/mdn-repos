use super::*;
use crate::error::*;
use crate::execution::support::*;
use std::sync::Arc;

pub struct ComparatorExecutorImpl {}

impl ComparatorExecutorImpl {
    pub fn new() -> Self {
        Self {}
    }
}

#[async_trait::async_trait]
impl ComparatorExecutor for ComparatorExecutorImpl {
    async fn check(
        &self,
        left_node: Arc<MeeNode<Expression>>,
        source_text: Arc<String>,
        node: Arc<MeeNode<Comparator>>,
        ctx: RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<bool> {
        match &node.value {
            Comparator::Eq(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                Ok(left == right)
            }
            Comparator::Ne(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                Ok(left != right)
            }
            Comparator::Lt(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text.clone())?
                        < right.cast_to_number(node, source_text.clone())?)
            }
            Comparator::Gt(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text.clone())?
                        > right.cast_to_number(node, source_text.clone())?)
            }
            Comparator::Ge(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text.clone())?
                        >= right.cast_to_number(node, source_text.clone())?)
            }
            Comparator::Le(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text.clone())?
                        <= right.cast_to_number(node, source_text.clone())?)
            }
            Comparator::Matches(expr) => {
                let expr = Arc::new(expr.clone());
                let left = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        left_node.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;
                let right = executor_list
                    .ee
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                    .await?;

                if left == Value::Null || right == Value::Null {
                    return Ok(false);
                } else {
                    let left = left.cast_to_string(left_node.clone(), source_text.clone())?;
                    let right = right.cast_to_string(node.clone(), source_text.clone())?;

                    let pattern = regex::Regex::new(&right).map_err(move |_| {
                        Error::runtime_error(
                            node.position.clone(),
                            source_text.as_str(),
                            "Invalid RegExp pattern".to_string(),
                        )
                    })?;

                    Ok(pattern.is_match(&left))
                }
            }
            Comparator::Exists => Ok(!executor_list
                .ee
                .execute(
                    source_text.clone(),
                    left_node.clone(),
                    ctx.clone(),
                    executor_list.clone(),
                )
                .await?
                .is_null()),
        }
    }
}
