use super::agent_data_node::MdnAgentDataNodeWillowImpl;
use crate::error::{MeeDataSyncErr, MeeDataSyncResult};
use async_trait::async_trait;
use futures::{stream::BoxStream, StreamExt, TryStreamExt};
use iroh_willow::proto::{
    grouping::{Range, RangeEnd, ThreeDRange},
    willow::Path,
};
use std::collections::HashSet;

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
    async fn get_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>;

    // /// Asynchronously iterates over the records for provided user ID
    // async fn get_values_stream_by_user(
    //     &self,
    //     user_id: &str,
    // ) -> impl Stream<Item = MeeDataSyncResult<(String, Vec<u8>)>>;

    // /// Asynchronously iterates over the records for provided attribute name
    // async fn get_values_stream_by_attr(
    //     &self,
    //     attr: &str,
    // ) -> impl Stream<Item = MeeDataSyncResult<(String, Vec<u8>)>>;
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

        let path_bytes = path
            .components()
            .iter()
            .map(|p| p.as_ref())
            .collect::<Vec<_>>();

        self.willow_peer
            .willow_data_manager
            .insert_entry(self.own_data_namespace_id, &path_bytes, value)
            .await?;

        Ok(())
    }

    async fn del_value(&self, key: &str) -> MeeDataSyncResult {
        todo!()
    }

    async fn get_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let mut range = ThreeDRange::full();

        let query_path = Path::new(&[Self::DATA_NAMESPACE_PATH_PREFIX.as_bytes()])?;

        // TODO wait for fix of the path end range calculation
        // range.paths = Range::new(query_path.clone(), RangeEnd::Closed(query_path.clone()));
        range.paths = Range::new(query_path.clone(), RangeEnd::Open);

        let owned_entries = self
            .willow_peer
            .willow_data_manager
            .filter_entries_stream(self.own_data_namespace_id, range.clone(), {
                let query_path = query_path.clone();

                move |e| query_path.is_prefix_of(&e.path)
            })
            .await?;

        let caps_ns = self
            .willow_peer
            .willow_delegation_manager
            .list_read_caps()
            .await?
            .into_iter()
            .filter_map(|c| {
                let ns = c.namespace();

                if ns != self.own_data_namespace_id {
                    Some(ns)
                } else {
                    None
                }
            });

        let mut caps_entries = HashSet::new();

        for ns in caps_ns {
            let delegated_entries = self
                .willow_peer
                .willow_data_manager
                .filter_entries(ns.clone(), ThreeDRange::full(), |e| {
                    query_path.is_prefix_of(&e.path)
                })
                .await?;

            caps_entries.extend(delegated_entries);
        }

        let cap_entries_stream = futures::stream::iter(caps_entries.into_iter().map(Ok));

        let entries = tokio_stream::StreamExt::merge(owned_entries, cap_entries_stream);

        let records = entries
            .and_then(|entry| {
                let willow_peer = self.willow_peer.clone();

                async move {
                    let path = entry.path.clone();
                    let payload = willow_peer
                        .willow_data_manager
                        .read_entry_payload(entry.clone())
                        .await?;

                    let record = if let Some(payload) = payload {
                        Some(ReadDataRecord {
                            key: path
                                .into_iter()
                                .filter_map(|p| match String::from_utf8(p.to_vec()) {
                                    Ok(v) => Some(v),
                                    Err(e) => {
                                        log::error!("Error stringifying willow path: {e}");
                                        None
                                    }
                                })
                                .collect::<Vec<_>>()
                                .join(Self::key_components_splitter()),
                            value: payload.to_vec(),
                        })
                    } else {
                        None
                    };

                    Ok(record) as MeeDataSyncResult<Option<ReadDataRecord>>
                }
            })
            .filter_map(|record| async {
                match record {
                    Ok(record) => record,
                    Err(e) => {
                        log::error!("Error processing entry: {e}");
                        None
                    }
                }
            });

        Ok(records.boxed())
    }
}
