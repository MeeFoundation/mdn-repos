use super::*;
use std::sync::Arc;

pub struct ExpressionExecutorImpl {
    _be: Option<Arc<dyn Executor<BoolExpression, Value> + Send + Sync>>,
    _pe: Option<Arc<dyn Executor<Path, Value> + Send + Sync>>,
    _qe: Option<Arc<dyn Executor<Query, Value> + Send + Sync>>,
}

impl ExpressionExecutorImpl {
    pub fn new(
        be: Option<Arc<dyn Executor<BoolExpression, Value> + Send + Sync>>,
        pe: Option<Arc<dyn Executor<Path, Value> + Send + Sync>>,
        qe: Option<Arc<dyn Executor<Query, Value> + Send + Sync>>,
    ) -> Self {
        Self {
            _be: be,
            _pe: pe,
            _qe: qe,
        }
    }

    pub fn set_be(&mut self, be: Arc<dyn Executor<BoolExpression, Value> + Send + Sync>) {
        self._be = Some(be);
    }

    pub fn set_pe(&mut self, pe: Arc<dyn Executor<Path, Value> + Send + Sync>) {
        self._pe = Some(pe);
    }

    pub fn set_qe(&mut self, qe: Arc<dyn Executor<Query, Value> + Send + Sync>) {
        self._qe = Some(qe);
    }

    fn be(&self) -> &Arc<dyn Executor<BoolExpression, Value> + Send + Sync> {
        self._be.as_ref().unwrap()
    }

    fn pe(&self) -> &Arc<dyn Executor<Path, Value> + Send + Sync> {
        self._pe.as_ref().unwrap()
    }

    fn qe(&self) -> &Arc<dyn Executor<Query, Value> + Send + Sync> {
        self._qe.as_ref().unwrap()
    }
}

#[async_trait::async_trait]
impl Executor<Expression, Value> for ExpressionExecutorImpl {
    async fn execute(
        &'static self,
        source_text: &'static str,
        node: &'static MeeNode<Expression>,
        ctx: &mut RuntimeContext,
    ) -> Result<Value, String> {
        match &node.value {
            Expression::Query(query) => self.qe().execute(source_text, query, ctx).await,
            Expression::BoolExpression(expr) => self.be().execute(source_text, expr, ctx).await,
            Expression::Link(path) => self.pe().execute(source_text, path, ctx).await,
            Expression::Object(map) => {
                let mut values = Map::new();
                for (k, v) in map {
                    let v = self.execute(source_text, v, ctx).await?;
                    values.insert(k.clone(), v);
                }
                Ok(Value::Object(values))
            }
            Expression::Array(arr) => {
                let mut values = Vec::new();
                for item in arr {
                    values.push(self.execute(source_text, item, ctx).await?);
                }
                Ok(Value::Array(values))
            }
            Expression::Bool(val) => Ok(Value::Bool(*val)),
            Expression::String(val) => Ok(Value::String(val.clone())),
            Expression::Number(val) => {
                let res = Number::from_f64(*val)
                .ok_or({ //for infinity only
                //only for testing
                // let error_place = format!("\x1b[31m{}\x1b[0m", &source_text[node.start..node.end]);
                let error_place = format!("<!{}!>", &source_text[node.start..node.end]);
                format!(
                    "Runtime error at position ({}, {}) (wrapped in '<!_!>') {}{}{} -  Invalid number: {:?}",
                    node.start,
                    node.end,
                    &source_text[..node.start],
                    error_place,
                    &source_text[node.end..],
                    val
                )
                })?;
                Ok(Value::Number(res))
            }
            Expression::Null => Ok(Value::Null),
        }
    }
}
