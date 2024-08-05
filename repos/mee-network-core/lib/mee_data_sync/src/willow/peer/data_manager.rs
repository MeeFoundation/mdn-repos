use super::user_manager::WillowUserManager;
use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use bytes::Bytes;
use futures::{Stream, TryStreamExt};
use iroh_willow::{
    form::EntryForm,
    proto::{
        grouping::ThreeDRange,
        keys::NamespaceId,
        willow::{Entry, Path},
    },
};

#[derive(Clone)]
pub struct WillowDataManager {
    willow_node: WillowNode,
    willow_user_manager: WillowUserManager,
}

impl WillowDataManager {
    pub fn new(willow_node: WillowNode, willow_user_manager: WillowUserManager) -> Self {
        Self {
            willow_node,
            willow_user_manager,
        }
    }
    pub async fn insert_entry(
        &self,
        namespace_id: NamespaceId,
        path: &[&[u8]],
        bytes: impl Into<Bytes>,
    ) -> MeeDataSyncResult<(Entry, bool)> {
        let path = Path::new(path)?;
        let entry = EntryForm::new_bytes(namespace_id, path, bytes);
        let user = self.willow_user_manager.get_active_user_profile().await?;

        let res = self.willow_node.engine.insert(entry, user).await?;

        Ok(res)
    }
    pub async fn get_entries_stream(
        &self,
        namespace: NamespaceId,
        range: ThreeDRange,
    ) -> MeeDataSyncResult<impl Stream<Item = anyhow::Result<Entry>>> {
        Ok(self
            .willow_node
            .engine
            .get_entries(namespace, range)
            .await?)
    }
    pub async fn get_entries(
        &self,
        namespace: NamespaceId,
        range: ThreeDRange,
    ) -> MeeDataSyncResult<Vec<Entry>> {
        Ok(self
            .get_entries_stream(namespace, range)
            .await?
            .try_collect()
            .await?)
    }
    pub async fn read_entry_payload(&self, entry: Entry) -> MeeDataSyncResult<Option<Bytes>> {
        Ok(self.willow_node.engine.read_payload(entry).await?)
    }
}
