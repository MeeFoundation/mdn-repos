use super::*;

impl MeeValue {
    pub fn value(&self, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        match self {
            MeeValue::Expression(expr) => expr.value(ctx),
            MeeValue::Object(map) => {
                let values = map
                    .into_iter()
                    .map(|(k, v)| v.value(ctx).map(|v| (k.clone(), v)))
                    .collect::<Result<serde_json::Map<_, _>, _>>()?;
                Ok(Value::Object(values))
            }
            MeeValue::Array(arr) => {
                let values = arr
                    .into_iter()
                    .map(|v| v.value(ctx))
                    .collect::<Result<Vec<_>, _>>()?;
                Ok(Value::Array(values))
            }
            MeeValue::Bool(val) => Ok(Value::Bool(*val)),
            MeeValue::String(val) => Ok(Value::String(val.clone())),
            MeeValue::Number(val) => {
                let res = Number::from_f64(*val).ok_or(format!("Invalid number '{val}'"))?;
                Ok(Value::Number(res))
            }
            MeeValue::Null => Ok(Value::Null),
        }
    }
}
