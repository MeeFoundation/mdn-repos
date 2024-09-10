use serde::{Deserialize, Serialize};
use serde_json::Value;

use std::collections::HashMap;
use std::collections::HashSet;

use utoipa::ToSchema;

use crate::json_utils::JsonExt;

use super::expression::Expr;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Default, ToSchema)]
pub struct DeriveClause(HashMap<String, Expr>);

impl DeriveClause {
    pub fn get_value(&self, value: &Value) -> Value {
        self.0.iter().fold(Value::Null, |mut acc, (k, v)| {
            if let Some(v) = v.get_value(Some(value)) {
                acc.x_set_property(k, v);
            }
            acc
        })
    }

    pub fn get_using_fields(&self) -> HashSet<String> {
        self.0.iter().fold(HashSet::new(), |mut acc, (_, v)| {
            acc.extend(v.get_using_fields());
            acc
        })
    }

    pub fn is_empty(&self) -> bool {
        self.0.is_empty()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn derive_clause_item_named_select_item() {
        let val = json!({
            "field1": "value1"
        });
        let json = r#"{"new_field1": "a","new_field2": { "@field1": "$upper"}}"#;
        let item: DeriveClause = serde_json::from_str(json).unwrap();
        assert_eq!(
            item.get_value(&val),
            json!({
                "new_field1": "a",
                "new_field2": "VALUE1"
            })
        );
    }
}
