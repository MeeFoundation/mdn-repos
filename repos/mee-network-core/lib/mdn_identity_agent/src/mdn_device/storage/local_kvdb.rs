use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use redb::{Database, TableDefinition};
use serde::{de::DeserializeOwned, Serialize};
use std::sync::Arc;

#[async_trait]
pub trait LocalKvDb {
    async fn get_string_value(&self, key: String) -> MdnIdentityAgentResult<Option<String>> {
        Ok(match self.get_value(key).await? {
            Some(res) => Some(String::from_utf8(res)?),
            None => None,
        })
    }
    async fn get_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>>;

    async fn set_value(&self, key: String, value: Vec<u8>) -> MdnIdentityAgentResult;

    async fn set_string_value(&self, key: String, value: String) -> MdnIdentityAgentResult {
        self.set_value(key, value.as_bytes().to_vec()).await
    }

    async fn del_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>>;
}

pub struct LocalKvDbExt(pub Arc<dyn LocalKvDb + Send + Sync>);

impl LocalKvDbExt {
    pub fn new(local_db: Arc<dyn LocalKvDb + Send + Sync>) -> Self {
        Self(local_db)
    }
    pub async fn set_json_value<T>(&self, key: String, value: &T) -> MdnIdentityAgentResult
    where
        T: Serialize + Send + Sync,
    {
        self.0.set_value(key, serde_json::to_vec(value)?).await
    }

    pub async fn get_json_value<R>(&self, key: String) -> MdnIdentityAgentResult<Option<R>>
    where
        R: DeserializeOwned,
    {
        Ok(match self.0.get_value(key).await? {
            Some(res) => Some(serde_json::from_slice(&res)?),
            None => None,
        })
    }
}

pub struct LocalKvDbRedb {
    db_file_path: String,
}

impl LocalKvDbRedb {
    const MAIN_TABLE: TableDefinition<'_, &str, Vec<u8>> = TableDefinition::new("MAIN_TABLE");

    pub async fn try_new(db_file_path: String) -> MdnIdentityAgentResult<Self> {
        let db_file_path = db_file_path.clone();

        tokio::task::spawn_blocking({
            let db_file_path = db_file_path.clone();
            move || {
                let db = Database::create(db_file_path)?;

                let write_txn = db.begin_write()?;
                write_txn.open_table(Self::MAIN_TABLE)?;
                write_txn.commit()?;

                MdnIdentityAgentResult::Ok(())
            }
        })
        .await??;

        Ok(Self { db_file_path })
    }
}

#[async_trait]
impl LocalKvDb for LocalKvDbRedb {
    async fn get_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>> {
        let db_file_path = self.db_file_path.clone();

        let res = tokio::task::spawn_blocking(move || {
            let db = Database::create(db_file_path)?;

            let read_txn = db.begin_read()?;
            let table = read_txn.open_table(Self::MAIN_TABLE)?;

            let res = table.get(key.as_str())?.map(|r| r.value());

            MdnIdentityAgentResult::Ok(res)
        })
        .await??;

        Ok(res)
    }
    async fn set_value(&self, key: String, value: Vec<u8>) -> MdnIdentityAgentResult {
        let db_file_path = self.db_file_path.clone();

        tokio::task::spawn_blocking(move || {
            let db = Database::create(db_file_path)?;

            let write_txn = db.begin_write()?;

            {
                let mut table = write_txn.open_table(Self::MAIN_TABLE)?;
                table.insert(key.as_str(), value)?;
            }

            write_txn.commit()?;

            MdnIdentityAgentResult::Ok(())
        })
        .await??;

        Ok(())
    }
    async fn del_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>> {
        let db_file_path = self.db_file_path.clone();

        let res = tokio::task::spawn_blocking(move || {
            let db = Database::create(db_file_path)?;

            let write_txn = db.begin_write()?;

            let res = {
                let mut table = write_txn.open_table(Self::MAIN_TABLE)?;
                let val = table.remove(key.as_str())?.map(|r| r.value());
                val
            };

            write_txn.commit()?;

            MdnIdentityAgentResult::Ok(res)
        })
        .await??;

        Ok(res)
    }
}

#[tokio::test]
async fn local_kvdb_smoke() {
    use mee_test_utils::cargo_target_level_filename;

    let db_file = cargo_target_level_filename!("local_kvdb_smoke");

    let db = LocalKvDbRedb::try_new(db_file).await.unwrap();
    let test_key = "test".to_string();
    let test_value = vec![123];

    db.set_value(test_key.clone(), test_value.clone())
        .await
        .unwrap();

    assert_eq!(
        db.get_value(test_key.clone()).await.unwrap(),
        Some(test_value.clone())
    );

    assert_eq!(
        db.del_value(test_key.clone()).await.unwrap(),
        Some(test_value)
    );
}
