use super::user_manager::WillowUserManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::{node::WillowNode, utils::empty_entry_payload},
};
use bytes::Bytes;
use futures::{future::join_all, Stream, StreamExt, TryStreamExt};
use iroh_willow::{
    form::{EntryForm, SubspaceForm},
    proto::{
        data_model::{Entry, Path},
        grouping::Range3d,
        keys::{NamespaceId, UserId},
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
    // TODO change entry return value
    pub async fn insert_entry(
        &self,
        namespace_id: NamespaceId,
        path: Path,
        bytes: impl Into<Bytes>,
    ) -> MeeDataSyncResult<(Entry, bool)> {
        let entry = EntryForm::new_bytes(namespace_id, path, bytes);
        let user = self.willow_user_manager.get_active_user_profile().await?;

        let (e, i) = self.willow_node.engine.insert_entry(entry, user).await?;

        Ok((e.entry().clone(), i))
    }
    pub async fn get_entries_stream(
        &self,
        namespace: NamespaceId,
        range: Range3d,
    ) -> MeeDataSyncResult<impl Stream<Item = MeeDataSyncResult<Entry>>> {
        Ok(self
            .willow_node
            .engine
            .get_entries(namespace, range)
            .await?
            .map(|en| en.map(|e| e.entry().clone()))
            .map_err(MeeDataSyncErr::from))
    }
    pub async fn get_entries(
        &self,
        namespace: NamespaceId,
        range: Range3d,
    ) -> MeeDataSyncResult<Vec<Entry>> {
        Ok(self
            .get_entries_stream(namespace, range)
            .await?
            .try_collect()
            .await?)
    }
    pub async fn remove_entries_completely(
        &self,
        entries: Vec<Entry>,
    ) -> MeeDataSyncResult<Vec<bool>> {
        Ok(self.willow_node.engine.remove_entries(entries).await?)
    }
    pub async fn remove_entries_softly(&self, entries: Vec<Entry>) -> MeeDataSyncResult<Vec<bool>> {
        let user = self.willow_user_manager.get_active_user_profile().await?;

        // TODO willow-iroh still has bug with empty payload
        let res = entries.into_iter().map(|entry| async move {
            let entry = EntryForm::new_bytes(
                *entry.namespace_id(),
                entry.path().clone(),
                empty_entry_payload().to_vec(),
            );

            let res = self.willow_node.engine.insert_entry(entry, user).await;

            match res {
                Ok(res) => res.1,
                Err(e) => {
                    log::error!("Error removing entry: {e}");
                    false
                }
            }
        });

        let res = join_all(res).await.into_iter().collect::<Vec<_>>();

        Ok(res)
    }
    pub async fn remove_entries_softly_for_subspace(
        &self,
        entries: Vec<Entry>,
        user_id: UserId,
    ) -> MeeDataSyncResult<Vec<bool>> {
        let user = self.willow_user_manager.get_active_user_profile().await?;

        // TODO willow-iroh still has bug with empty payload
        let res = entries.into_iter().map(|entry| async move {
            let mut entry = EntryForm::new_bytes(
                *entry.namespace_id(),
                entry.path().clone(),
                empty_entry_payload().to_vec(),
            );

            entry.subspace_id = SubspaceForm::Exact(user_id);

            let res = self.willow_node.engine.insert_entry(entry, user).await;

            match res {
                Ok(res) => res.1,
                Err(e) => {
                    log::error!("Error removing entry: {e}");
                    false
                }
            }
        });

        let res = join_all(res).await.into_iter().collect::<Vec<_>>();

        Ok(res)
    }
    pub async fn read_entry_payload(&self, entry: Entry) -> MeeDataSyncResult<Option<Bytes>> {
        Ok(self.willow_node.engine.read_payload(entry).await?)
    }
}
