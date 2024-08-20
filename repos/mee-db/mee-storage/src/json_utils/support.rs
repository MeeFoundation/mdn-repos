use crate::binary_kv_store::PATH_SEPARATOR;
use serde_json::{Map, Value};
use std::collections::BTreeMap;
use tracing::debug;

pub(super) fn inner_set(map: &mut BTreeMap<String, Value>, key: String, value: Value) {
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

pub(super) fn merge_json(first: &mut Value, second: Value) {
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

pub(super) fn apply_property(current: &mut Value, k: &str, v: Value) {
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
                        merge_json(&mut array[index], next_obj);
                        current_obj = &mut array[index];
                    }
                    _ if current_obj.is_object() => {
                        current_obj = current_obj
                            .as_object_mut()
                            .unwrap()
                            .entry(parts[i].to_string())
                            .or_insert(Value::Null);
                        merge_json(current_obj, next_obj);
                    }
                    _ => {
                        //TODO make error more clear
                    }
                }
            }
        }
    }
}
