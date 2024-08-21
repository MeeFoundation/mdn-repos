use crate::error::{MeeDataSyncErr, MeeDataSyncResult};
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

pub const KEY_COMPONENTS_SPLITTER: &str = "/";

/// Extracts key parts (user, attribute name, sub-attribute name, etc.) from a key.
pub fn key_components(key: &str) -> MeeDataSyncResult<KeyComponents> {
    let components = key.split(KEY_COMPONENTS_SPLITTER).collect::<Vec<_>>();

    let kc = match &components[..] {
        [user_id, attribute_name] => KeyComponents::ShortPathAttribute(ShortPathAttribute {
            user_id: user_id.to_string(),
            attribute_name: attribute_name.to_string(),
        }),
        [user_id, attribute_name, attribute_instance_id, sub_attribute_name] => {
            KeyComponents::FullPathAttribute(FullPathAttribute {
                user_id: user_id.to_string(),
                attribute_name: attribute_name.to_string(),
                attribute_instance_id: attribute_instance_id.to_string(),
                sub_attribute_name: sub_attribute_name.to_string(),
            })
        }
        _ => Err(MeeDataSyncErr::SyncedKvStorage(format!(
            "Error parsing key components: Invalid key: {key}"
        )))?,
    };

    Ok(kc)
}

#[async_trait]
pub trait MdnAgentDataNodeKvStore {
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
