use super::node::MdnAgentProviderNodeWillowImpl;
use crate::{
    error::MeeDataSyncResult,
    mdn::common::store::{
        data_entry_path_from_key_components, key_components, KeyComponents,
        MdnAgentDataNodeKvStore, ReadDataRecord,
    },
};
use async_trait::async_trait;
use futures::stream::BoxStream;
use iroh_willow::proto::data_model::{Entry, NamespaceId, Path};

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
    async fn all_values_filter(
        &self,
        filter_fn: Box<dyn for<'a> Fn(&'a Entry) -> bool + Send + Sync + 'static>,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        self.all_values_filter(filter_fn).await
    }
    async fn remove_entries(&self, key: &str) -> MeeDataSyncResult<Vec<bool>> {
        self.remove_entries(key).await
    }
}
