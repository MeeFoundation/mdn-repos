use super::node::MdnAgentProviderNodeWillowImpl;
use crate::{
    async_move,
    error::MeeDataSyncResult,
    mdn::common::store::{
        data_entry_path_from_key_components, key_components, KeyComponents, MdnAgentDataNodeKvStore,
    },
    utils::try_stream_dedup,
    willow::utils::empty_entry_payload,
};
use async_trait::async_trait;
use futures::{stream::BoxStream, StreamExt, TryStreamExt};
use iroh_willow::proto::{
    data_model::{Entry, NamespaceId, Path},
    grouping::Range3d,
};
use mee_macro_utils::let_clone;

#[async_trait]
impl MdnAgentDataNodeKvStore for MdnAgentProviderNodeWillowImpl {
    type KeyComps = KeyComponents;

    fn data_entry_path_from_key_components(
        &self,
        key_components: Self::KeyComps,
    ) -> MeeDataSyncResult<Path> {
        data_entry_path_from_key_components(key_components)
    }
    fn key_components(&self, key: &str) -> MeeDataSyncResult<Self::KeyComps> {
        key_components(key)
    }

    fn willow_peer(&self) -> crate::willow::peer::WillowPeer {
        self.willow_peer.clone()
    }
    async fn data_ns(&self) -> MeeDataSyncResult<NamespaceId> {
        Ok(self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0)
    }
    async fn data_entries(
        &self,
        range: Range3d,
    ) -> MeeDataSyncResult<BoxStream<'_, MeeDataSyncResult<Entry>>> {
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

        // TODO uncomment
        // let search_schemas_ns = self.mdn_ns_store_manager.get_search_schemas_ns().await?.0;

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
            .filter_map(move |c| {
                // log::warn!("cap: {c:#?}");

                let ns = c.namespace();

                if ns != own_revoke_list_caps
                    // && ns != search_schemas_ns
                    && ns != own_data_namespace_id
                    && !others_revoke_list_caps
                        .iter()
                        .any(|c| c.revocation_ns == ns)
                    && data_owner_revoke_list_caps
                        .map(|dns| ns != dns.0)
                        .unwrap_or(true)
                {
                    Some(ns)
                } else {
                    None
                }
            });

        let cap_entries_stream = futures::stream::iter(caps_ns)
            .map(MeeDataSyncResult::Ok)
            .and_then(move |ns| {
                let_clone!(range);

                async move {
                    let delegated_entries = self
                        .willow_peer
                        .willow_data_manager
                        .get_entries_stream(ns, range)
                        .await?;

                    MeeDataSyncResult::Ok(delegated_entries)
                }
            })
            .try_flatten();

        let cap_entries_stream = try_stream_dedup(cap_entries_stream);

        let entries = tokio_stream::StreamExt::merge(owned_entries, cap_entries_stream);

        Ok(entries.boxed())
    }
    async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        let comps = key_components(key)?;
        let path = data_entry_path_from_key_components(comps)?;
        let range = Range3d::new_full();

        let entries: Vec<_> = self
            .data_entries(range)
            .await?
            .try_filter(|e| async_move! {e.path() == &path})
            .try_collect()
            .await?;

        let res = self
            .willow_peer
            .willow_data_manager
            .remove_entries_softly(entries)
            .await?;

        Ok(res)
    }

    async fn post_set_value(&self, key: &str, _value: Vec<u8>) -> MeeDataSyncResult {
        let path = self.data_entry_path_from_key_components(self.key_components(key)?)?;

        self.willow_peer()
            .willow_data_manager
            .insert_entry(
                self.mdn_ns_store_manager.get_search_schemas_ns().await?.0,
                path,
                empty_entry_payload().to_vec(),
            )
            .await?;

        Ok(())
    }

    async fn post_del_value(&self, key: &str) -> MeeDataSyncResult {
        let path = self.data_entry_path_from_key_components(self.key_components(key)?)?;

        let entries = self
            .willow_peer
            .willow_data_manager
            .get_entries_stream(
                self.mdn_ns_store_manager.get_search_schemas_ns().await?.0,
                Range3d::new_full(),
            )
            .await?
            .try_filter(|e| async_move! { e.path() == &path })
            .try_collect()
            .await?;

        let _res = self
            .willow_peer
            .willow_data_manager
            .remove_entries_softly(entries)
            .await?;

        Ok(())
    }
}
