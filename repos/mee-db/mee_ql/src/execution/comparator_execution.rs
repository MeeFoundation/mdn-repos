use super::*;
use crate::execution::support::*;

impl Comparator {
    // pub fn using_paths(&self) -> HashSet<Path> {
    //     match self {
    //         Comparator::Eq(expr)
    //         | Comparator::Ne(expr)
    //         | Comparator::Gt(expr)
    //         | Comparator::Lt(expr)
    //         | Comparator::Ge(expr)
    //         | Comparator::Le(expr)
    //         | Comparator::Matches(expr) => expr.using_paths(),
    //         Comparator::Exists => HashSet::new(),
    //     }
    // }

    pub fn value(&self, val: &Expression, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        match self {
            Comparator::Eq(expr) => {
                let left = expr.value(ctx)?;
                let right = val.value(ctx)?;
                Ok(Value::Bool(left == right))
            }
            Comparator::Ne(expr) => {
                let left = expr.value(ctx)?;
                let right = val.value(ctx)?;
                Ok(Value::Bool(left != right))
            }
            Comparator::Lt(expr) => {
                let right = expr.value(ctx).cast_to_number()?;
                let left = val.value(ctx).cast_to_number()?;
                Ok(Value::Bool(left < right))
            }
            Comparator::Gt(expr) => {
                let right = expr.value(ctx).cast_to_number()?;
                let left = val.value(ctx).cast_to_number()?;
                Ok(Value::Bool(left > right))
            }
            Comparator::Ge(expr) => {
                let right = expr.value(ctx).cast_to_number()?;
                let left = val.value(ctx).cast_to_number()?;
                Ok(Value::Bool(left >= right))
            }
            Comparator::Le(expr) => {
                let right = expr.value(ctx).cast_to_number()?;
                let left = val.value(ctx).cast_to_number()?;
                Ok(Value::Bool(left <= right))
            }
            Comparator::Matches(expr) => {
                let left = val.value(ctx).cast_to_string()?;
                let pattern = regex::Regex::new(&expr.value(ctx).cast_to_string()?)
                    .map_err(|e| e.to_string())?;

                Ok(Value::Bool(pattern.is_match(&left)))
            }
            Comparator::Exists => Ok(Value::Bool(!val.value(ctx)?.is_null())),
        }
    }
}
