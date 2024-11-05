use super::*;
use async_stream::try_stream;
use futures::pin_mut;
use futures::stream::{Stream, StreamExt};
use mee_storage::binary_kv_store::PATH_SEPARATOR;
use mee_storage::json_kv_store::Store;
use mee_storage::query_el::FieldFilter;
use serde_json::Value;
use std::sync::Arc;

use mee_storage::json_utils::ID_PREFIX;

fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
}

fn property_key(object_key: &str, property: &str) -> String {
    format!("{object_key}{PATH_SEPARATOR}{property}")
}

pub struct IteratorExecutorImpl {
    store: Store,
}

impl IteratorExecutorImpl {
    pub fn new(store: Store) -> Self {
        Self { store }
    }

    async fn users(store: Store) -> Result<impl Stream<Item = Value> + Send, String> {
        store
            .range("".to_string(), FieldFilter::All)
            .await
            .map_err(|e| e.to_string())
    }

    async fn apply_assignments(
        source_text: Arc<String>,
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
        assignments: &HashMap<MeeNode<String>, MeeNode<Expression>>,
    ) -> Result<(), String> {
        for (key, expr) in assignments.iter() {
            let expr = Arc::new(expr.clone());
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
        }
        Ok(())
    }

    async fn filter_value(
        filter_node: &Option<MeeNode<BoolExpression>>,
        source_text: Arc<String>,
        ctx: RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<bool, String> {
        if let Some(filter_node) = filter_node {
            if executor_list
                .be
                .execute(
                    source_text.clone(),
                    Arc::new(filter_node.clone()),
                    ctx,
                    executor_list.clone(),
                )
                .await?
                != Value::Bool(true)
            {
                return Ok(false);
            }
        }
        Ok(true)
    }
}

#[async_trait::async_trait]
impl IteratorExecutor for IteratorExecutorImpl {
    async fn stream(
        &self,
        source_text: Arc<String>,
        node: Arc<MeeNode<IteratorStmt>>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let source_node = node.value.source.clone();
        let filter_node = node.value.filter.clone();

        let store = self.store.clone();
        let item_name = node.value.item.value.clone();
        let limit = node.value.limit.unwrap_or(usize::MAX);
        let offset = node.value.offset.unwrap_or(0);

        let stream: ContextStream = match source_node.value.clone() {
            Source::ArraySource(exprs) => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                for await ctx in input_ctx {
                    let ctx = ctx?;
                    for item in exprs.iter() {
                        let item = Arc::new(item.clone());
                        let v = executor_list
                            .ee
                            .execute(
                                source_text.clone(),
                                item.clone(),
                                ctx.clone(),
                                executor_list.clone(),
                            )
                            .await?;
                        let mut new_ctx: RuntimeContext = ctx.clone();
                        new_ctx.insert(item_name.clone(), v);
                        IteratorExecutorImpl::apply_assignments(
                            source_text.clone(),
                            &mut new_ctx,
                            executor_list.clone(),
                            &node.value.assignments,
                        )
                        .await?;
                        if IteratorExecutorImpl::filter_value(&filter_node.clone(), source_text.clone(), new_ctx.clone(), executor_list.clone())
                            .await?
                        {
                            yield new_ctx.clone();
                        }
                    }
                }
            }),
            Source::PathSource(MeeNode {
                value: Path { ref root, field },
                ..
            }) if field.is_none() && *root == "users".to_string() => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                for await ctx in input_ctx {
                    let ctx = ctx?;

                    let users = Self::users(store.clone()).await?;
                    pin_mut!(users);
                    for await user in users {
                        let mut new_ctx: RuntimeContext = ctx.clone();
                        new_ctx.insert(
                            format!("{item_name}.$path"),
                            Value::String(object_key(&user.x_get_id().unwrap())),
                        );
                        new_ctx.insert(item_name.clone(), user);

                        IteratorExecutorImpl::apply_assignments(
                            source_text.clone(),
                            &mut new_ctx,
                            executor_list.clone(),
                            &node.value.assignments,
                        )
                        .await?;
                        if IteratorExecutorImpl::filter_value(&filter_node.clone(), source_text.clone(), new_ctx.clone(), executor_list.clone())
                            .await?
                        {
                            yield new_ctx.clone();
                        }
                    }
                }
            }),
            Source::PathSource(path_node) => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                for await ctx in input_ctx {
                  let ctx = ctx?;

                    let path_node = Arc::new(path_node.clone());
                    let path_value = executor_list
                            .pe
                        .execute(source_text.clone(), path_node.clone(), ctx.clone(), executor_list.clone())
                        .await?;
                    if !path_value.is_null() {
                        let prefix = path_node.value.root.clone();
                        let prefix = ctx
                            .get(&format!("{prefix}.$path"))
                            .and_then(|v| v.as_str().map(|s| format!("{s}{PATH_SEPARATOR}")))
                            .unwrap_or("".to_string());
                        let prefix = format!("{prefix}{}{PATH_SEPARATOR}", path_node.value.field.as_ref().unwrap_or(&"".to_string()));

                        for (i, item) in path_value
                            .cast_to_array(path_node.clone(), source_text.clone())?
                            .iter()
                            .enumerate()
                        {
                            let mut new_ctx: RuntimeContext = ctx.clone();

                            new_ctx.insert(
                                format!("{item_name}.$path"),
                                Value::String(format!("{prefix}{i}")),
                            );

                            new_ctx.insert(item_name.clone(), item.clone());
                            IteratorExecutorImpl::apply_assignments(
                                source_text.clone(),
                                &mut new_ctx,
                                executor_list.clone(),
                                &node.value.assignments,
                            )
                            .await?;
                            if IteratorExecutorImpl::filter_value(&filter_node.clone(), source_text.clone(), new_ctx.clone(), executor_list.clone())
                                .await?
                            {
                                yield new_ctx.clone();
                            }
                        }
                    }
                }
            }),
        };

        stream.skip(offset).take(limit).boxed()
    }
}
