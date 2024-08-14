use super::PATH_SEPARATOR;
use super::{KVIteratorControl, KVIteratorListener, KVStore};
use crate::error::{Error::LockError, Result};
use std::collections::BTreeMap;
use std::ops::Bound::{Excluded, Included};
use std::sync::{Arc, RwLock};

pub struct BTreeMapStore {
    db: Arc<RwLock<BTreeMap<String, Vec<u8>>>>,
}

impl BTreeMapStore {
    pub fn new() -> Self {
        Self {
            db: Arc::new(RwLock::new(BTreeMap::new())),
        }
    }
}

impl KVStore for BTreeMapStore {
    fn insert(&self, path: String, value: Vec<u8>) -> Result<()> {
        let mut db = self.db.write().map_err(|e| LockError(e.to_string()))?;
        db.insert(path, value);
        Ok(())
    }

    fn get(&self, path: &str) -> Result<Option<Vec<u8>>> {
        let db = self.db.read().map_err(|e| LockError(e.to_string()))?;
        Ok(db.get(path).cloned())
    }

    fn range(&self, path: String, listener: &mut Box<dyn KVIteratorListener>) -> Result<()> {
        let db = self.db.read().map_err(|e| LockError(e.to_string()))?;
        let excluded = Excluded(format!("{}{}", &path, char::MAX));
        let range = db.range((Included(path.clone()), excluded));
        let mut skip_prefix = "".to_string();

        for (k, v) in range {
            let k = match k.replace(&path, "") {
                k if k.starts_with(PATH_SEPARATOR) => k[1..].to_string(),
                k => k,
            };

            if !skip_prefix.is_empty() && k.starts_with(&skip_prefix) {
                continue;
            }

            match listener.on_kv(k, v) {
                Ok(KVIteratorControl::SkipPrefix(prefix)) => {
                    skip_prefix = prefix.clone();
                }
                Ok(KVIteratorControl::Next) => {}
                Ok(KVIteratorControl::Stop) => {
                    break;
                }
                Err(e) => return Err(e),
            }
        }
        listener.flush()?;

        Ok(())
    }

    fn delete(&self, path: &str) -> Result<()> {
        let mut db = self.db.write().map_err(|e| LockError(e.to_string()))?;
        let excluded = Excluded(format!("{}{}", &path, char::MAX));
        let keys_to_delete = db
            .range((Included(path.to_string()), excluded))
            .map(|(k, _)| k.clone())
            .collect::<Vec<_>>();

        for key in keys_to_delete {
            db.remove(&key);
        }

        Ok(())
    }
}
