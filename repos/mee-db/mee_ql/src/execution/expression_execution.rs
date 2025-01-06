use mee_storage::Record;

use super::*;
use crate::error::*;
use std::sync::Arc;

pub struct ExpressionExecutorImpl;

impl ExpressionExecutorImpl {
    pub fn new() -> Self {
        Self {}
    }
}

#[async_trait::async_trait]
impl Executor<Expression, Value> for ExpressionExecutorImpl {
    async fn execute(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Expression>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Value> {
        match &node.value {
            Expression::Query(query) => {
                let query = Arc::new(query.as_ref().clone());
                executor_list
                    .qe
                    .clone()
                    .execute(
                        source_text.clone(),
                        query.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await
            }
            Expression::BoolExpression(expr) => {
                let expr = Arc::new(expr.as_ref().clone());
                executor_list
                    .be
                    .clone()
                    .execute(
                        source_text.clone(),
                        expr.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await
            }
            Expression::Link(path) => {
                let path = Arc::new(path.clone());
                
                executor_list
                    .pe
                    .clone()
                    .execute(
                        source_text.clone(),
                        path.clone(),
                        ctx,
                        executor_list.clone(),
                    )
                    .await
            }
            Expression::Object(map) => {
                let mut values = Map::new();
                for (k, v) in map {
                    let v = Arc::new(v.clone());
                    let v = executor_list
                        .ee
                        .clone()
                        .execute(source_text.clone(), v.clone(), ctx, executor_list.clone())
                        .await?;
                    values.insert(k.clone(), v);
                }
                Ok(Value::Object(values))
            }
            Expression::Array(arr) => {
                let mut values = Vec::new();
                for item in arr {
                    let item = Arc::new(item.clone());
                    values.push(
                        self.execute(
                            source_text.clone(),
                            item.clone(),
                            ctx,
                            executor_list.clone(),
                        )
                        .await?,
                    );
                }
                Ok(Value::Array(values))
            }
            Expression::Bool(val) => Ok(Value::Bool(*val)),
            Expression::String(val) => Ok(Value::String(val.clone())),
            Expression::Number(val) => {
                let res = Number::from_f64(*val).ok_or(Error::runtime_error(
                    node.position.clone(),
                    source_text.as_str(),
                    "Invalid number".to_string(),
                ))?;
                Ok(Value::Number(res))
            }
            Expression::Null => Ok(Value::Null),
            Expression::User(user) => Ok(user.snapshot(None).await?),
        }
    }
}
