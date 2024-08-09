use serde_json::{Map, Value};
use tracing::debug;

use super::ID_PROPERTY;

pub trait JsonExt {
    fn set_id(&mut self, id: &str) -> &mut Self;

    #[allow(unused)]
    fn get_id(&self) -> Option<&str>;

    #[allow(unused)]
    fn set_property(&mut self, key: &str, value: Value) -> &mut Self;

    fn merge(&mut self, other: Value) -> &mut Self;
}

fn merge_json(first: &mut Value, second: Value) {
    match (first, second) {
        (Value::Object(first), Value::Object(second)) => {
            for (key, value) in second {
                merge_json(first.entry(key).or_insert(Value::Null), value);
            }
        }
        (Value::Array(first), Value::Array(second)) => {
            first.extend(second);
        }
        (first, second) => {
            debug!("Value {:?} replaced with {:?}", first, second);
            *first = second;
        }
    }
}

fn merge_json_map(first: &mut Map<String, Value>, second: Map<String, Value>) {
    for (key, value) in second {
        merge_json(first.entry(key).or_insert(Value::Null), value);
    }
}

fn add_property(obj: &mut Value, key: &str, value: Value) {
    match obj {
        Value::Object(obj) => {
            obj.insert(key.to_string(), value);
        }
        _ => {
            debug!(
                "Value {:?} replaced with object with key {:?} and value {:?}",
                obj, key, value
            );
            let mut new_obj = Map::new();
            new_obj.insert(key.to_string(), value);
            *obj = Value::Object(new_obj);
        }
    }
}

impl JsonExt for Value {
    fn set_id(&mut self, id: &str) -> &mut Self {
        add_property(self, ID_PROPERTY, Value::String(id.to_string()));
        self
    }

    fn get_id(&self) -> Option<&str> {
        self.get(ID_PROPERTY).and_then(|id| id.as_str())
    }

    fn set_property(&mut self, key: &str, value: Value) -> &mut Self {
        add_property(self, key, value);
        self
    }

    fn merge(&mut self, other: Value) -> &mut Self {
        merge_json(self, other);
        self
    }
}

impl JsonExt for Map<String, Value> {
    fn set_id(&mut self, id: &str) -> &mut Self {
        self.insert(ID_PROPERTY.to_string(), Value::String(id.to_string()));
        self
    }

    fn get_id(&self) -> Option<&str> {
        self.get(ID_PROPERTY).and_then(|id| id.as_str())
    }

    fn set_property(&mut self, key: &str, value: Value) -> &mut Self {
        self.insert(key.to_string(), value);
        self
    }

    fn merge(&mut self, other: Value) -> &mut Self {
        if let Value::Object(obj) = other {
            merge_json_map(self, obj);
        } else {
            debug!("Cannot merge map with {:?}", other);
        }
        self
    }
}

#[cfg(test)]
mod test {
    use super::*;
    use serde_json::json;

    #[test]
    fn merge_json_objects() {
        let mut first = json!(
            {
                "field1": "value1",
                "field2": "value2",
                "field3": {
                    "field4": "value4"
                }
            }
        );
        let second = json!(
            {
                "field1": "value6",
                "field3": {
                    "field5": "value5"
                }
            }
        );
        let expected = json!(
            {
                "field1": "value6",
                "field2": "value2",
                "field3": {
                    "field4": "value4",
                    "field5": "value5"
                }
            }
        );
        merge_json(&mut first, second);
        assert_eq!(first, expected);
    }

    #[test]
    fn merge_json_arrays() {
        let mut first = json!([1, 2, 3]);
        let second = json!([4, 5, 6]);
        let expected = json!([1, 2, 3, 4, 5, 6]);
        merge_json(&mut first, second);
        assert_eq!(first, expected);
    }

    #[test]
    fn merge_json_replace_incompatible() {
        let mut first = json!([1, 2, 3,]);
        let second = json!(
            {
                "field1": ["value6", "value7"],
            }
        );
        let expected = second.clone();
        merge_json(&mut first, second);
        assert_eq!(first, expected);
    }
}
