use super::*;
use async_stream::{stream, try_stream};
use futures::pin_mut;
use futures::stream::Stream;
use mee_storage::json_kv_store::{JsonStream, Store};
use mee_storage::query_el::FieldFilter;
use std::result::Result as StdResult;

#[async_trait::async_trait]
trait QueryExecutor {
    async fn execute(&'static self, store: Store) -> JsonResultStream;
}

impl Query {
    fn get_body(&self) -> &QueryBody {
        match self {
            Query::ArrayQuery { body } | Query::ElementQuery { body } => body,
        }
    }

    pub fn value(&self, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        self.get_body()
            .result
            .as_ref()
            .map(|expr| expr.value(ctx))
            .unwrap_or(Ok(Value::Null))
    }
}

impl QueryBody {
    fn get_user_id(&self, ctx: &HashMap<String, Value>) -> Result<String, String> {
        ctx.get(&self.main_iterator.item)
            .ok_or(format!(
                "Cannot resolve path root '{}'",
                self.main_iterator.item
            ))?
            .x_get_id()
            .ok_or(format!(
                "Expected an object at path '{}'",
                self.main_iterator.item
            ))
            .map(|id| id.to_string())
    }

    fn execute_updates(&'static self, store: Store, input_ctx: ContextStream) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let ctx = ctx?;
                for (path, expr) in self.updates.iter() {
                    let v = expr.value(&ctx)?;
                    let user_id = self.get_user_id(&ctx)?;
                    let path_str = path.to_store_path(&user_id);

                    store.set(path_str, v).await.map_err(|e| e.to_string())?;
                }
                yield ctx;
            }
        };
        Box::pin(stream)
    }

    fn execute_deletes(&'static self, store: Store, input_ctx: ContextStream) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let ctx = ctx?;
                match &self.deletes {
                    DeleteStmt::Paths(paths) => {
                        for path in paths.iter() {
                            let user_id = self.get_user_id(&ctx)?;
                            let path_str = path.to_store_path(&user_id);

                            store.delete(path_str).await.map_err(|e| e.to_string())?;
                        }
                    }
                    DeleteStmt::All => {
                        let user_id = self.get_user_id(&ctx)?;
                        let path_str = Path {
                            root: self.main_iterator.item.clone(),
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
impl QueryExecutor for QueryBody {
    async fn execute(&'static self, store: Store) -> JsonResultStream {
        let initial_stream = stream! {
            yield Ok::<HashMap<String, Value>, String>(HashMap::new());
        };
        let mut main_stream: ContextStream = Box::pin(initial_stream);

        main_stream = self.main_iterator.execute(store.clone(), main_stream).await;

        let mut new_stream = main_stream;

        for iterator in self.embedded_iterators.iter() {
            new_stream = iterator.execute(store.clone(), new_stream).await;
        }

        new_stream = self.execute_updates(store.clone(), new_stream);

        new_stream = self.execute_deletes(store.clone(), new_stream);

        let stream = try_stream! {
            for await ctx in new_stream {
                let ctx = ctx?;
                if let Some(result) = &self.result {
                    let value = result.value(&ctx)?;
                    yield value;
                } else {
                    yield Value::Null;
                }
            }
        };

        Box::pin(stream)
    }
}
