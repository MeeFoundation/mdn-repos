use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::{peer::WillowPeer, utils::path_from_bytes_slice},
};
use async_trait::async_trait;
use futures::stream::BoxStream;
use iroh_willow::proto::data_model::{Entry, NamespaceId, Path};

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

pub fn data_entry_path_from_key_components(
    key_components: KeyComponents,
) -> MeeDataSyncResult<Path> {
    let mut path_components = vec![];

    match key_components {
        KeyComponents::FullPathAttribute(FullPathAttribute {
            user_id,
            attribute_name,
            attribute_instance_id,
            sub_attribute_name,
        }) => {
            path_components.extend(vec![
                user_id,
                attribute_name,
                attribute_instance_id,
                sub_attribute_name,
            ]);
        }
        KeyComponents::ShortPathAttribute(ShortPathAttribute {
            user_id,
            attribute_name,
        }) => {
            path_components.extend(vec![user_id, attribute_name]);
        }
    }

    let path_components = path_components
        .iter()
        .map(String::as_bytes)
        .collect::<Vec<_>>();

    let path = path_from_bytes_slice(&path_components)?;

    Ok(path)
}

#[async_trait]
pub trait MdnAgentDataNodeKvStore {
    fn willow_peer(&self) -> WillowPeer;
    async fn data_ns(&self) -> MeeDataSyncResult<NamespaceId>;
    async fn all_values_filter(
        &self,
        filter_fn: Box<dyn for<'a> Fn(&'a Entry) -> bool + Send + Sync + 'static>,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;
    async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>>;

    async fn set_value(&self, key: &str, value: Vec<u8>) -> MeeDataSyncResult {
        let path = data_entry_path_from_key_components(key_components(key)?)?;

        self.willow_peer()
            .willow_data_manager
            .insert_entry(self.data_ns().await?, path, value)
            .await?;

        Ok(())
    }

    /// Delete value by key (full path is required!)
    async fn del_value(&self, key: &str) -> MeeDataSyncResult<bool> {
        let res = self.remove_entries(key).await?.pop().unwrap_or(false);

        Ok(res)
    }

    /// Asynchronously iterates over the records for the provided user ID
    async fn get_values_stream_by_user(
        &self,
        user_id: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let user_prefix = path_from_bytes_slice(&[user_id.as_bytes()])?;

        let res = self
            .all_values_filter(Box::new(move |e| user_prefix.is_prefix_of(e.path())))
            .await?;

        Ok(res)
    }

    /// Asynchronously iterates over the records for the provided attribute name
    async fn get_values_stream_by_attr(
        &self,
        attribute_name: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let attribute_name = attribute_name.to_string();

        let res = self
            .all_values_filter(Box::new(move |e| {
                let attribute_name_component = e.path().get_component(1);
                if let Some(attr) =
                    attribute_name_component.and_then(|c| String::from_utf8(c.to_vec()).ok())
                {
                    attr == attribute_name
                } else {
                    false
                }
            }))
            .await?;

        Ok(res)
    }

    /// Asynchronously iterates over the whole store records
    async fn get_all_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let res = self.all_values_filter(Box::new(|_| true)).await?;

        Ok(res)
    }
}
