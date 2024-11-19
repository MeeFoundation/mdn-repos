use super::*;
use crate::error::*;
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

impl QueryExecutorImpl {
    async fn execute_update(
        &self,
        source_text: Arc<String>,
        pair: (Arc<MeeNode<Path>>, Arc<MeeNode<Expression>>),
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
        updates: Arc<Mutex<HashMap<String, Value>>>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let ctx = ctx?;
                let (path, expr) = pair.clone();

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

                yield ctx;
            }

        };
        Box::pin(stream)
    }

    async fn execute_delete(
        &self,
        _source_text: Arc<String>,
        path: Arc<MeeNode<Path>>,
        input_ctx: ContextStream,
        deletes: Arc<Mutex<HashSet<String>>>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let  ctx = ctx?;

                let path_node = Arc::new(path.clone());

                        let prefix = ctx
                            .get(&format!("{}.$path", path_node.value.root))
                            .and_then(|v| v.as_str().map(|s| format!("{s}{PATH_SEPARATOR}")))
                            .unwrap_or("".to_string());
                        let prefix = format!("{prefix}{}", path_node.value.field.as_ref().unwrap_or(&"".to_string()));

                        deletes.lock().unwrap().insert(prefix);
                yield ctx.clone();
            }
        };
        Box::pin(stream)
    }

    async fn execute_assignment(
        &self,
        source_text: Arc<String>,
        pair: (Arc<MeeNode<String>>, Arc<MeeNode<Expression>>),
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;
                let (key, expr) = pair.clone();
                let value = executor_list
            .ee
            .execute(
                source_text.clone(),
                expr.clone(),
                ctx.clone(),
                executor_list.clone(),
            )
            .await?;
        ctx.insert(key.value.clone(), value);
        yield ctx.clone();
            }
        };
        Box::pin(stream)
    }

    async fn execute_filter(
        &self,
        filter_node: Option<MeeNode<BoolExpression>>,
        source_text: Arc<String>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let ctx = ctx?;

                if let Some(ref filter_node) = filter_node {
                    if executor_list
                    .be
                    .execute(
                        source_text.clone(),
                        Arc::new(filter_node.clone()),
                        ctx.clone(),
                        executor_list.clone(),
                    )
                .await?
                == Value::Bool(true)
            {
                yield ctx.clone();
            }
            }
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

        for statement in node.value.statements.iter() {
            match statement.value {
                Statement::Iterator(ref iterator) => {
                    new_stream = executor_list
                        .ie
                        .stream(
                            source_text.clone(),
                            Arc::new(MeeNode::new(
                                iterator.clone(),
                                statement.position.0,
                                statement.position.1,
                            ))
                            .clone(),
                            new_stream,
                            executor_list.clone(),
                        )
                        .await;
                }
                Statement::Assignment(ref assignment) => {
                    new_stream = self
                        .execute_assignment(
                            source_text.clone(),
                            (
                                Arc::new(assignment.0.clone()),
                                Arc::new(assignment.1.clone()),
                            ),
                            new_stream,
                            executor_list.clone(),
                        )
                        .await;
                }
                Statement::Update(ref update) => {
                    new_stream = self
                        .execute_update(
                            source_text.clone(),
                            (Arc::new(update.0.clone()), Arc::new(update.1.clone())),
                            new_stream,
                            executor_list.clone(),
                            updates.clone(),
                        )
                        .await;
                }
                Statement::Delete(ref delete) => {
                    new_stream = self
                        .execute_delete(
                            source_text.clone(),
                            Arc::new(delete.clone()),
                            new_stream,
                            deletes.clone(),
                        )
                        .await;
                }
                Statement::Filter(ref filter) => {
                    new_stream = self
                        .execute_filter(
                            Some(filter.clone()),
                            source_text.clone(),
                            new_stream,
                            executor_list.clone(),
                        )
                        .await;
                }
                Statement::Offset(ref offset) => {
                    new_stream = Box::pin(new_stream.skip(*offset));
                }
                Statement::Limit(ref limit) => {
                    new_stream = Box::pin(new_stream.take(*limit));
                }
            }
        }

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
    ) -> Result<Value> {
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
            self.store.clone().set(path, value).await?;
        }

        for path in deletes.into_iter() {
            let path = path.clone();

            self.store.delete(path).await?;
        }

        result
    }
}
