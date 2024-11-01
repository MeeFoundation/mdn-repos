use super::*;
use async_stream::{stream, try_stream};
use futures::pin_mut;
use futures::stream::{Stream, StreamExt};
use mee_storage::json_kv_store::{JsonStream, Store};
use mee_storage::query_el::FieldFilter;
use std::result::Result as StdResult;
use std::sync::Arc;

pub struct QueryExecutorImpl {
    pub ee: Arc<dyn Executor<Expression, Value> + Send + Sync>,
    pub be: Arc<dyn Executor<BoolExpression, Value> + Send + Sync>,
    pub ie: Arc<dyn IteratorExecutor + Send + Sync>,
    pub store: Store,
}

//Fix for case [user for a in [1,2,3]  for user in users]
impl QueryExecutorImpl {
    async fn get_user_id(
        &'static self,
        source_text: &str,
        node: &MeeNode<Query>,
        ctx: &mut RuntimeContext,
    ) -> Result<String, String> {
        let user_item = &node.value.main_iterator.value.item.value;
        ctx.get(user_item)
            .and_then(|v| v.x_get_id())
            .ok_or({
                //only for testing
                // let error_place = format!("\x1b[31m{}\x1b[0m", &source_text[node.start..node.end]);
                let error_place = format!("<!{}!>", &source_text[node.start..node.end]);
                format!(
                    "Runtime error at position ({}, {}) (wrapped in '<!_!>') {}{}{} -  User id is not found in the context",
                    node.start,
                    node.end,
                    &source_text[..node.start],
                    error_place,
                    &source_text[node.end..],
                )
            })
            .map(|id| id.to_string())
    }

    async fn execute_updates(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Query>,
        input_ctx: ContextStream,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                for (path, expr) in node.value.updates.iter() {
                    let v = self.ee.execute(source_text, expr, &mut ctx).await?;
                    let user_id = self.get_user_id(source_text, node, &mut ctx).await?;
                    let path_str = path.value.to_store_path(&user_id);

                    self.store.set(path_str, v).await.map_err(|e| e.to_string())?;
                }
                yield ctx;
            }
        };
        Box::pin(stream)
    }

    async fn execute_deletes(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Query>,
        input_ctx: ContextStream,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                match &node.value.deletes.value {
                    DeleteStmt::Paths(path_nodes) => {
                        for path_node in path_nodes.iter() {
                            let user_id = self.get_user_id(source_text, node, &mut ctx).await?;
                            let path_str = path_node.value.to_store_path(&user_id);
                            self.store.delete(path_str).await.map_err(|e| e.to_string())?;
                        }
                    }
                    DeleteStmt::All => {
                        let user_id = self.get_user_id(source_text, node, &mut ctx).await?;
                        let user_item = &node.value.main_iterator.value.item.value;
                        let path_str = Path {
                            root: user_item.clone(),
                            field: None,
                        }
                        .to_store_path(&user_id);

                        self.store.delete(path_str).await.map_err(|e| e.to_string())?;
                    }
                    _ => {}
                }
                yield ctx.clone();
            }
        };
        Box::pin(stream)
    }
}

#[async_trait::async_trait]
impl QueryExecutor for QueryExecutorImpl {
    async fn stream(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Query>,
        input_ctx: ContextStream,
    ) -> JsonResultStream {
        let mut main_stream: ContextStream = Box::pin(input_ctx);

        main_stream = self
            .ie
            .stream(source_text, &node.value.main_iterator, main_stream)
            .await;

        let mut new_stream = main_stream;

        for iterator in node.value.embedded_iterators.iter() {
            new_stream = self.ie.stream(source_text, iterator, new_stream).await;
        }

        new_stream = self.execute_updates(source_text, node, new_stream).await;

        new_stream = self.execute_deletes(source_text, node, new_stream).await;

        let stream = try_stream! {

            for await ctx in new_stream {
                let mut ctx = ctx?;
                if let Some(result) = &node.value.result {
                    let value = self.ee.execute(source_text, result, &mut ctx).await?;
                    yield value;
                } else {
                    yield Value::Null;
                }
            }
        };

        Box::pin(stream)
    }
}

#[async_trait::async_trait]
impl Executor<Query, Value> for QueryExecutorImpl {
    async fn execute(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Query>,
        ctx: &mut RuntimeContext,
    ) -> Result<Value, String> {
        let ctx = ctx.clone();
        let initial_stream = stream! {
            yield Ok(ctx);
        };
        let initial_stream = Box::pin(initial_stream);

        let mut stream = self.stream(source_text, node, initial_stream).await;

        //TODO: handle errors
        match node.value.query_type {
            QueryType::FirstOrNull => stream.next().await.unwrap(),
            QueryType::All => {
                let arr = stream.collect::<Vec<_>>().await;
                Ok(Value::Array(arr.into_iter().map(|v| v.unwrap()).collect()))
            }
        }
    }
}
