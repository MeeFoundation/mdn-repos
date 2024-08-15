use super::namespace::{NamespaceStoreInMemory, NamespaceStoreManager};
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    mdn::{
        node::{MdnAgentDataNodeDelegation, MdnAgentDataNodeNetwork, MdnAgentDataNodeUser},
        store::{
            FullPathAttribute, KeyComponents, MdnAgentDataNodeKvStore, ReadDataRecord,
            ShortPathAttribute,
        },
    },
    willow::{
        peer::{delegation_manager::ImportCapabilitiesFromRemotePeer, WillowPeer},
        utils::path_from_bytes_slice,
    },
};
use async_trait::async_trait;
use futures::{stream::BoxStream, Stream, StreamExt, TryStreamExt};
use iroh_net::{ticket::NodeTicket, NodeAddr};
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo},
    proto::{
        data_model::{Entry, Path},
        grouping::Range3d,
        keys::UserId,
        meadowcap::AccessMode,
    },
    session::intents::IntentHandle,
};
use std::{collections::HashSet, sync::Arc};

#[async_trait]
impl MdnAgentDataNodeNetwork for MdnAgentDataNodeWillowImpl {
    async fn network_node_ticket(&self) -> MeeDataSyncResult<NodeTicket> {
        self.willow_peer
            .willow_network_manager
            .iroh_node_ticket()
            .await
    }
    async fn network_node_addr(&self) -> MeeDataSyncResult<NodeAddr> {
        self.willow_peer
            .willow_network_manager
            .iroh_node_addr()
            .await
    }
    fn add_remote_peer(&self, node_addr: NodeAddr) -> MeeDataSyncResult {
        self.willow_peer
            .willow_network_manager
            .add_remote_peer(node_addr)
    }
}

#[async_trait]
impl MdnAgentDataNodeDelegation for MdnAgentDataNodeWillowImpl {
    async fn import_capabilities_from_remote_peer(
        &self,
        caps: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle> {
        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps)
            .await
    }
    async fn delegate_capabilities(
        &self,
        access_mode: AccessMode,
        to: DelegateTo,
    ) -> MeeDataSyncResult<Vec<CapabilityPack>> {
        self.willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(
                    self.ns_store_manager
                        .store
                        .get_agent_node_data_ns()
                        .await?
                        .ok_or_else(MeeDataSyncErr::missing_agent_node_data_namespace)?
                        .0
                        .clone(),
                ),
                access_mode,
                to,
            )
            .await
    }
}

#[async_trait]
impl MdnAgentDataNodeUser for MdnAgentDataNodeWillowImpl {
    async fn user_id(&self) -> MeeDataSyncResult<UserId> {
        self.willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await
    }
}

#[derive(Clone)]
pub struct MdnAgentDataNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub(crate) ns_store_manager: NamespaceStoreManager,
}

impl MdnAgentDataNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        Ok(Self {
            ns_store_manager: NamespaceStoreManager::new(
                Arc::new(NamespaceStoreInMemory::new()),
                willow_peer.willow_namespace_manager.clone(),
            )
            .await?,
            willow_peer,
        })
    }
    pub fn make_entry_path_from_key_components(
        &self,
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
    pub async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        let comps = self.key_components(key)?;
        let path = self.make_entry_path_from_key_components(comps)?;

        let entries = self
            .all_entries_filter(move |e| e.path() == &path)
            .await?
            .collect::<Vec<_>>()
            .await;

        let res = self
            .willow_peer
            .willow_data_manager
            .remove_entries(entries)
            .await?;

        Ok(res)
    }
    pub async fn all_entries_filter<F>(
        &self,
        filter_entry_fn: F,
    ) -> MeeDataSyncResult<impl Stream<Item = Entry>>
    where
        F: Fn(&Entry) -> bool + Send + Sync + 'static,
    {
        let range = Range3d::new_full();

        let entries = self
            .entries_for_range(range)
            .await?
            .try_filter(move |e| {
                let pred = filter_entry_fn(e);

                async move { pred }
            })
            .filter_map(|record| async {
                match record {
                    Ok(record) => Some(record),
                    Err(e) => {
                        log::error!("Error processing entry: {e}");
                        None
                    }
                }
            });

        Ok(entries)
    }

    pub async fn entries_for_range(
        &self,
        range: Range3d,
    ) -> MeeDataSyncResult<impl Stream<Item = MeeDataSyncResult<Entry>>> {
        let own_data_namespace_id = self
            .ns_store_manager
            .store
            .get_agent_node_data_ns()
            .await?
            .ok_or_else(MeeDataSyncErr::missing_agent_node_data_namespace)?
            .0;

        let owned_entries = self
            .willow_peer
            .willow_data_manager
            .get_entries_stream(own_data_namespace_id, range.clone())
            .await?;

        let caps_ns = self
            .willow_peer
            .willow_delegation_manager
            .list_read_caps()
            .await?
            .into_iter()
            .filter_map(|c| {
                let ns = c.namespace();

                if ns != own_data_namespace_id {
                    Some(ns)
                } else {
                    None
                }
            });

        let mut caps_entries = HashSet::new();

        for ns in caps_ns {
            let delegated_entries: Vec<_> = self
                .willow_peer
                .willow_data_manager
                .get_entries_stream(ns.clone(), range.clone())
                .await?
                .try_collect()
                .await?;

            // TODO deduplicate without materialization
            caps_entries.extend(delegated_entries);
        }

        let cap_entries_stream = futures::stream::iter(caps_entries.into_iter().map(Ok));

        let entries = tokio_stream::StreamExt::merge(owned_entries, cap_entries_stream);

        Ok(entries)
    }
    pub async fn all_values_filter<F>(
        &self,
        filter_entry_fn: F,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>>
    where
        F: Fn(&Entry) -> bool + Send + Sync + 'static,
    {
        let range = Range3d::new_full();

        let entries = self.entries_for_range(range).await?;

        let records = entries
            .try_filter(move |e| {
                // log::warn!(
                //     "p: {} ns: {} ss: {}",
                //     display_path(e.path()),
                //     e.namespace_id(),
                //     e.subspace_id()
                // );

                let pred = filter_entry_fn(e);

                async move { pred }
            })
            .and_then(|entry| {
                let willow_peer = self.willow_peer.clone();

                async move {
                    let path = entry.path().clone();
                    let payload = willow_peer
                        .willow_data_manager
                        .read_entry_payload(entry.clone())
                        .await?;

                    let record = if let Some(payload) = payload {
                        if payload.is_empty() {
                            return Ok(None);
                        }

                        let key = path
                            .components()
                            .into_iter()
                            .filter_map(|p| match String::from_utf8(p.to_vec()) {
                                Ok(v) => Some(v),
                                Err(e) => {
                                    log::error!("Error stringifying willow path: {e}");
                                    None
                                }
                            })
                            .collect::<Vec<_>>()
                            .join(<Self as MdnAgentDataNodeKvStore>::key_components_splitter());

                        Some(ReadDataRecord {
                            key,
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
