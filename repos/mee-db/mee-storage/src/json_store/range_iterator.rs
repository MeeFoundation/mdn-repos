use serde_json::{Map, Value};
use tracing::error;

use super::support::*;
use crate::error::Error::KVStoreError;
use crate::error::Result;
use crate::kv_store::{KVIteratorControl, KVIteratorListener, ID_PREFIX, PATH_SEPARATOR};
use std::collections::BTreeMap;
use std::sync::Arc;
use std::sync::Mutex;
pub(super) struct KVIteratorListenerImpl {
    value_filter: Option<Box<dyn Fn(&Value) -> bool>>,
    #[allow(unused)]
    key_filter: Option<Box<dyn Fn(&str) -> bool>>,
    ordering: Option<Box<dyn Fn(&Value) -> String>>,
    left_capacity: Option<usize>,
    offset: usize,
    current_id: String,
    current_value: Value,
    result: Arc<Mutex<BTreeMap<String, Value>>>,
}

// pub enum RangeType {
//     AllObjectsByType,
//     CertainObject,
//     CertainObjectProperty,
// }

// fn get_range_type(path: &str) -> RangeType {
//     match path.matches('.').count() {
//         0 => RangeType::AllObjectsByType,
//         1 => RangeType::CertainObject,
//         _ => RangeType::CertainObjectProperty,
//     }
// }

impl KVIteratorListenerImpl {
    pub fn new(
        value_filter: Option<Box<dyn Fn(&Value) -> bool>>,
        key_filter: Option<Box<dyn Fn(&str) -> bool>>,
        ordering: Option<Box<dyn Fn(&Value) -> String>>,
        limit: Option<usize>,
        offset: usize,
        result: Arc<Mutex<BTreeMap<String, Value>>>,
    ) -> Self {
        let left_capacity = limit.map(|limit| limit + offset);
        Self {
            value_filter,
            key_filter,
            ordering,
            left_capacity,
            offset,
            current_id: "".to_string(),
            current_value: Value::Null,
            result,
        }
    }

    fn add_to_result(&mut self) -> Result<KVIteratorControl> {
        if !self
            .value_filter
            .as_ref()
            .map(|f| f(&self.current_value))
            .unwrap_or(true)
        {
            return Ok(KVIteratorControl::Next);
        }

        let order_key: String = self
            .ordering
            .as_ref()
            .map(|f| f(&self.current_value))
            .unwrap_or_else(|| self.current_id.to_string());

        let mut result = self
            .result
            .lock()
            .map_err(|e| KVStoreError(e.to_string()))?;

        if !self.current_id.is_empty() {
            self.current_value.set_id(&self.current_id);
        }

        result.insert(order_key, self.current_value.take());

        if let Some(left_capasity) = self.left_capacity.clone() {
            if left_capasity == 0 {
                if let Some(last_key) = result.last_key_value().map(|(k, _)| k.clone()) {
                    result.remove(&last_key);
                }
                if self.ordering.is_none() {
                    return Ok(KVIteratorControl::Stop);
                }
            } else {
                self.left_capacity = Some(left_capasity - 1);
            }
        }

        Ok(KVIteratorControl::Next)
    }

    fn apply_pair_to_value(&mut self, k: String, v: &Vec<u8>) -> Result<()> {
        let v: Value = serde_json::from_slice(v)?;
        println!("->> k:{:#?}, v:{:#?}", k, v);
        if k.is_empty() {
            self.current_value = v;
        } else {
            let parts = k
                .split(PATH_SEPARATOR)
                .filter(|x| !x.is_empty())
                .collect::<Vec<&str>>();

            if parts.len() > 0 {
                if self.current_value.is_null() {
                    self.current_value = if parts[0].parse::<usize>().is_ok() {
                        Value::Array(vec![])
                    } else {
                        Value::Object(Map::new())
                    }
                }

                let mut current_obj = &mut self.current_value;

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
                            array[index].merge(next_obj);
                            current_obj = &mut array[index];
                        }
                        _ if current_obj.is_object() => {
                            current_obj = current_obj
                                .as_object_mut()
                                .unwrap()
                                .entry(parts[i].to_string())
                                .or_insert(Value::Null);
                            current_obj.merge(next_obj);
                        }
                        _ => {
                            error!("Unexpected KV store state for key: {}. Collected object: {:#?}, inserting path: {}, inserting value: {}", &self.current_id, &self.current_value, &k, &v);
                            return Err(KVStoreError(
                                "Unexpected KV store state for key: {key}. ".to_string(),
                            ));
                        }
                    }
                    println!(
                        "->> current_obj: {:#?}",
                        serde_json::to_string_pretty(current_obj)
                    );
                }
            }
        }
        Ok(())
    }

    fn setup_new_object(&mut self, id: String) -> Result<()> {
        if self.current_id.is_empty() && !id.is_empty() {
            if !self.current_value.is_null() {
                self.add_to_result()?;
            }
            self.current_id = id;
        }
        Ok(())
    }

    fn split_key(&mut self, key: String) -> (String, String) {
        if key.starts_with(ID_PREFIX) {
            let mut split = key.splitn(2, PATH_SEPARATOR);
            let id = split.next().unwrap_or("").to_string();
            let key = split.next().unwrap_or("").to_string();
            (id, key)
        } else {
            ("".to_string(), key)
        }
    }
}

impl KVIteratorListener for KVIteratorListenerImpl {
    fn on_kv(&mut self, key: String, value: &Vec<u8>) -> Result<KVIteratorControl> {
        println!("->> key:{key}");
        let (id, key) = self.split_key(key);
        println!("->> id:{id}, key:{key}");
        self.setup_new_object(id)?;

        self.apply_pair_to_value(key, value)?;

        Ok(KVIteratorControl::Next)
    }

    fn flush(&mut self) -> Result<()> {
        self.add_to_result()?;
        let mut result = self
            .result
            .lock()
            .map_err(|e| KVStoreError(e.to_string()))?;

        for _ in 0..self.offset {
            if let Some(last_key) = result.first_key_value().map(|(k, _)| k.clone()) {
                result.remove(&last_key);
            }
        }
        Ok(())
    }
}
