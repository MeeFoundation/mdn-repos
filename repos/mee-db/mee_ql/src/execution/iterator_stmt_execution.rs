use super::*;
use async_stream::try_stream;
use futures::pin_mut;
use futures::stream::Stream;
use mee_storage::json_kv_store::Store;
use mee_storage::query_el::FieldFilter;
use serde_json::Value;
use std::collections::HashMap;
use std::pin::Pin;

pub type Context = HashMap<String, Value>;
pub type ContextStream = Pin<Box<dyn Stream<Item = Result<Context, String>> + Send>>;
pub type JsonResultStream = Pin<Box<dyn Stream<Item = Result<Value, String>> + Send>>;

impl IteratorStmt {
    pub async fn execute(&'static self, store: Store, input_ctx: ContextStream) -> ContextStream {
        match self.source.clone() {
            Source::ArraySource(exprs) => {
                let stream = try_stream! {
                    pin_mut!(input_ctx);
                    for await ctx in input_ctx {
                        let ctx = ctx?;
                        for item in exprs.iter() {
                            let v = item.value(&ctx)?;
                            let mut new_ctx = ctx.clone();
                            new_ctx.insert(self.item.clone(), v);
                            yield new_ctx;
                        }
                    }
                };
                Box::pin(stream)
            }
            Source::PathSource(Path { root, field })
                if field.is_none() && root == "users".to_string() =>
            {
                let stream = try_stream! {
                    pin_mut!(input_ctx);
                    for await ctx in input_ctx {
                        let ctx = ctx?;
                        let users = Self::users(store.clone()).await?;
                        pin_mut!(users);
                        for await user in users {
                            let mut new_ctx = ctx.clone();
                            new_ctx.insert(self.item.clone(), user);
                            yield new_ctx;
                        }
                    }
                };
                Box::pin(stream)
            }

            _ => {
                let stream = try_stream! {
                    Err("Unsupported source".to_string())?;
                    yield HashMap::new();
                };
                Box::pin(stream)
            }
        }
    }

    async fn users(store: Store) -> Result<impl Stream<Item = Value> + Send, String> {
        store
            .range("".to_string(), FieldFilter::All)
            .await
            .map_err(|e| e.to_string())
    }
}
