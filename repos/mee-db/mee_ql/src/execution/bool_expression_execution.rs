use super::*;
use crate::error::*;
use crate::execution::support::*;
use std::sync::Arc;

pub struct BoolExpressionExecutorImpl;

impl BoolExpressionExecutorImpl {
    pub fn new() -> Self {
        Self {}
    }
}

#[async_trait::async_trait]
impl Executor<BoolExpression, Value> for BoolExpressionExecutorImpl {
    async fn execute(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<BoolExpression>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Value> {
        let be = executor_list.be.clone();
        let ce = executor_list.ce.clone();
        let ee = executor_list.ee.clone();

        match &node.value {
            BoolExpression::And(exprs) => {
                for expr in exprs {
                    let expr = Arc::new(expr.clone());
                    if !be
                        .clone()
                        .execute(
                            source_text.clone(),
                            expr.clone(),
                            ctx,
                            executor_list.clone(),
                        )
                        .await?
                        .cast_to_bool(expr.clone(), source_text.clone())?
                    {
                        return Ok(Value::Bool(false));
                    }
                }
                Ok(Value::Bool(true))
            }
            BoolExpression::Or(exprs) => {
                for expr in exprs {
                    let expr = Arc::new(expr.clone());
                    if be
                        .clone()
                        .execute(
                            source_text.clone(),
                            expr.clone(),
                            ctx,
                            executor_list.clone(),
                        )
                        .await?
                        .cast_to_bool(expr.clone(), source_text.clone())?
                    {
                        return Ok(Value::Bool(true));
                    }
                }
                Ok(Value::Bool(false))
            }
            BoolExpression::Not(ref expr) => {
                let expr = Arc::new(*expr.clone());
                if be
                    .clone()
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await?
                    .cast_to_bool(expr.clone(), source_text.clone())?
                {
                    Ok(Value::Bool(false))
                } else {
                    Ok(Value::Bool(true))
                }
            }
            BoolExpression::Comparison { val, comparator } => {
                let val = Arc::new(val.clone());
                let comparator = Arc::new(comparator.clone());
                let left = ce
                    .clone()
                    .check(
                        val.clone(),
                        source_text.clone(),
                        comparator.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await?;
                Ok(Value::Bool(left))
            }
            BoolExpression::Expression(path) => {
                let path = Arc::new(path.clone());
                let left = ee
                    .clone()
                    .execute(
                        source_text.clone(),
                        path.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await?;
                Ok(Value::Bool(left == Value::Bool(true)))
            }
            BoolExpression::True => Ok(Value::Bool(true)),
            BoolExpression::False => Ok(Value::Bool(false)),
        }
    }
}
