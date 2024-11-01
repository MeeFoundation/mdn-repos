use super::*;
use crate::execution::support::*;
use std::sync::Arc;

pub struct ComparatorExecutorImpl {
    pub ee: Option<Arc<dyn Executor<Expression, Value> + Send + Sync>>,
}

#[async_trait::async_trait]
impl ComparatorExecutor for ComparatorExecutorImpl {
    async fn check(
        &'static self,
        left_node: &'static MeeNode<Expression>,
        source_text: &'static str,
        node: &'static MeeNode<Comparator>,
        ctx: &mut RuntimeContext,
    ) -> Result<bool, String> {
        match &node.value {
            Comparator::Eq(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;
                Ok(left == right)
            }
            Comparator::Ne(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;
                Ok(left != right)
            }
            Comparator::Lt(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text)?
                        < right.cast_to_number(node, source_text)?)
            }
            Comparator::Gt(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text)?
                        > right.cast_to_number(node, source_text)?)
            }
            Comparator::Ge(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text)?
                        >= right.cast_to_number(node, source_text)?)
            }
            Comparator::Le(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;

                Ok(left != Value::Null
                    && right != Value::Null
                    && left.cast_to_number(left_node, source_text)?
                        <= right.cast_to_number(node, source_text)?)
            }
            Comparator::Matches(expr) => {
                let left = self.ee.execute(source_text, left_node, ctx).await?;
                let right = self.ee.execute(source_text, expr, ctx).await?;

                if left == Value::Null || right == Value::Null {
                    return Ok(false);
                } else {
                    let left = left.cast_to_string(left_node, source_text)?;
                    let right = right.cast_to_string(node, source_text)?;

                    let pattern = regex::Regex::new(&right).map_err(|_| {
                    let error_place = format!("<!{}!>", &source_text[node.start..node.end]);
                    format!(
                        "Runtime error at position ({}, {}) (wrapped in '<!_!>') {}{}{} -  Invalid RegExp pattern '{}'",
                        node.start,
                        node.end,
                        &source_text[..node.start],
                        error_place,
                        &source_text[node.end..],
                        &right
                        )
                    })?;

                    Ok(pattern.is_match(&left))
                }
            }
            Comparator::Exists => Ok(!self
                .ee
                .execute(source_text, left_node, ctx)
                .await?
                .is_null()),
        }
    }
}
