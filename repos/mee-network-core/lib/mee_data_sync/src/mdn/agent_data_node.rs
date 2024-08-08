use super::traits::{
    GetUserDataRecord, MdnAgentDataNodeDelegation, MdnAgentDataNodeNetwork, MdnAgentDataNodeStore,
    MdnAgentDataNodeUser,
};
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::peer::{delegation_manager::ImportCapabilitiesFromRemotePeer, WillowPeer},
};
use async_trait::async_trait;
use futures::future::join_all;
use iroh_net::{ticket::NodeTicket, NodeAddr};
use iroh_willow::{
    auth::{CapSelector, CapabilityPack, DelegateTo},
    proto::{
        grouping::{Range, RangeEnd, ThreeDRange},
        keys::{NamespaceId, NamespaceKind, UserId},
        meadowcap::AccessMode,
        willow::{Entry, Path},
    },
    session::intents::IntentHandle,
};
use std::collections::HashSet;

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
                CapSelector::widest(self.own_data_namespace_id.clone()),
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
    willow_peer: WillowPeer,
    agent_holder_id: String,
    own_data_namespace_id: NamespaceId,
}

impl MdnAgentDataNodeWillowImpl {
    pub async fn new(willow_peer: WillowPeer, agent_holder_id: String) -> MeeDataSyncResult<Self> {
        let data_namespace_id = willow_peer
            .willow_namespace_manager
            .get_namespace_or_create(NamespaceKind::Owned)
            .await?;

        Ok(Self {
            own_data_namespace_id: data_namespace_id,
            willow_peer,
            agent_holder_id,
        })
    }
    pub fn make_entry_path(
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
impl MdnAgentDataNodeStore for MdnAgentDataNodeWillowImpl {
    fn user_data_root_path(&self, user_id: &str) -> String {
        format!("mdn/{}/data/{}", self.agent_holder_id, user_id)
    }
    // TODO find entries in delegated data areas (read caps namespaces)
    async fn get_user_data(
        &self,
        user_id: &str,
        attribute_name: &str,
        sub_attribute_path: &[&str],
    ) -> MeeDataSyncResult<Vec<GetUserDataRecord>> {
        let mut range = ThreeDRange::full();

        let query_path = self.make_entry_path(user_id, attribute_name, sub_attribute_path)?;

        // TODO wait for fix of the path end range calculation
        // range.paths = Range::new(query_path.clone(), RangeEnd::Closed(query_path.clone()));
        range.paths = Range::new(query_path.clone(), RangeEnd::Open);

        let mut entries = self
            .willow_peer
            .willow_data_manager
            .filter_entries(self.own_data_namespace_id, range, |e| {
                query_path.is_prefix_of(&e.path)
            })
            .await?;

        // log::warn!("[owned] {query_path:?} {entries:#?}");

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
            let e = self
                .willow_peer
                .willow_data_manager
                .filter_entries(ns, ThreeDRange::full(), |e| {
                    let owner_agnostic_path = e.path.remove_prefix(2);
                    let owner_agnostic_query_path = query_path.remove_prefix(2);
                    owner_agnostic_query_path.is_prefix_of(&owner_agnostic_path)
                })
                .await?;

            caps_entries.extend(e);
        }

        // log::warn!("[shared] {query_path:?} {caps_entries:#?}");

        entries.extend(caps_entries);

        let records = entries.into_iter().map(|entry| {
            let willow_peer = self.willow_peer.clone();

            async move {
                let path = entry.path.clone();
                let payload = willow_peer
                    .willow_data_manager
                    .read_entry_payload(entry.clone())
                    .await
                    .map_err(|e| (e, entry))?;

                let record = if let Some(payload) = payload {
                    Some(GetUserDataRecord {
                        key: path,
                        value: payload.to_vec(),
                    })
                } else {
                    None
                };

                Ok(record) as Result<Option<GetUserDataRecord>, (MeeDataSyncErr, Entry)>
            }
        });

        let records = join_all(records)
            .await
            .into_iter()
            .filter_map(|rec| match rec {
                Ok(v) => v,
                Err((err, entry)) => {
                    log::error!("Error ({err}) reading entry ({entry:#?}) payload.");
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
}
