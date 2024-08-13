use super::agent_data_node::MdnAgentDataNodeWillowImpl;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::utils::path_from_bytes_slice,
};
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
    fn key_components(&self, key: &str) -> MeeDataSyncResult<KeyComponents>;

    async fn set_value(&self, key: &str, value: Vec<u8>) -> MeeDataSyncResult;

    async fn del_value(&self, key: &str) -> MeeDataSyncResult;

    /// Asynchronously iterates over the whole store records
    async fn get_all_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;

    /// Asynchronously iterates over the records for provided user ID
    async fn get_values_stream_by_user(
        &self,
        user_id: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;

    /// Asynchronously iterates over the records for provided attribute name
    async fn get_values_stream_by_attr(
        &self,
        attribute_name: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;
}

#[async_trait]
impl MdnAgentDataNodeKvStore for MdnAgentDataNodeWillowImpl {
    fn key_components_splitter() -> &'static str {
        "/"
    }
    fn key_components(&self, key: &str) -> MeeDataSyncResult<KeyComponents> {
        let components = key
            .split(Self::key_components_splitter())
            .collect::<Vec<_>>();

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

    async fn set_value(&self, key: &str, value: Vec<u8>) -> MeeDataSyncResult {
        let path = self.make_entry_path_from_key_components(self.key_components(key)?)?;

        self.willow_peer
            .willow_data_manager
            .insert_entry(self.own_data_namespace_id, path, value)
            .await?;

        Ok(())
    }

    async fn del_value(&self, key: &str) -> MeeDataSyncResult {
        todo!()
    }

    async fn get_values_stream_by_user(
        &self,
        user_id: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let user_prefix = path_from_bytes_slice(&[user_id.as_bytes()])?;

        let res = self
            .all_values_with_entry_filter(move |e| user_prefix.is_prefix_of(e.path()))
            .await?;

        Ok(res)
    }

    async fn get_values_stream_by_attr(
        &self,
        attribute_name: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let attribute_name = attribute_name.to_string();

        let res = self
            .all_values_with_entry_filter(move |e| {
                let attribute_name_component = e.path().get_component(1);
                if let Some(attr) =
                    attribute_name_component.and_then(|c| String::from_utf8(c.to_vec()).ok())
                {
                    attr == attribute_name
                } else {
                    false
                }
            })
            .await?;

        Ok(res)
    }

    async fn get_all_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let res = self.all_values_with_entry_filter(|_| true).await?;

        Ok(res)
    }
}
