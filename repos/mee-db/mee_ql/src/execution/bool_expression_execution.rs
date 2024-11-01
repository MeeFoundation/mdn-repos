use super::*;
use crate::execution::support::*;
use std::sync::Arc;
pub struct BoolExpressionExecutorImpl {
    _ee: Option<Arc<dyn Executor<Expression, Value> + Send + Sync>>,
    _ce: Option<Arc<dyn ComparatorExecutor + Send + Sync>>,
}

impl BoolExpressionExecutorImpl {
    pub fn new(
        ee: Option<Arc<dyn Executor<Expression, Value> + Send + Sync>>,
        ce: Option<Arc<dyn ComparatorExecutor + Send + Sync>>,
    ) -> Self {
        Self { _ee: ee, _ce: ce }
    }

    pub fn set_ee(&mut self, ee: Arc<dyn Executor<Expression, Value> + Send + Sync>) {
        self._ee = Some(ee);
    }

    pub fn set_ce(&mut self, ce: Arc<dyn ComparatorExecutor + Send + Sync>) {
        self._ce = Some(ce);
    }

    fn ee(&self) -> &Arc<dyn Executor<Expression, Value> + Send + Sync> {
        self._ee.as_ref().unwrap()
    }

    fn ce(&self) -> &Arc<dyn ComparatorExecutor + Send + Sync> {
        self._ce.as_ref().unwrap()
    }
}

#[async_trait::async_trait]
impl Executor<BoolExpression, Value> for BoolExpressionExecutorImpl {
    async fn execute(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<BoolExpression>,
        ctx: &mut RuntimeContext,
    ) -> Result<Value, String> {
        match &node.value {
            BoolExpression::And(exprs) => {
                for expr in exprs {
                    if !self
                        .execute(source_text, &expr, ctx)
                        .await?
                        .cast_to_bool(&expr, source_text)?
                    {
                        return Ok(Value::Bool(false));
                    }
                }
                Ok(Value::Bool(true))
            }
            BoolExpression::Or(exprs) => {
                for expr in exprs {
                    if self
                        .execute(source_text, &expr, ctx)
                        .await?
                        .cast_to_bool(&expr, source_text)?
                    {
                        return Ok(Value::Bool(true));
                    }
                }
                Ok(Value::Bool(false))
            }
            BoolExpression::Not(expr) => {
                if self
                    .execute(source_text, &expr, ctx)
                    .await?
                    .cast_to_bool(&expr, source_text)?
                {
                    Ok(Value::Bool(false))
                } else {
                    Ok(Value::Bool(true))
                }
            }
            BoolExpression::Comparison { val, comparator } => {
                let left = self.ce().check(&val, source_text, comparator, ctx).await?;
                Ok(Value::Bool(left))
            }
            BoolExpression::Expression(path) => {
                let left = self.ee().execute(source_text, path, ctx).await?;
                Ok(Value::Bool(left == Value::Bool(true)))
            }
            BoolExpression::True => Ok(Value::Bool(true)),
            BoolExpression::False => Ok(Value::Bool(false)),
        }
    }
}
