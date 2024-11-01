use super::*;
use async_stream::try_stream;
use futures::pin_mut;
use futures::stream::{Stream, StreamExt};
use mee_storage::json_kv_store::Store;
use mee_storage::query_el::FieldFilter;
use serde_json::Value;
use std::sync::Arc;

pub struct IteratorExecutorImpl {
    pub ee: Arc<dyn Executor<Expression, Value> + Send + Sync>,
    pub pe: Arc<dyn Executor<Path, Value> + Send + Sync>,
    pub ce: Arc<dyn Executor<BoolExpression, Value> + Send + Sync>,
    pub store: Store,
}

impl IteratorExecutorImpl {
    async fn users(store: Store) -> Result<impl Stream<Item = Value> + Send, String> {
        store
            .range("".to_string(), FieldFilter::All)
            .await
            .map_err(|e| e.to_string())
    }

    async fn filter_value(
        &'static self,
        filter_node: &'static Option<MeeNode<BoolExpression>>,
        source_text: &'static str,
        ctx: &mut RuntimeContext,
    ) -> Result<bool, String> {
        if let Some(filter_node) = filter_node {
            if self.ce.execute(source_text, &filter_node, ctx).await? != Value::Bool(true) {
                return Ok(false);
            }
        }
        Ok(true)
    }
}

#[async_trait::async_trait]
impl IteratorExecutor for IteratorExecutorImpl {
    async fn stream(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<IteratorStmt>,
        input_ctx: ContextStream,
    ) -> ContextStream {
        let source_node = &node.value.source;
        let filter_node = &node.value.filter;
        let item_name = node.value.item.value.clone();
        let limit = node.value.limit.unwrap_or(usize::MAX);
        let offset = node.value.offset.unwrap_or(0);

        let stream: ContextStream = match &source_node.value {
            Source::ArraySource(exprs) => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                for await ctx in input_ctx {
                    let mut ctx = ctx?;
                    for item in exprs.iter() {
                        let v = self.ee.execute(source_text, item, &mut ctx).await?;
                        let mut new_ctx = ctx.clone();
                        new_ctx.insert(item_name.clone(), v);
                        if self
                            .filter_value(filter_node, source_text, &mut new_ctx)
                            .await?
                        {
                            yield new_ctx;
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
                    let users = Self::users(self.store.clone()).await?;
                    pin_mut!(users);
                    for await user in users {
                        let mut new_ctx = ctx.clone();
                        new_ctx.insert(item_name.clone(), user);
                        if self
                            .filter_value(filter_node, source_text, &mut new_ctx)
                            .await?
                        {
                            yield new_ctx;
                        }
                    }
                }
            }),
            Source::PathSource(path_node) => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                for await ctx in input_ctx {
                    let mut ctx = ctx?;
                    let path_value = self.pe.execute(source_text, path_node,  &mut ctx).await?;
                    if !path_value.is_null() {
                        for item in path_value.cast_to_array(path_node, source_text)? {
                            let mut new_ctx = ctx.clone();
                            new_ctx.insert(item_name.clone(), item);
                            if self
                            .filter_value(filter_node, source_text, &mut new_ctx)
                            .await?
                        {
                            yield new_ctx;
                        }
                        }
                    }
                }
            }),
        };

        stream.skip(offset).take(limit).boxed()
    }
}
