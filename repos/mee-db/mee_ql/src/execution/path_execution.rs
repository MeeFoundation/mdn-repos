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
        ctx: RuntimeContext,
        _: Arc<ExecutorList>,
    ) -> Result<Value> {
        let var = ctx.get(&node.value.root).ok_or(Error::runtime_error(
            node.position.clone(),
            source_text.as_str(),
            format!("Variable {:?} is not found", node.value.root),
        ))?;

        if let Some(field) = &node.value.field {
            Ok(var.x_get_property(field).cloned().unwrap_or(Value::Null))
        } else {
            Ok(var.clone())
        }
    }
}
