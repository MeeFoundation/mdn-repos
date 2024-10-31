use super::*;

impl Expression {
    pub fn value(&self, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        match self {
            Expression::Value(val) => val.value(ctx),
            Expression::Query(query) => query.value(ctx),
            Expression::BoolExpression(expr) => expr.value(ctx),
            Expression::Link(path) => path.value(ctx),
        }
    }
}
