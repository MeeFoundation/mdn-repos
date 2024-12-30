use mee_storage::Record;

use super::*;
use crate::error::*;
pub struct PathExecutorImpl;
impl PathExecutorImpl {
    pub fn new() -> Self {
        Self {}
    }
}

#[async_trait::async_trait]
impl Executor<Path, Value> for PathExecutorImpl {
    async fn execute(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Path>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Value> {
        let var = ctx.get_mut(&node.value.root).ok_or(Error::runtime_error(
            node.position.clone(),
            source_text.as_str(),
            format!("Variable {:?} is not found", node.value.root),
        ))?;

        let var = match var {
            LazyValue::Unevaluated(expr) => match &expr.value {
                Expression::Link(path) => {
                    let new_path = path.map(|p| p.combine(node.value.clone()));
                    let res = executor_list
                        .pe
                        .clone()
                        .execute(source_text, Arc::new(new_path), ctx, executor_list.clone())
                        .await?;
                    return Ok(res);
                }
                Expression::User(record) => {
                    if let Some(ref prop) = node.value.field {
                        let res = record.get(prop).await?.unwrap_or(Value::Null);
                        res
                    } else {
                        let val = record.snapshot(None).await?;
                        val
                    }
                }
                _ => {
                    let value = executor_list
                        .ee
                        .execute(source_text, expr.clone(), ctx, executor_list.clone())
                        .await?;
                    ctx.insert(node.value.root.clone(), LazyValue::Evaluated(value.clone()));
                    value
                }
            },
            LazyValue::Evaluated(value) => value.clone(),
        };

        if let Some(field) = &node.value.field {
            Ok(var.x_get_property(field).cloned().unwrap_or(Value::Null))
        } else {
            Ok(var.clone())
        }
    }
}

#[async_trait::async_trait]
impl PathExecutor for PathExecutorImpl {
    async fn size(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Path>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Option<usize>> {
        let var = ctx.get_mut(&node.value.root).ok_or(Error::runtime_error(
            node.position.clone(),
            source_text.as_str(),
            format!("Variable {:?} is not found", node.value.root),
        ))?;

        match var {
            LazyValue::Unevaluated(expr) => match &expr.value {
                Expression::Link(path) => {
                    let new_path = path.map(|p| p.combine(node.value.clone()));
                    let res = executor_list
                        .pe
                        .clone()
                        .size(source_text, Arc::new(new_path), ctx, executor_list.clone())
                        .await;
                    res
                }
                Expression::User(record) => {
                    if let Some(ref prop) = node.value.field {
                        let size = record.property_size(prop).await?;
                        Ok(size)
                    } else {
                        Ok(None)
                    }
                }
                _ => Ok(None),
            },
            LazyValue::Evaluated(value) => match value {
                Value::Array(arr) => Ok(Some(arr.len())),
                _ => Ok(None),
            },
        }
    }

    async fn resolve_path(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Path>>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Arc<MeeNode<Path>>> {
        let var = ctx.get_mut(&node.value.root).ok_or(Error::runtime_error(
            node.position.clone(),
            source_text.as_str(),
            format!("Variable {:?} is not found", node.value.root),
        ))?;
        match var {
            LazyValue::Unevaluated(expr) => match &expr.value {
                Expression::Link(path) => {
                    let new_path = path.map(|p| p.combine(node.value.clone()));
                    let res = executor_list
                        .pe
                        .clone()
                        .resolve_path(source_text, Arc::new(new_path), ctx, executor_list.clone())
                        .await;
                    res
                }
                _ => Ok(node.clone()),
            },
            _ => Ok(node.clone()),
        }
    }
}
