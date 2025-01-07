use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_macro_utils::let_clone;
use redb::{Database, ReadOnlyTable, ReadableTable, TableDefinition};
use serde::{de::DeserializeOwned, Serialize};
use std::{ops::RangeBounds, sync::Arc};

#[async_trait]
pub trait LocalKvDb {
    async fn get_string_value(&self, key: String) -> MdnIdentityAgentResult<Option<String>> {
        Ok(match self.get_value(key).await? {
            Some(res) => Some(String::from_utf8(res)?),
            None => None,
        })
    }
    async fn get_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>>;

    async fn range_inclusive(
        &self,
        start_bound: Option<String>,
        end_bound: Option<String>,
    ) -> MdnIdentityAgentResult<Vec<(String, Vec<u8>)>>;

    async fn all_values(
        &self,
        filter: Box<dyn for<'fa> Fn(&'fa str) -> bool + Send>,
    ) -> MdnIdentityAgentResult<Vec<(String, Vec<u8>)>>;

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
    table_name: String,
}

impl LocalKvDbRedb {
    pub async fn try_new(db_file_path: String, table_name: String) -> MdnIdentityAgentResult<Self> {
        let db_file_path = db_file_path.clone();

        tokio::task::spawn_blocking({
            let_clone!(table_name);

            {
                let db_file_path = db_file_path.clone();
                move || {
                    let db = Database::create(db_file_path)?;

                    let write_txn = db.begin_write()?;

                    let table_name: TableDefinition<'_, &str, Vec<u8>> =
                        TableDefinition::new(&table_name);

                    write_txn.open_table(table_name)?;
                    write_txn.commit()?;

                    MdnIdentityAgentResult::Ok(())
                }
            }
        })
        .await??;

        Ok(Self {
            db_file_path,
            table_name,
        })
    }
}

fn make_range_res<'a, R: RangeBounds<&'a str>>(
    table: &ReadOnlyTable<&str, Vec<u8>>,
    range: R,
) -> MdnIdentityAgentResult<Vec<(String, Vec<u8>)>> {
    Ok(table
        .range(range)?
        .map(|kvr| kvr.map(|(k, v)| (k.value().to_string(), v.value())))
        .collect::<Result<Vec<_>, _>>()?)
}

#[async_trait]
impl LocalKvDb for LocalKvDbRedb {
    async fn get_value(&self, key: String) -> MdnIdentityAgentResult<Option<Vec<u8>>> {
        let db_file_path = self.db_file_path.clone();
        let table_name = self.table_name.clone();

        let res = tokio::task::spawn_blocking({
            move || {
                let db = Database::open(db_file_path)?;

                let read_txn = db.begin_read()?;

                let table_name: TableDefinition<'_, &str, Vec<u8>> =
                    TableDefinition::new(&table_name);

                let table = read_txn.open_table(table_name)?;

                let res = table.get(key.as_str())?.map(|r| r.value());

                MdnIdentityAgentResult::Ok(res)
            }
        })
        .await??;

        Ok(res)
    }
    async fn all_values(
        &self,
        filter: Box<dyn for<'fa> Fn(&'fa str) -> bool + Send>,
    ) -> MdnIdentityAgentResult<Vec<(String, Vec<u8>)>> {
        let db_file_path = self.db_file_path.clone();
        let table_name = self.table_name.clone();

        let res = tokio::task::spawn_blocking({
            move || {
                let db = Database::open(db_file_path)?;

                let read_txn = db.begin_read()?;

                let table_name_def: TableDefinition<'_, &str, Vec<u8>> =
                    TableDefinition::new(&table_name);

                let table = read_txn.open_table(table_name_def)?;

                let res = table
                    .iter()?
                    .filter_map(|k| match k {
                        Ok((k, v)) => {
                            let key = k.value();

                            if filter(key) {
                                Some((key.to_string(), v.value()))
                            } else {
                                None
                            }
                        }
                        Err(e) => {
                            log::error!("Error filtering local db ({table_name}) entries: {e}");
                            None
                        }
                    })
                    .collect();

                MdnIdentityAgentResult::Ok(res)
            }
        })
        .await??;

        Ok(res)
    }
    async fn range_inclusive(
        &self,
        start_bound: Option<String>,
        end_bound: Option<String>,
    ) -> MdnIdentityAgentResult<Vec<(String, Vec<u8>)>> {
        let db_file_path = self.db_file_path.clone();
        let table_name = self.table_name.clone();

        let res = tokio::task::spawn_blocking(move || {
            let db = Database::open(db_file_path)?;

            let read_txn = db.begin_read()?;

            let table_name: TableDefinition<'_, &str, Vec<u8>> = TableDefinition::new(&table_name);

            let table = read_txn.open_table(table_name)?;

            let res = match (start_bound, end_bound) {
                (None, None) => make_range_res(&table, ..),
                (None, Some(end)) => make_range_res(&table, ..end.as_str()),
                (Some(start), None) => make_range_res(&table, start.as_str()..),
                (Some(start), Some(end)) => make_range_res(&table, start.as_str()..=end.as_str()),
            }?;

            MdnIdentityAgentResult::Ok(res)
        })
        .await??;

        Ok(res)
    }
    async fn set_value(&self, key: String, value: Vec<u8>) -> MdnIdentityAgentResult {
        let db_file_path = self.db_file_path.clone();
        let table_name = self.table_name.clone();

        tokio::task::spawn_blocking(move || {
            let db = Database::open(db_file_path)?;

            let write_txn = db.begin_write()?;

            {
                let table_name: TableDefinition<'_, &str, Vec<u8>> =
                    TableDefinition::new(&table_name);

                let mut table = write_txn.open_table(table_name)?;
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
        let table_name = self.table_name.clone();

        let res = tokio::task::spawn_blocking(move || {
            let db = Database::open(db_file_path)?;

            let write_txn = db.begin_write()?;

            let res = {
                let table_name: TableDefinition<'_, &str, Vec<u8>> =
                    TableDefinition::new(&table_name);

                let mut table = write_txn.open_table(table_name)?;
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

    async fn set_string(db: Arc<LocalKvDbRedb>, k: String, v: String) {
        db.set_string_value(k.clone(), v.clone()).await.unwrap();
    }

    let db_file = cargo_target_level_filename!("local_kvdb_smoke");

    let db = Arc::new(
        LocalKvDbRedb::try_new(db_file.clone(), "MAIN1".to_string())
            .await
            .unwrap(),
    );
    let test_raw_key = "test".to_string();
    let test_raw_value = vec![123];

    let test_string_key = "k".to_string();
    let test_string_value = "v".to_string();

    set_string(
        db.clone(),
        test_string_key.clone(),
        test_string_value.clone(),
    )
    .await;

    db.set_value(test_raw_key.clone(), test_raw_value.clone())
        .await
        .unwrap();

    assert_eq!(
        db.get_value(test_raw_key.clone()).await.unwrap(),
        Some(test_raw_value.clone())
    );

    assert_eq!(
        db.get_string_value(test_string_key.clone()).await.unwrap(),
        Some(test_string_value.clone())
    );

    // same db instance, but with another table
    let db2 = Arc::new(
        LocalKvDbRedb::try_new(db_file, "MAIN2".to_string())
            .await
            .unwrap(),
    );

    let test_raw_key2 = "test1".to_string();
    let test_raw_value2 = vec![4, 5, 6];

    db2.set_value(test_raw_key2.clone(), test_raw_value2.clone())
        .await
        .unwrap();

    assert_eq!(
        db2.get_value(test_raw_key2.clone()).await.unwrap(),
        Some(test_raw_value2.clone())
    );

    assert_eq!(
        db.get_value(test_raw_key.clone()).await.unwrap(),
        Some(test_raw_value.clone())
    );

    assert_eq!(
        db2.del_value(test_raw_key2.clone()).await.unwrap(),
        Some(test_raw_value2.clone())
    );

    assert_eq!(
        db.del_value(test_raw_key.clone()).await.unwrap(),
        Some(test_raw_value.clone())
    );

    let one = ("asd/1".to_string(), vec![1]);
    let two = ("asd/2".to_string(), vec![2]);
    let three = ("asd/3".to_string(), vec![3]);

    // filter test
    db.set_value(one.0.clone(), one.1.clone()).await.unwrap();
    db.set_value(two.0.clone(), two.1.clone()).await.unwrap();
    db.set_value(three.0.clone(), three.1.clone())
        .await
        .unwrap();

    let res = db
        .all_values(Box::new(|k| k.starts_with("asd/")))
        .await
        .unwrap();

    assert_eq!(vec![one, two, three], res);
}
