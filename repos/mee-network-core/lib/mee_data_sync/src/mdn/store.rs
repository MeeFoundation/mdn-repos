use crate::error::MeeDataSyncResult;
use async_trait::async_trait;
use futures::stream::BoxStream;

/// `{user_id}/{root_attribute}/{root_attribute_id}/{sub_attribute}`
pub struct FullPathAttribute {
    pub user_id: String,
    pub attribute_name: String,
    pub attribute_instance_id: String,
    pub sub_attribute_name: String,
}

/// `{user_id}/{root_attribute}`
pub struct ShortPathAttribute {
    pub user_id: String,
    pub attribute_name: String,
}

pub enum KeyComponents {
    FullPathAttribute(FullPathAttribute),
    ShortPathAttribute(ShortPathAttribute),
}

#[derive(Debug)]
pub struct ReadDataRecord {
    pub key: String,
    pub value: Vec<u8>,
}

#[async_trait]
pub trait MdnAgentDataNodeKvStore {
    fn key_components_splitter() -> &'static str;
    /// Extracts key parts (user, attribute name, sub-attribute name, etc.) from a key.
    fn key_components(key: &str) -> MeeDataSyncResult<KeyComponents>;

    async fn set_value(&self, key: &str, value: Vec<u8>) -> MeeDataSyncResult;

    /// Delete value by key (full path is required!)
    async fn del_value(&self, key: &str) -> MeeDataSyncResult<bool>;

    /// Asynchronously iterates over the whole store records
    async fn get_all_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;

    /// Asynchronously iterates over the records for the provided user ID
    async fn get_values_stream_by_user(
        &self,
        user_id: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;

    /// Asynchronously iterates over the records for the provided attribute name
    async fn get_values_stream_by_attr(
        &self,
        attribute_name: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;
}
