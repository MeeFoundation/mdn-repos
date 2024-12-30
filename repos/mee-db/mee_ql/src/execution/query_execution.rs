use super::*;
use crate::error::*;
use async_stream::{stream, try_stream};
use futures::pin_mut;
use futures::stream::StreamExt;
use mee_storage::json_kv_store::Record;

use std::sync::Arc;

pub struct QueryExecutorImpl;

impl QueryExecutorImpl {
    pub fn new() -> Self {
        Self {}
    }
}

impl QueryExecutorImpl {
    async fn execute_update(
        &self,
        source_text: Arc<String>,
        pair: (Arc<MeeNode<Path>>, Arc<MeeNode<Expression>>),
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;

                let (path, expr) = pair.clone();

                    let v: Value = executor_list
                        .ee
                        .execute(
                            source_text.clone(),
                            expr.clone(),
                            &mut ctx,
                            executor_list.clone(),
                        )
                        .await?;

                let path = executor_list
                    .pe
                    .clone()
                    .resolve_path(source_text.clone(), path.clone(), &mut ctx, executor_list.clone())
                    .await?;

                let prop: String = path.value.field.clone().unwrap_or("".to_string());

               match ctx.get(&path.value.root) {
                Some(LazyValue::Unevaluated(arc)) => {
                    match &arc.value {
                        Expression::User(record) => {
                            record.set(prop, v).await?;
                        }
                        _ => {
                            Err(Error::runtime_error(
                                arc.position.clone(),
                                source_text.as_str(),
                                format!("Invalid set property: {:?}", &path),
                            ))?
                        }
                    }
                }
                _ => {
                    Err(Error::runtime_error(
                        path.position.clone(),
                        source_text.as_str(),
                        format!("Incorrect path to property for update: {:?}", &path),
                    ))?
                }
               }

                yield ctx;
            }

        };
        Box::pin(stream)
    }

    async fn execute_delete(
        &self,
        source_text: Arc<String>,
        path: Arc<MeeNode<Path>>,
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;

                let path = executor_list
                    .pe
                    .clone()
                    .resolve_path(source_text.clone(), path.clone(), &mut ctx, executor_list.clone())
                    .await?;

               match ctx.get(&path.value.root) {
                Some(LazyValue::Unevaluated(arc)) => {
                    match &arc.value {
                        Expression::User(record) => {
                            match &path.value.field {
                                Some(prop) => {
                                    record.delete_property(prop.clone() ).await?;
                                }
                                None => {
                                    record.delete().await?;
                                }
                            }

                        }
                        _ => {
                            Err(Error::runtime_error(
                                arc.position.clone(),
                                source_text.as_str(),
                                format!("Invalid delete property: {:?}", &path),
                            ))?
                        }
                    }
                }
                _ => {
                    Err(Error::runtime_error(
                        path.position.clone(),
                        source_text.as_str(),
                        format!("Incorrect path to property for delete: {:?}", &path),
                    ))?
                }
               }

                yield ctx
            }
        };
        Box::pin(stream)
    }

    async fn execute_assignment(
        &self,
        pair: (Arc<MeeNode<String>>, Arc<MeeNode<Expression>>),
        input_ctx: ContextStream,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;

                let (key, expr) = pair.clone();
                ctx.insert(key.value.clone(), LazyValue::Unevaluated(expr));
                yield ctx;
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
                let mut ctx = ctx?;

                if let Some(ref filter_node) = filter_node {
                    if executor_list
                    .be
                    .execute(
                        source_text.clone(),
                        Arc::new(filter_node.clone()),
                        &mut ctx,
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

    async fn execute_append(
        &self,
        source_text: Arc<String>,
        pair: (Arc<MeeNode<Path>>, Arc<MeeNode<Expression>>),
        input_ctx: ContextStream,
        executor_list: Arc<ExecutorList>,
    ) -> ContextStream {
        let stream = try_stream! {
            pin_mut!(input_ctx);
            for await ctx in input_ctx {
                let mut ctx = ctx?;

                let (path, expr) = pair.clone();

                    let v = executor_list
                        .ee
                        .execute(
                            source_text.clone(),
                            expr.clone(),
                            &mut ctx,
                            executor_list.clone(),
                        )
                        .await?;


                 let path = executor_list
                    .pe
                    .clone()
                    .resolve_path(source_text.clone(), path.clone(), &mut ctx, executor_list.clone())
                    .await?;

                let prop: String = path.value.field.clone().unwrap_or("".to_string());

               match ctx.get(&path.value.root) {
                Some(LazyValue::Unevaluated(arc)) => {
                    match &arc.value {
                        Expression::User(record) => {
                            record.append(prop, v).await?;
                        }
                        _ => {
                            Err(Error::runtime_error(
                                arc.position.clone(),
                                source_text.as_str(),
                                format!("Invalid set property: {:?}", &path),
                            ))?
                        }
                    }
                }
                _ => {
                    Err(Error::runtime_error(
                        path.position.clone(),
                        source_text.as_str(),
                        format!("Incorrect path to property for update: {:?}", &path),
                    ))?
                }
               }

                yield ctx;
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
                            (
                                Arc::new(assignment.0.clone()),
                                Arc::new(assignment.1.clone()),
                            ),
                            new_stream,
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
                        )
                        .await;
                }
                Statement::Delete(ref delete) => {
                    new_stream = self
                        .execute_delete(
                            source_text.clone(),
                            Arc::new(delete.clone()),
                            new_stream,
                            executor_list.clone(),
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
                Statement::AppendMany(ref append) => match &append.1.value {
                    Expression::Array(values) => {
                        for value in values.iter() {
                            new_stream = self
                                .execute_append(
                                    source_text.clone(),
                                    (Arc::new(append.0.clone()), Arc::new(value.clone())),
                                    new_stream,
                                    executor_list.clone(),
                                )
                                .await;
                        }
                    }
                    _ => {}
                },
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
                let mut ctx = ctx?;

                for (_, value) in ctx.iter() {
                    match value {
                        LazyValue::Unevaluated(expr) => {
                            match &expr.value {
                                Expression::User(record) => {
                                    record.commit().await?;
                                }
                                _ => {}
                            }
                        }
                        _ => {}
                    }
                }

                if let Some(result) = &node.clone().value.result {
                    let result = Arc::new(result.clone());
                    let value = executor_list
                        .ee
                        .execute(
                            source_text.clone(),
                            result.clone(),
                            &mut ctx,
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
        ctx: &mut RuntimeContext,
        executor_list: Arc<ExecutorList>,
    ) -> Result<Value> {
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
        let result = match node.value.query_type.clone() {
            QueryType::FirstOrNull => stream.next().await.ok_or(Error::UnexpectedStateError(
                "Failed to get first or null value".to_string(),
            ))?,
            QueryType::All => {
                let arr = stream.collect::<Vec<_>>().await;
                Ok(Value::Array(arr.into_iter().collect::<Result<Vec<_>>>()?))
            }
        };

        result
    }
}
