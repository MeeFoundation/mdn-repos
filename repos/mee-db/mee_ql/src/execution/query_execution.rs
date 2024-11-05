use super::*;
use async_stream::{stream, try_stream};
use futures::pin_mut;
use futures::stream::StreamExt;
use mee_storage::binary_kv_store::PATH_SEPARATOR;
use mee_storage::json_kv_store::Store;
use std::collections::HashSet;
use std::sync::{Arc, Mutex};

pub struct QueryExecutorImpl {
    pub store: Store,
}

impl QueryExecutorImpl {
    pub fn new(store: Store) -> Self {
        Self { store }
    }
}

fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
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
        updates: Arc<Mutex<HashMap<String, Value>>>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let  ctx = ctx?;
                for (path, expr) in node.clone().value.updates.iter() {
                    dbg!(&path);
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

                let prefix = ctx
                            .get(&format!("{}.$path", path.value.root))
                            .and_then(|v| v.as_str().map(|s| format!("{s}{PATH_SEPARATOR}")))
                            .unwrap_or("".to_string());
                    let prefix = format!("{prefix}{}", path.value.field.as_ref().unwrap_or(&"".to_string()));

                    updates.lock().unwrap().insert(prefix, v);
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
        deletes: Arc<Mutex<HashSet<String>>>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                match node.clone().value.deletes.value {
                    DeleteStmt::Paths(ref path_nodes) => {
                        for path_node in path_nodes.iter() {
                            let path_node = Arc::new(path_node.clone());

                        let prefix = ctx
                            .get(&format!("{}.$path", path_node.value.root))
                            .and_then(|v| v.as_str().map(|s| format!("{s}{PATH_SEPARATOR}")))
                            .unwrap_or("".to_string());
                        let prefix = format!("{prefix}{}", path_node.value.field.as_ref().unwrap_or(&"".to_string()));

                        deletes.lock().unwrap().insert(prefix);
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

                        deletes.lock().unwrap().insert(path_str);
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
        updates: Arc<Mutex<HashMap<String, Value>>>,
        deletes: Arc<Mutex<HashSet<String>>>,
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
                updates.clone(),
            )
            .await;

        new_stream = self
            .execute_deletes(
                source_text.clone(),
                node.clone(),
                new_stream,
                deletes.clone(),
            )
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

        let updates = Arc::new(Mutex::new(HashMap::new()));
        let deletes = Arc::new(Mutex::new(HashSet::new()));

        let mut stream = self
            .stream(
                source_text.clone(),
                node.clone(),
                initial_stream,
                executor_list,
                updates.clone(),
                deletes.clone(),
            )
            .await;

        //TODO: handle errors
        let result = match node.value.query_type.clone() {
            QueryType::FirstOrNull => stream.next().await.unwrap(),
            QueryType::All => {
                let arr = stream.collect::<Vec<_>>().await;
                Ok(Value::Array(arr.into_iter().map(|v| v.unwrap()).collect()))
            }
        };

        let updates = updates
            .lock()
            .unwrap()
            .clone()
            .into_iter()
            .collect::<HashMap<_, _>>();
        let deletes = deletes
            .lock()
            .unwrap()
            .clone()
            .into_iter()
            .collect::<HashSet<_>>();

        for (path, value) in updates.into_iter() {
            let path = path.clone();
            let value = value.clone();
            self.store
                .clone()
                .set(path, value)
                .await
                .map_err(|e| e.to_string())?;
        }

        for path in deletes.into_iter() {
            let path = path.clone();

            self.store.delete(path).await.map_err(|e| e.to_string())?;
        }

        result
    }
}
