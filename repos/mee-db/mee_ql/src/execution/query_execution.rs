use super::*;
use async_stream::{stream, try_stream};
use futures::pin_mut;
use futures::stream::StreamExt;
use mee_storage::json_kv_store::Store;
use std::sync::Arc;

pub struct QueryExecutorImpl {
    pub store: Store,
}

impl QueryExecutorImpl {
    pub fn new(store: Store) -> Self {
        Self { store }
    }
}

//Fix for case [user for a in [1,2,3]  for user in users]
impl QueryExecutorImpl {
    async fn get_user_id(
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
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
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let store = self.store.clone();
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                for (path, expr) in node.clone().value.updates.iter() {
                    let expr = Arc::new(expr.clone());
                    let v = executor_list
                        .ee
                        .execute(
                            source_text.clone(),
                            expr.clone(),
                            ctx.clone(),
                            executor_list.clone(),
                        )
                        .await?;
                    let user_id = QueryExecutorImpl::get_user_id(
                            source_text.clone(),
                        node.clone(),
                        &mut ctx,
                    )
                    .await?;
                    let path_str = path.value.to_store_path(&user_id);

                    store.set(path_str, v).await.map_err(|e| e.to_string())?;
                }
                yield ctx;
            }
        };
        Box::pin(stream)
    }

    async fn execute_deletes(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
        input_ctx: ContextStream,
    ) -> ContextStream {
        let store = self.store.clone();
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                match node.clone().value.deletes.value {
                    DeleteStmt::Paths(ref path_nodes) => {
                        for path_node in path_nodes.iter() {
                            let path_node = Arc::new(path_node.clone());
                            let user_id = QueryExecutorImpl::get_user_id(
                                source_text.clone(),
                                node.clone(),
                                &mut ctx,
                            )
                            .await?;
                            let path_str = path_node.value.to_store_path(&user_id);
                            store.delete(path_str).await.map_err(|e| e.to_string())?;
                        }
                    }
                    DeleteStmt::All => {
                        let user_id = QueryExecutorImpl::get_user_id(
                            source_text.clone(),
                            node.clone(),
                            &mut ctx,
                        )
                        .await?;
                        let user_item = &node.clone().value.main_iterator.value.item.value;
                        let path_str = Path {
                            root: user_item.clone(),
                            field: None,
                        }
                        .to_store_path(&user_id);

                        store.delete(path_str).await.map_err(|e| e.to_string())?;
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
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> JsonResultStream {
        let main_stream: ContextStream = Box::pin(input_ctx);
        let main_iterator = Arc::new(node.value.main_iterator.clone());

        let main_stream = executor_list
            .ie
            .stream(
                source_text.clone(),
                main_iterator.clone(),
                main_stream,
                executor_list.clone(),
            )
            .await;

        let mut new_stream = main_stream;

        for iterator in node.value.embedded_iterators.iter() {
            let iterator = Arc::new(iterator.clone());
            new_stream = executor_list
                .ie
                .stream(
                    source_text.clone(),
                    iterator.clone(),
                    new_stream,
                    executor_list.clone(),
                )
                .await;
        }

        new_stream = self
            .execute_updates(
                source_text.clone(),
                node.clone(),
                new_stream,
                executor_list.clone(),
            )
            .await;

        new_stream = self
            .execute_deletes(source_text.clone(), node.clone(), new_stream)
            .await;

        let stream = try_stream! {

            for await ctx in new_stream {
                let ctx = ctx?;

                if let Some(result) = &node.clone().value.result {
                    let result = Arc::new(result.clone());
                    let value = executor_list
                        .ee
                        .execute(
                            source_text.clone(),
                            result.clone(),
                            ctx.clone(),
                            executor_list.clone(),
                        )
                        .await?;
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
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<Query>>,
        ctx: RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Value, String> {
        let ctx = ctx.clone();
        let initial_stream = stream! {
            yield Ok(ctx);
        };
        let initial_stream = Box::pin(initial_stream);

        let mut stream = self
            .stream(
                source_text.clone(),
                node.clone(),
                initial_stream,
                executor_list,
            )
            .await;

        //TODO: handle errors
        match node.value.query_type.clone() {
            QueryType::FirstOrNull => stream.next().await.unwrap(),
            QueryType::All => {
                let arr = stream.collect::<Vec<_>>().await;
                Ok(Value::Array(arr.into_iter().map(|v| v.unwrap()).collect()))
            }
        }
    }
}
