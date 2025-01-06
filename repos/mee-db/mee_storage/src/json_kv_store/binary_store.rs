#![allow(unused)]
use core::fmt::Debug;
use std::sync::Arc;
use thiserror::Error;
pub type KVStore = Arc<dyn BinaryKVStore + Send + Sync + 'static>;
pub type KV = (String, Vec<u8>);
pub type KVStream = futures::stream::BoxStream<'static, KV>;
pub type KeysStream = futures::stream::BoxStream<'static, String>;
pub type BinaryStore = Arc<dyn BinaryKVStore + Send + Sync + 'static>;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Write error: failed to set key '{0}': {1}")]
    WriteError(String, String),
    #[error("Read error: failed to get key '{0}': {1}")]
    ReadError(String, String),
}

pub type Result<T> = std::result::Result<T, Error>;

#[async_trait::async_trait]
pub trait BinaryKVStore: Debug {
    #[allow(unused)]
    async fn insert(&self, path: String, value: Vec<u8>) -> Result<()>;
    async fn insert_many(&self, batch: Vec<KV>) -> Result<()>;
    async fn count(&self, path: String) -> Result<Option<usize>>;
    async fn range(&self, path: String) -> Result<KVStream>;

    async fn keys(&self, path: String) -> Result<KeysStream>;

    async fn delete(&self, path: &str) -> Result<()>;
    #[allow(unused)]
    async fn get(&self, path: &str) -> Result<Option<Vec<u8>>>;

    async fn next_key(&self, path: String) -> Result<Option<String>>;
}

pub const PATH_SEPARATOR: char = '/';
pub const PATH_PREFIX: char = '@';
