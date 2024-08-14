use super::ID_PROPERTY;
use crate::kv_store::PATH_SEPARATOR;
use serde_json::{Map, Value};
use std::collections::BTreeMap;
use tracing::debug;

pub trait JsonExt {
    fn x_set_id(&mut self, id: &str) -> &mut Self;

    #[allow(unused)]
    fn x_get_id(&self) -> Option<&str>;

    #[allow(unused)]
    fn x_set_property(&mut self, key: &str, value: Value) -> &mut Self;

    fn x_merge(&mut self, other: Value) -> &mut Self;

    fn x_to_flatten_map(self, prefix: String) -> BTreeMap<String, Value>;
}

fn inner_set(map: &mut BTreeMap<String, Value>, key: String, value: Value) {
    match value {
        Value::Object(obj) => {
            for (k, v) in obj {
                let sub_key = format!("{key}{PATH_SEPARATOR}{k}");
                inner_set(map, sub_key, v);
            }
        }
        Value::Array(arr) => {
            if arr.is_empty() {
                map.insert(key, Value::Array(vec![]));
            } else {
                for (i, v) in arr.into_iter().enumerate() {
                    let sub_key = format!("{key}{PATH_SEPARATOR}{i}");
                    inner_set(map, sub_key, v);
                }
            }
        }
        _ => {
            map.insert(key, value);
        }
    }
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

fn apply_property(current: &mut Value, k: &str, v: Value) {
    if k.is_empty() {
        *current = v;
    } else {
        let parts = k
            .split(PATH_SEPARATOR)
            .filter(|x| !x.is_empty())
            .collect::<Vec<&str>>();

        if parts.len() > 0 {
            if current.is_null() {
                *current = if parts[0].parse::<usize>().is_ok() {
                    Value::Array(vec![])
                } else {
                    Value::Object(Map::new())
                }
            }

            let mut current_obj = current;

            for i in 0..parts.len() {
                let next_obj: Value = if i == parts.len() - 1 {
                    v.clone()
                } else {
                    let next_is_array = parts[i + 1].parse::<usize>().is_ok();
                    if next_is_array {
                        Value::Array(vec![])
                    } else {
                        Value::Object(Map::new())
                    }
                };

                match parts[i].parse::<usize>() {
                    Ok(index) if current_obj.is_array() => {
                        let array = current_obj.as_array_mut().unwrap();
                        if array.len() <= index {
                            array.resize(index + 1, Value::Null);
                        }
                        array[index].x_merge(next_obj);
                        current_obj = &mut array[index];
                    }
                    _ if current_obj.is_object() => {
                        current_obj = current_obj
                            .as_object_mut()
                            .unwrap()
                            .entry(parts[i].to_string())
                            .or_insert(Value::Null);
                        current_obj.x_merge(next_obj);
                    }
                    _ => {
                        //TODO make error more clear
                    }
                }
            }
        }
    }
}

impl JsonExt for Value {
    fn x_set_id(&mut self, id: &str) -> &mut Self {
        apply_property(self, ID_PROPERTY, Value::String(id.to_string()));
        self
    }

    fn x_get_id(&self) -> Option<&str> {
        self.get(ID_PROPERTY).and_then(|id| id.as_str())
    }

    fn x_set_property(&mut self, key: &str, value: Value) -> &mut Self {
        apply_property(self, key, value);
        self
    }

    fn x_merge(&mut self, other: Value) -> &mut Self {
        merge_json(self, other);
        self
    }

    fn x_to_flatten_map(self, prefix: String) -> BTreeMap<String, Value> {
        let mut map = BTreeMap::new();
        inner_set(&mut map, prefix, self);
        map
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
        first.x_merge(second);
        assert_eq!(first, expected);
    }

    #[test]
    fn merge_json_arrays() {
        let mut first = json!([1, 2, 3]);
        let second = json!([4, 5, 6]);
        let expected = json!([1, 2, 3, 4, 5, 6]);
        first.x_merge(second);
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
        first.x_merge(second);
        assert_eq!(first, expected);
    }

    #[test]
    fn set_id() {
        let mut obj = json!({});
        obj.x_set_id("id:132");
        assert_eq!(obj, json!({ID_PROPERTY: "id:132"}));
    }

    #[test]
    fn get_id() {
        let obj = json!({ID_PROPERTY: "id:123"});
        assert_eq!(obj.x_get_id(), Some("id:123"));
    }

    #[test]
    fn set_single_property() {
        let mut obj = json!({});
        obj.x_set_property("field1", json!("value1"));
        assert_eq!(obj, json!({"field1": "value1"}));
    }

    #[test]
    fn set_complex_property() {
        let mut obj = Value::Null;
        obj.x_set_property("field1", json!("value1"));
        obj.x_set_property(&format!("field2{PATH_SEPARATOR}field3"), json!("value3"));
        obj.x_set_property(
            &format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}0"),
            json!("value4"),
        );
        obj.x_set_property(
            &format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}1"),
            json!("value5"),
        );

        assert_eq!(
            obj,
            json!({
                "field1": "value1",
                "field2": {
                    "field3": "value3",
                    "field4": ["value4", "value5"]
                }
            })
        );
    }

    #[test]
    fn to_map() {
        let obj = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": ["value4", "value5"]
            }
        });
        let map = obj.x_to_flatten_map("key".to_string());
        let mut expected = BTreeMap::new();
        expected.insert(format!("key{PATH_SEPARATOR}field1"), json!("value1"));
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field3"),
            json!("value3"),
        );
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}0"),
            json!("value4"),
        );
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}1"),
            json!("value5"),
        );

        assert_eq!(map, expected);
    }
}
