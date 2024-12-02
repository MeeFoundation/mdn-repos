use super::{BinaryKVStore, KVStream, Result, KV, PATH_SEPARATOR};

use async_stream::stream;

use futures::StreamExt;
use std::collections::BTreeMap;
use std::ops::Bound::{Excluded, Included};
use std::sync::Arc;
use tokio::sync::RwLock;

#[derive(Debug)]
pub struct BTreeMapStore {
    db: Arc<RwLock<BTreeMap<String, Vec<u8>>>>,
}

impl Default for BTreeMapStore {
    fn default() -> Self {
        Self::new()
    }
}

impl BTreeMapStore {
    pub fn new() -> Self {
        Self {
            db: Arc::new(RwLock::new(BTreeMap::new())),
        }
    }
}

#[async_trait::async_trait]
impl BinaryKVStore for BTreeMapStore {
    async fn insert(&self, path: String, value: Vec<u8>) -> Result<()> {
        let mut db = self.db.write().await;
        db.insert(path, value);
        Ok(())
    }

    async fn get(&self, path: &str) -> Result<Option<Vec<u8>>> {
        let db = self.db.read().await;
        Ok(db.get(path).cloned())
    }

    async fn delete(&self, path: &str) -> Result<()> {
        let mut db = self.db.write().await;
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
        let mut db = self.db.write().await;
        for (k, v) in batch {
            db.insert(k, v);
        }
        Ok(())
    }

    async fn max_index(&self, path: String) -> Result<usize> {
        let db = self.db.read().await;
        let excluded = Excluded(format!("{path}{}", char::MAX));
        let range = db.range((Included(path.clone()), excluded));
        let mut max_index = 0;
        for (k, _) in range.clone() {
            let k = match k[path.len()..].to_string() {
                k if k.starts_with(PATH_SEPARATOR) => k[1..].to_string(),
                k => k,
            };
            let index = k.split(PATH_SEPARATOR).next().unwrap();
            if let Ok(index) = index.parse::<usize>() {
                if index > max_index {
                    max_index = index;
                }
            }
        }
        Ok(max_index)
    }

    async fn range(&self, path: String) -> Result<KVStream> {
        let db = self.db.clone();

        let s = stream! {
            let db = db.read().await;
            let excluded = Excluded(format!("{path}{}", char::MAX));
            let range = db.range((Included(path.clone()), excluded));
            for (k, v) in range {
                let k = match k[path.len()..].to_string() {
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
