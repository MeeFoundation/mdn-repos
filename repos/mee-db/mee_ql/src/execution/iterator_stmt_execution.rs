use super::*;
use crate::error::*;
use async_stream::try_stream;
use futures::pin_mut;
use futures::stream::{Stream, StreamExt};
use mee_storage::binary_kv_store::PATH_SEPARATOR;
use mee_storage::json_kv_store::RecordStream;
use mee_storage::json_kv_store::Store;
use serde_json::Value;
use std::sync::Arc;

use mee_storage::json_utils::ID_PREFIX;

fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
}

pub struct IteratorExecutorImpl {
    store: Store,
}

impl IteratorExecutorImpl {
    pub fn new(store: Store) -> Self {
        Self { store }
    }

    async fn users(store: Store) -> Result<RecordStream> {
        let res = store.stream().await?;
        Ok(res)
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

        let store = self.store.clone();
        let item_name = node.value.item.value.clone();
        let item_start = node.value.item.position.0;
        let item_end = node.value.item.position.1;

        let stream: ContextStream = match source_node.value.clone() {
            Expression::Array(exprs) => Box::pin(try_stream! {
                pin_mut!(input_ctx);
                let source_key = uuid::Uuid::now_v7().to_string();
                for await ctx in input_ctx {
                    let mut ctx = ctx?;
                    ctx.insert(source_key.clone(), LazyValue::Unevaluated(Arc::new(source_node.clone())));
                    for i in 0..exprs.len() {
                        let mut new_ctx = ctx.clone();
                        let item = MeeNode::new(Expression::Link(MeeNode::new(Path::new(format!("{source_key}.{i}")), item_start, item_end)), item_start, item_end);
                        new_ctx.insert(item_name.clone(), LazyValue::Unevaluated(Arc::new(item)));

                        yield new_ctx.clone();
                    }
                }
            }),
            Expression::Link(MeeNode {
                value: Path { ref root, field },
                ..
            }) => {
                if field.is_none() && root == "users" {
                    Box::pin(try_stream! {
                            pin_mut!(input_ctx);
                            for await ctx in input_ctx {
                                let ctx = ctx?;
                                let users = Self::users(store.clone()).await?;
                                pin_mut!(users);
                                for await user in users {
                                    let mut new_ctx = ctx.clone();
                                    let item = MeeNode::new(Expression::User(user), item_start, item_end);
                                    new_ctx.insert(item_name.clone(), LazyValue::Unevaluated(Arc::new(item)));

                                    yield new_ctx.clone();
                                }
                            }
                    })
                } else {
                    Box::pin(try_stream! {
                    pin_mut!(input_ctx);
                    let source_key = uuid::Uuid::now_v7().to_string();
                    for await ctx in input_ctx {
                        let mut ctx = ctx?;
                        ctx.insert(source_key.clone(), LazyValue::Unevaluated(Arc::new(source_node.clone())));

                        for i in 0..10 {
                            let mut new_ctx = ctx.clone();
                            let item = MeeNode::new(Expression::Link(MeeNode::new(Path::new(format!("{source_key}.{i}")), item_start, item_end)), item_start, item_end);
                                new_ctx.insert(item_name.clone(), LazyValue::Unevaluated(Arc::new(item)));

                                yield new_ctx.clone();
                            }
                        }
                    })
                }
            }
            _ => Box::pin(try_stream! {
                yield Err(Error::runtime_error(
                node.position.clone(),
                source_text.as_str(),
                    format!("Invalid source: {:?}", &source_node.value),
                ))?
            }),
        };

        stream.boxed()
    }
}
