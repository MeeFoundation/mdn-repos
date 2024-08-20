use super::{KVStore, KVStream, KV, PATH_SEPARATOR};
use crate::error::Result;

use async_stream::stream;

use futures::StreamExt;
use std::collections::BTreeMap;
use std::ops::Bound::{Excluded, Included};
use std::sync::Arc;
use tokio::sync::RwLock;

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

#[async_trait::async_trait]
impl KVStore for BTreeMapStore {
    async fn insert(&self, path: String, value: Vec<u8>) -> Result<()> {
        let mut db = self.db.write().await;
        // .map_err(|e| LockError(e.to_string()))?;
        db.insert(path, value);
        Ok(())
    }

    async fn get(&self, path: &str) -> Result<Option<Vec<u8>>> {
        let db = self.db.read().await; //.map_err(|e| LockError(e.to_string()))?;
        Ok(db.get(path).cloned())
    }

    async fn delete(&self, path: &str) -> Result<()> {
        let mut db = self.db.write().await; //.map_err(|e| LockError(e.to_string()))?;
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

    async fn insert_many(&self, batch: Vec<KV>) -> Result<()> {
        let mut db = self.db.write().await; //.map_err(|e| LockError(e.to_string()))?;
        for (k, v) in batch {
            db.insert(k, v);
        }
        Ok(())
    }

    async fn range(&self, path: String) -> Result<KVStream> {
        let db = self.db.clone();

        let s = stream! {
            let db = db.read().await;
            let excluded = Excluded(format!("{}{}", &path, char::MAX));
            let range = db.range((Included(path.clone()), excluded));
            for (k, v) in range {
                let k = match k.replace(&path, "") {
                    k if k.starts_with(PATH_SEPARATOR) => k[1..].to_string(),
                    k => k,
                };
                yield (k.clone(), v.clone());
            }
        }
        .boxed();

        Ok(s)
    }
}