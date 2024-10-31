use super::*;

impl Path {
    pub fn to_field(&self) -> String {
        self.field.as_ref().map_or(self.root.clone(), |f| {
            format!("{}{PATH_SEPARATOR}{f}", self.root)
        })
    }

    pub fn value(&self, ctx: &HashMap<String, Value>) -> Result<Value, String> {
        let var = ctx
            .get(&self.root)
            .ok_or(format!("Variable {} not found in context", self.root))?;

        Ok(self
            .field
            .as_ref()
            .map(|f| var.x_get_property(&f).cloned().unwrap_or(Value::Null))
            .unwrap_or(var.clone()))
    }

    pub fn as_number(&self, ctx: &HashMap<String, Value>) -> Result<f64, String> {
        self.value(ctx)?
            .as_f64()
            .ok_or(format!("Expected number at path {}", self.root))
    }

    pub fn as_bool(&self, ctx: &HashMap<String, Value>) -> Result<bool, String> {
        self.value(ctx)?
            .as_bool()
            .ok_or(format!("Expected boolean at path {}", self.root))
    }

    pub fn as_string(&self, ctx: &HashMap<String, Value>) -> Result<String, String> {
        self.value(ctx)?
            .as_str()
            .map(|s| s.to_string())
            .ok_or(format!("Expected string at path {}", self.root))
    }

    pub fn as_array(&self, ctx: &HashMap<String, Value>) -> Result<Vec<Value>, String> {
        self.value(ctx)?
            .as_array()
            .map(|a| a.to_vec())
            .ok_or(format!("Expected array at path {}", self.root))
    }

    pub fn as_object(&self, ctx: &HashMap<String, Value>) -> Result<Map<String, Value>, String> {
        self.value(ctx)?
            .as_object()
            .map(|o| o.clone())
            .ok_or(format!("Expected object at path {}", self.root))
    }
}
