use serde_json::Value;

use super::support::*;
use super::ID_PREFIX;
use crate::error::Result;
use crate::kv_store::{KVStream, PATH_SEPARATOR};
use futures::StreamExt;
use std::collections::BTreeMap;

pub enum KVIteratorControl {
    #[allow(unused)]
    SkipPrefix(String),
    Next,
    Stop,
}
pub(super) struct KVIteratorListenerImpl {
    value_filter: Option<Box<dyn Fn(&Value) -> bool + Send + Sync>>,
    #[allow(unused)]
    key_filter: Option<Box<dyn Fn(&str) -> bool + Send + Sync>>,
    ordering: Option<Box<dyn Fn(&Value) -> String + Send + Sync>>,
    left_capacity: Option<usize>,
    offset: usize,
    current_id: String,
    current_value: Value,
    result: BTreeMap<String, Value>,
}

impl KVIteratorListenerImpl {
    pub fn new(
        value_filter: Option<Box<dyn Fn(&Value) -> bool + Send + Sync>>,
        key_filter: Option<Box<dyn Fn(&str) -> bool + Send + Sync>>,
        ordering: Option<Box<dyn Fn(&Value) -> String + Send + Sync>>,
        limit: Option<usize>,
        offset: usize,
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
            result: BTreeMap::new(),
        }
    }

    pub async fn collect(&mut self, mut kv_byte_stream: KVStream) -> Result<Vec<Value>> {
        while let Some((k, v)) = kv_byte_stream.next().await {
            let control = self.on_kv(k, &v);
            match control {
                Ok(KVIteratorControl::Next) => {}
                Ok(KVIteratorControl::Stop) => break,
                Err(e) => return Err(e),
                _ => {}
            }
        }
        self.flush()?;
        Ok(self.result.values().cloned().collect())
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

        let result = &mut self.result;

        if !self.current_id.is_empty() {
            self.current_value.x_set_id(&self.current_id);
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

    fn on_kv(&mut self, key: String, value: &Vec<u8>) -> Result<KVIteratorControl> {
        println!("->> key:{key}");
        let (id, key) = self.split_key(key);
        println!("->> id:{id}, key:{key}");
        self.setup_new_object(id)?;
        let v = serde_json::from_slice(value)?;
        self.current_value.x_set_property(&key, v);

        Ok(KVIteratorControl::Next)
    }

    fn flush(&mut self) -> Result<()> {
        self.add_to_result()?;
        let result = &mut self.result;
        for _ in 0..self.offset {
            if let Some(last_key) = result.first_key_value().map(|(k, _)| k.clone()) {
                result.remove(&last_key);
            }
        }
        Ok(())
    }
}
