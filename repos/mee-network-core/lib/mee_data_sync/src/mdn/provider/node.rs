use super::{
    caps::{MdnProviderCapabilityInMemoryStore, MdnProviderCapabilityManager},
    delegation::{manager::MdnProviderDelegationManager, MdnProviderDelegationManagerImpl},
    namespace::{MdnProviderNamespaceStoreInMemory, MdnProviderNamespaceStoreManager},
};
use crate::{
    error::MeeDataSyncResult,
    mdn::traits::{
        network::MdnAgentDataNodeNetworkOps,
        node::MdnAgentProviderNode,
        store::{
            data_entry_path_from_key_components, key_components, ReadDataRecord,
            KEY_COMPONENTS_SPLITTER,
        },
        user::MdnAgentDataNodeUserOps,
    },
    willow::{peer::WillowPeer, utils::is_empty_entry_payload},
};
use async_trait::async_trait;
use futures::{stream::BoxStream, Stream, StreamExt, TryStreamExt};
use iroh_willow::proto::{data_model::Entry, grouping::Range3d};
use std::{collections::HashSet, sync::Arc};
use tokio::task::JoinHandle;

// #[derive(Clone)]
pub struct MdnAgentProviderNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
    pub(crate) mdn_ns_store_manager: MdnProviderNamespaceStoreManager,
    mdn_delegation_manager: Arc<MdnProviderDelegationManagerImpl>,
    background_jobs: Arc<Vec<JoinHandle<()>>>,
}

impl Drop for MdnAgentProviderNodeWillowImpl {
    fn drop(&mut self) {
        for job in self.background_jobs.iter() {
            job.abort();
        }
    }
}

impl MdnAgentProviderNode for MdnAgentProviderNodeWillowImpl {
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnProviderDelegationManager + Send + Sync> {
        self.mdn_delegation_manager.clone()
    }
}

impl MdnAgentProviderNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer) -> MeeDataSyncResult<Self> {
        let mdn_ns_store_manager = MdnProviderNamespaceStoreManager::new(
            Arc::new(MdnProviderNamespaceStoreInMemory::new()),
            willow_peer.willow_namespace_manager.clone(),
        )
        .await?;

        let mdn_provider_capability_manager =
            MdnProviderCapabilityManager::new(Arc::new(MdnProviderCapabilityInMemoryStore::new()));

        let mdn_delegation_manager = MdnProviderDelegationManagerImpl::new(
            willow_peer.clone(),
            mdn_ns_store_manager.clone(),
            mdn_provider_capability_manager,
        )
        .await?;

        let background_jobs = mdn_delegation_manager.clone().run_background_jobs();

        Ok(Self {
            background_jobs: Arc::new(background_jobs),
            mdn_delegation_manager: Arc::new(mdn_delegation_manager),
            mdn_ns_store_manager,
            willow_peer,
        })
    }

    pub async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        let comps = key_components(key)?;
        let path = data_entry_path_from_key_components(comps)?;

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

        let data_owner_revoke_list_caps = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?;

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
                    && !others_revoke_list_caps
                        .iter()
                        .any(|c| c.revocation_ns == ns)
                    && data_owner_revoke_list_caps
                        .map(|dns| ns != dns.0)
                        .unwrap_or(false)
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
    pub async fn all_values_filter(
        &self,
        filter_entry_fn: Box<dyn Fn(&Entry) -> bool + Send + Sync + 'static>,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
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
                        if is_empty_entry_payload(&payload) {
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
                            .join(KEY_COMPONENTS_SPLITTER);

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

#[async_trait]
impl MdnAgentDataNodeNetworkOps for MdnAgentProviderNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}

#[async_trait]
impl MdnAgentDataNodeUserOps for MdnAgentProviderNodeWillowImpl {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }
}
