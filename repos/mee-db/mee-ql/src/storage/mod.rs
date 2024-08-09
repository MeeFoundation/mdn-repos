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
    fn set(&self, key: String, value: Value) -> ApiResult<()>;

    fn get(&self, key: String) -> ApiResult<Option<Value>>;

    fn delete(&self, key: String) -> ApiResult<()>;

    fn generate_id(&self) -> ApiResult<String>;
}

pub struct StorageBTreeMapImpl {
    db: Arc<RwLock<BTreeMap<String, Value>>>,
}

impl StorageBTreeMapImpl {
    pub fn new() -> Self {
        Self {
            db: Arc::new(RwLock::new(BTreeMap::new())),
        }
    }
}

impl Storage for StorageBTreeMapImpl {
    fn set(&self, key: String, value: Value) -> ApiResult<()> {
        let mut db = self.db.write().unwrap();
        db.insert(key, value);
        Ok(())
    }

    fn get(&self, key: String) -> ApiResult<Option<Value>> {
        let db = self.db.read().unwrap();
        Ok(db.get(&key).cloned())
    }

    fn delete(&self, key: String) -> ApiResult<()> {
        let mut db = self.db.write().unwrap();
        db.remove(&key);
        Ok(())
    }

    fn generate_id(&self) -> ApiResult<String> {
        // Пример генерации уникального идентификатора
        Ok(uuid::Uuid::new_v7().to_string())
    }
}
