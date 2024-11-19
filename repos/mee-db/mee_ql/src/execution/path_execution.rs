use super::*;
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
    ) -> Result<Value, String> {
        let var = ctx.get(&node.value.root).ok_or({
                //only for testing
    // let error_place = format!("\x1b[31m{}\x1b[0m", &source_text[node.start..node.end]);
    let error_place = format!("<!{}!>", &source_text[node.start..node.end]);
    format!(
        "Runtime error at position ({}, {}) (wrapped in '<!_!>') {}{}{} -  Variable {:?} is not found",
                node.start,
                node.end,
                &source_text[..node.start],
                error_place,
                    &source_text[node.end..],
                    node.value.root
                )
            })?;

        if let Some(field) = &node.value.field {
            Ok(var.x_get_property(field).cloned().unwrap_or(Value::Null))
        } else {
            Ok(var.clone())
        }
    }
}
