use super::{
    delegation::MdnDelegationManager,
    namespace::{MdnNamespaceStoreManager, NamespaceStoreInMemory},
};
use crate::{
    error::MeeDataSyncResult,
    mdn::store::{
        FullPathAttribute, KeyComponents, MdnAgentDataNodeKvStore, ReadDataRecord,
        ShortPathAttribute,
    },
    willow::{peer::WillowPeer, utils::path_from_bytes_slice},
};
use futures::{stream::BoxStream, Stream, StreamExt, TryStreamExt};
use iroh_willow::proto::{
    data_model::{Entry, Path},
    grouping::Range3d,
};
use std::{collections::HashSet, sync::Arc};
use tokio::task::JoinHandle;

// #[derive(Clone)]
pub struct MdnAgentDataNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub(crate) mdn_ns_store_manager: MdnNamespaceStoreManager,
    pub mdn_delegation_manager: MdnDelegationManager,
    cap_revoke_task: Arc<JoinHandle<()>>,
}

impl Drop for MdnAgentDataNodeWillowImpl {
    fn drop(&mut self) {
        self.cap_revoke_task.abort();
    }
}

impl MdnAgentDataNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let mdn_ns_store_manager = MdnNamespaceStoreManager::new(
            Arc::new(NamespaceStoreInMemory::new()),
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        let mdn_delegation_manager =
            MdnDelegationManager::new(willow_peer.clone(), mdn_ns_store_manager.clone());

        let cap_revoke_taks = mdn_delegation_manager.clone().run_revocation_handler();

        Ok(Self {
            cap_revoke_task: Arc::new(cap_revoke_taks),
            mdn_delegation_manager,
            mdn_ns_store_manager,
            willow_peer,
        })
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
    pub async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        let comps = Self::key_components(key)?;
        let path = Self::data_entry_path_from_key_components(comps)?;

        let entries = self
            .all_data_entries_filter(move |e| e.path() == &path)
            .await?
            .collect::<Vec<_>>()
            .await;

        let res = self
            .willow_peer
            .willow_data_manager
            .remove_entries_softly(entries)
            .await?;

        Ok(res)
    }
    pub async fn all_data_entries_filter<F>(
        &self,
        filter_entry_fn: F,
    ) -> MeeDataSyncResult<impl Stream<Item = Entry>>
    where
        F: Fn(&Entry) -> bool + Send + Sync + 'static,
    {
        let range = Range3d::new_full();

        let entries = self
            .data_entries_for_range(range)
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

    pub async fn data_entries_for_range(
        &self,
        range: Range3d,
    ) -> MeeDataSyncResult<impl Stream<Item = MeeDataSyncResult<Entry>>> {
        let own_data_namespace_id = self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0;
        let own_revoke_list_caps = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;

        let others_revoke_list_caps = self
            .mdn_ns_store_manager
            .get_others_cap_revoke_list_nss()
            .await?;

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
                // log::warn!("cap: {c:#?}");

                let ns = c.namespace();

                if ns != own_revoke_list_caps
                    && ns != own_data_namespace_id
                    && !others_revoke_list_caps.iter().any(|c| c.ns_id == ns)
                {
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

        let entries = self.data_entries_for_range(range).await?;

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
                        if payload.is_empty() || *payload == [0] {
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
