use super::*;
use crate::execution::support::*;

impl BoolExpression {
    pub fn value(&self, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        match self {
            BoolExpression::And(exprs) => {
                for expr in exprs {
                    if !expr.value(ctx).cast_to_bool()? {
                        return Ok(Value::Bool(false));
                    }
                }
                Ok(Value::Bool(true))
            }
            BoolExpression::Or(exprs) => {
                for expr in exprs {
                    if expr.value(ctx).cast_to_bool()? {
                        return Ok(Value::Bool(true));
                    }
                }
                Ok(Value::Bool(false))
            }
            BoolExpression::Not(expr) => {
                if expr.value(ctx).cast_to_bool()? {
                    Ok(Value::Bool(false))
                } else {
                    Ok(Value::Bool(true))
                }
            }
            BoolExpression::Comparison { val, comparator } => comparator.value(val, ctx),
            BoolExpression::Expression(path) => path.value(ctx),
            BoolExpression::True => Ok(Value::Bool(true)),
            BoolExpression::False => Ok(Value::Bool(false)),
        }
    }
}
