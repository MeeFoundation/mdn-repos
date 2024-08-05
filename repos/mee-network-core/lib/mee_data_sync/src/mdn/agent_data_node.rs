use crate::{error::MeeDataSyncResult, willow::peer::WillowPeer};
use async_trait::async_trait;
use futures::future::join_all;
use iroh_willow::proto::{
    grouping::{Range, RangeEnd, ThreeDRange},
    keys::{NamespaceId, NamespaceKind},
    willow::Path,
};

#[derive(Debug)]
pub struct GetUserDataRecord {
    pub key: String,
    pub value: Vec<u8>,
}

#[async_trait]
pub trait MdnAgentDataNode {
    /// Path/key to user's data root in KV-like storage
    fn user_data_root_path(&self, user_id: &str) -> String;

    async fn get_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
    ) -> MeeDataSyncResult<Vec<GetUserDataRecord>>;

    async fn set_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
        value: Vec<u8>,
    ) -> MeeDataSyncResult;
}

#[derive(Clone)]
pub struct MdnAgentDataNodeWillowImpl {
    willow_peer: WillowPeer,
    agent_holder_id: String,
    namespace_id: NamespaceId,
}

impl MdnAgentDataNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer, agent_holder_id: String) -> MeeDataSyncResult<Self> {
        let namespace_id = willow_peer
            .willow_namespace_manager
            .create_namespace(NamespaceKind::Owned)
            .await?;

        Ok(Self {
            namespace_id,
            willow_peer,
            agent_holder_id,
        })
    }
    fn make_entry_path(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
    ) -> MeeDataSyncResult<Path> {
        let user_data_root_path = self.user_data_root_path(user_id);
        let mut path_components = user_data_root_path.split("/").collect::<Vec<_>>();

        path_components.extend([attribute_name]);

        if !sub_attribute_path.is_empty() {
            path_components.extend(sub_attribute_path);
        }

        let path_components = path_components
            .into_iter()
            .map(|s| s.as_bytes())
            .collect::<Vec<_>>();

        let path = Path::new(&path_components)?;

        Ok(path)
    }
}

#[async_trait]
impl MdnAgentDataNode for MdnAgentDataNodeWillowImpl {
    fn user_data_root_path(&self, user_id: &str) -> String {
        format!("mdn/{}/data/{}", self.agent_holder_id, user_id)
    }
    async fn get_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
    ) -> MeeDataSyncResult<Vec<GetUserDataRecord>> {
        // TODO handle namespace properly
        // let ns = self
        //     .willow_peer
        //     .willow_namespace_manager
        //     .get_owned_namespaces()
        //     .await?
        //     .pop()
        //     .unwrap();

        let mut range = ThreeDRange::full();

        let path = self.make_entry_path(user_id, attribute_name, sub_attribute_path)?;

        range.paths = Range::new(path.clone(), RangeEnd::Open);

        let entries = self
            .willow_peer
            .willow_data_manager
            .get_entries(self.namespace_id, range)
            .await?;

        let records = entries.into_iter().map(|entry| {
            let willow_peer = self.willow_peer.clone();

            async move {
                let path = entry.path.clone();
                let payload = willow_peer
                    .willow_data_manager
                    .read_entry_payload(entry)
                    .await?;

                let record = if let Some(payload) = payload {
                    Some(GetUserDataRecord {
                        key: path
                            .into_iter()
                            .map(|p| String::from_utf8(p.to_vec()).unwrap())
                            .collect::<Vec<_>>()
                            .join("/"),
                        value: payload.to_vec(),
                    })
                } else {
                    None
                };

                Ok(record) as MeeDataSyncResult<Option<GetUserDataRecord>>
            }
        });

        let records = join_all(records)
            .await
            .into_iter()
            .filter_map(|rec| match rec {
                Ok(v) => v,
                Err(e) => {
                    log::error!("Error reading entry payload: {e}");
                    None
                }
            })
            .collect();

        Ok(records)
    }

    async fn set_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
        value: Vec<u8>,
    ) -> MeeDataSyncResult {
        let path = self.make_entry_path(user_id, attribute_name, sub_attribute_path)?;

        // TODO handle namespace properly
        // let ns = self
        //     .willow_peer
        //     .willow_namespace_manager
        //     .get_owned_namespaces()
        //     .await?
        //     .pop()
        //     .unwrap();

        let path_bytes = path
            .components()
            .iter()
            .map(|p| p.as_ref())
            .collect::<Vec<_>>();

        self.willow_peer
            .willow_data_manager
            .insert_entry(self.namespace_id, &path_bytes, value)
            .await?;

        Ok(())
    }
}
