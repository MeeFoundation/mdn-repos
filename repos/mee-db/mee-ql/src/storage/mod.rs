use crate::error::*;
use serde_json::Value;
use std::collections::HashMap;
use std::sync::Arc;

pub type DB = Arc<dyn Storage + Sync + Send>;

#[derive(Debug)]
pub enum MergeStrategy {
    Replace,
    IgnoreExisting,
    Append,
}

pub trait Storage {
    fn create_node(&self, schema: String, properties: HashMap<String, Value>) -> ApiResult<String>;

    fn merge_node(
        &self,
        schema: String,
        id: String,
        properties: HashMap<String, Value>,
        strategy: MergeStrategy,
    ) -> ApiResult<HashMap<String, Value>>;

    fn delete_node(&self, schema: String, id: String) -> ApiResult<String>;

    fn select_nodes_by_id(
        &self,
        schema: String,
        ids: Vec<String>,
        fields: Option<Vec<String>>,
    ) -> ApiResult<Vec<HashMap<String, Value>>>;

    fn select_nodes_by_filter(
        &self,
        schema: String,
        properties: HashMap<String, Value>,
        fields: Option<Vec<String>>,
    ) -> ApiResult<Vec<HashMap<String, Value>>>;
}

pub struct StorageImpl {
    db: sled::Db,
}

impl StorageImpl {
    pub fn new(path: &str) -> ApiResult<Self> {
        let db = sled::open(path)?;
        Ok(Self { db })
    }
}

impl Storage for StorageImpl {
    fn create_node(&self, schema: String, properties: HashMap<String, Value>) -> ApiResult<String> {
        let tree = self.db.open_tree(schema)?;
        let id = self.db.generate_id()?;
        let str_id = id.to_string();
        let value: String = serde_json::to_string(&properties)?;
        tree.insert(str_id.clone(), value.as_bytes())?;

        Ok(str_id)
    }

    fn merge_node(
        &self,
        schema: String,
        id: String,
        properties: HashMap<String, Value>,
        strategy: MergeStrategy,
    ) -> ApiResult<HashMap<String, Value>> {
        let tree = self.db.open_tree(schema)?;
        let value = tree.get(&id)?.unwrap_or_default();
        let mut existing_properties: HashMap<String, Value> = serde_json::from_slice(&value)?;
        let mut new_properties = properties;

        match strategy {
            MergeStrategy::IgnoreExisting => {
                new_properties.extend(existing_properties);
            }
            MergeStrategy::Append => {
                existing_properties.extend(new_properties);
                new_properties = existing_properties;
            }
            MergeStrategy::Replace => {}
        }

        let value = serde_json::to_string(&new_properties)?;
        tree.insert(id.clone(), value.as_bytes())?;

        new_properties.insert("id".to_string(), Value::String(id));

        Ok(new_properties)
    }

    fn delete_node(&self, schema: String, id: String) -> ApiResult<String> {
        let tree = self.db.open_tree(schema)?;
        tree.remove(&id)?;
        Ok(id)
    }

    fn select_nodes_by_id(
        &self,
        schema: String,
        ids: Vec<String>,
        fields: Option<Vec<String>>,
    ) -> ApiResult<Vec<HashMap<String, Value>>> {
        let tree = self.db.open_tree(schema)?;
        let mut ApiResult = vec![];

        for id in ids {
            let value = tree.get(&id)?.unwrap_or_default();
            let mut properties: HashMap<String, Value> = serde_json::from_slice(&value)?;

            if let Some(fields) = fields.clone() {
                for key in fields {
                    properties.remove(&key);
                }
            }

            properties.insert("id".to_string(), Value::String(id.clone()));

            ApiResult.push(properties);
        }

        Ok(ApiResult)
    }

    fn select_nodes_by_filter(
        &self,
        schema: String,
        expected_properties: HashMap<String, Value>,
        fields: Option<Vec<String>>,
    ) -> ApiResult<Vec<HashMap<String, Value>>> {
        let tree = self.db.open_tree(schema)?;
        let mut ApiResult = vec![];

        for item in tree.iter() {
            let (id, value) = item?;
            let id = std::str::from_utf8(&id).unwrap();
            let value = std::str::from_utf8(&value).unwrap();

            let properties: HashMap<String, Value> = serde_json::from_str(&value)?;

            let mut matched = true;
            for (key, expected_value) in expected_properties.iter() {
                if let Some(value) = properties.get(key) {
                    if value != expected_value {
                        matched = false;
                        break;
                    }
                }
            }

            if matched {
                let mut properties = properties;
                if let Some(fields) = fields.clone() {
                    for key in fields {
                        properties.remove(&key);
                    }
                }

                properties.insert("id".to_string(), Value::String(id.to_string()));

                ApiResult.push(properties);
            }
        }

        Ok(ApiResult)
    }
}
