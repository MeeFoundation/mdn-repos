use super::user_manager::WillowUserManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::{node::WillowNode, utils::deleted_entry_payload},
};
use bytes::Bytes;
use futures::{Stream, StreamExt, TryStreamExt};
use iroh_blobs::store::{bao_tree::io::fsm::AsyncSliceReader, Map, MapEntry};
use iroh_willow::{
    form::{EntryForm, SubspaceForm},
    proto::{
        data_model::{Entry, Path},
        grouping::Range3d,
        keys::{NamespaceId, UserId},
    },
};
use mee_async_utils::local_spawn::{LocalSpawner, TaskRunner};
use tokio::sync::oneshot::{self};

pub enum WillowDataManagerLocalTask {
    ReadEntryPayload {
        willow_node: WillowNode,
        entry: Entry,
        reply_tx: oneshot::Sender<MeeDataSyncResult<Option<Bytes>>>,
    },
}

#[async_trait::async_trait(?Send)]
impl TaskRunner for WillowDataManagerLocalTask {
    async fn run(self) {
        match self {
            WillowDataManagerLocalTask::ReadEntryPayload {
                willow_node,
                entry,
                reply_tx,
            } => {
                let res = async move {
                    let blob_entry = willow_node.blobs.get(&entry.payload_digest().0).await?;

                    let data = if let Some(blob_entry) = blob_entry {
                        let mut reader = blob_entry.data_reader().await?;
                        let data = reader
                            .read_at(0, entry.payload_length().try_into()?)
                            .await?;

                        Some(data)
                    } else {
                        None
                    };

                    MeeDataSyncResult::Ok(data)
                };

                if reply_tx.send(res.await).is_err() {
                    log::error!("Read entry payload channel send error");
                }
            }
        }
    }
}

#[derive(Clone)]
pub struct WillowDataManager {
    willow_node: WillowNode,
    willow_user_manager: WillowUserManager,
    local_spawner: LocalSpawner<WillowDataManagerLocalTask>,
}

impl WillowDataManager {
    pub fn try_new(
        willow_node: WillowNode,
        willow_user_manager: WillowUserManager,
    ) -> MeeDataSyncResult<Self> {
        Ok(Self {
            willow_node,
            willow_user_manager,
            local_spawner: LocalSpawner::try_new()?,
        })
    }
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

        let res = futures::stream::iter(entries)
            .map(MeeDataSyncResult::Ok)
            .and_then(|entry| async move {
                let entry = EntryForm::new_bytes(
                    *entry.namespace_id(),
                    entry.path().clone(),
                    deleted_entry_payload().to_vec(),
                );

                let res = self.willow_node.engine.insert_entry(entry, user).await?;

                Ok(res.1)
            })
            .try_collect()
            .await?;

        Ok(res)
    }
    pub async fn remove_entries_softly_for_subspace(
        &self,
        entries: Vec<Entry>,
        user_id: UserId,
    ) -> MeeDataSyncResult<Vec<bool>> {
        let user = self.willow_user_manager.get_active_user_profile().await?;

        let res = futures::stream::iter(entries)
            .map(MeeDataSyncResult::Ok)
            .and_then(|entry| async move {
                let mut entry = EntryForm::new_bytes(
                    *entry.namespace_id(),
                    entry.path().clone(),
                    deleted_entry_payload().to_vec(),
                );

                entry.subspace_id = SubspaceForm::Exact(user_id);

                let res = self.willow_node.engine.insert_entry(entry, user).await?;

                MeeDataSyncResult::Ok(res.1)
            })
            .try_collect()
            .await?;

        Ok(res)
    }
    pub async fn read_entry_payload(&self, entry: Entry) -> MeeDataSyncResult<Option<Bytes>> {
        let (reply_tx, reply_rx) = oneshot::channel();

        self.local_spawner
            .spawn(WillowDataManagerLocalTask::ReadEntryPayload {
                willow_node: self.willow_node.clone(),
                entry,
                reply_tx,
            })?;

        Ok(reply_rx
            .await
            .map_err(|_| anyhow::anyhow!("Read entry payload receiving channel error"))??)
    }
}
