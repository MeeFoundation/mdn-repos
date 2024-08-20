use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::peer::namespace_manager::WillowNamespaceManager,
};
use async_trait::async_trait;
use iroh_willow::proto::{
    data_model::NamespaceId,
    keys::{NamespaceKind, UserId},
};
use std::{collections::HashMap, sync::Arc};
use tokio::sync::Mutex;

#[derive(Debug, Clone)]
pub struct AgentNodeDataNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub struct CapabilityRevocationListNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub struct OtherPeerCapabilityRevocationNs {
    pub peer_id: UserId,
    pub ns_id: NamespaceId,
}

#[derive(Debug, Clone)]
pub enum MdnNamespaceType {
    /// Owned namespace for storing actual data (persona model attributes)
    AgentNodeDataNs(AgentNodeDataNs),

    /// Communal namespace for capability revocation list
    CapabilityRevocationListNs(CapabilityRevocationListNs),

    /// Revocations lists from other peers delegated access to this peer
    OtherPeerCapabilityRevocationNs(OtherPeerCapabilityRevocationNs),
}

impl MdnNamespaceType {
    pub fn namespace_id(&self) -> NamespaceId {
        match self {
            MdnNamespaceType::AgentNodeDataNs(ns) => ns.0,
            MdnNamespaceType::CapabilityRevocationListNs(ns) => ns.0,
            MdnNamespaceType::OtherPeerCapabilityRevocationNs(ns) => ns.ns_id,
        }
    }
}

#[async_trait]
pub trait MdnNamespaceStore {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool>;
    async fn set_ns(&self, ns_type: MdnNamespaceType) -> MeeDataSyncResult;
    async fn get_agent_node_data_ns(&self) -> MeeDataSyncResult<Option<AgentNodeDataNs>>;
    async fn get_cap_revoke_list_ns(&self)
        -> MeeDataSyncResult<Option<CapabilityRevocationListNs>>;
    async fn get_others_cap_revoke_list_nss(
        &self,
    ) -> MeeDataSyncResult<Vec<OtherPeerCapabilityRevocationNs>>;
}

#[async_trait]
impl MdnNamespaceStore for NamespaceStoreInMemory {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool> {
        let res = self.store.lock().await.contains_key(&ns_id);

        Ok(res)
    }
    async fn set_ns(&self, ns_type: MdnNamespaceType) -> MeeDataSyncResult {
        self.store
            .lock()
            .await
            .insert(ns_type.namespace_id(), ns_type);

        Ok(())
    }
    async fn get_others_cap_revoke_list_nss(
        &self,
    ) -> MeeDataSyncResult<Vec<OtherPeerCapabilityRevocationNs>> {
        let nss = self
            .store
            .lock()
            .await
            .iter()
            .filter_map(|(_, ns)| match ns {
                MdnNamespaceType::OtherPeerCapabilityRevocationNs(v) => Some(v),
                _ => None,
            })
            .cloned()
            .collect();

        Ok(nss)
    }
    async fn get_agent_node_data_ns(&self) -> MeeDataSyncResult<Option<AgentNodeDataNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                MdnNamespaceType::AgentNodeDataNs(v) => Some(v),
                _ => None,
            })
            .cloned();

        Ok(ns)
    }
    async fn get_cap_revoke_list_ns(
        &self,
    ) -> MeeDataSyncResult<Option<CapabilityRevocationListNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                MdnNamespaceType::CapabilityRevocationListNs(v) => Some(v),
                _ => None,
            })
            .cloned();

        Ok(ns)
    }
}

#[derive(Clone)]
pub struct NamespaceStoreInMemory {
    store: Arc<Mutex<HashMap<NamespaceId, MdnNamespaceType>>>,
}

impl NamespaceStoreInMemory {
    pub fn new() -> Self {
        Self {
            store: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

#[derive(Clone)]
pub struct MdnNamespaceStoreManager {
    store: Arc<dyn MdnNamespaceStore + Send + Sync>,
}

impl MdnNamespaceStoreManager {
    pub async fn new(
        store: Arc<dyn MdnNamespaceStore + Send + Sync>,
        willow_namespace_manager: WillowNamespaceManager,
    ) -> MeeDataSyncResult<Self> {
        if store.get_agent_node_data_ns().await?.is_none() {
            let own_data_namespace_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Owned)
                .await?;

            store
                .set_ns(MdnNamespaceType::AgentNodeDataNs(AgentNodeDataNs(
                    own_data_namespace_id,
                )))
                .await?;

            log::info!("Willow data namespace has created: {own_data_namespace_id}");
        }

        if store.get_cap_revoke_list_ns().await?.is_none() {
            let cap_revocation_list_ns_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Communal)
                .await?;

            store
                .set_ns(MdnNamespaceType::CapabilityRevocationListNs(
                    CapabilityRevocationListNs(cap_revocation_list_ns_id),
                ))
                .await?;

            log::info!(
                "Willow caps revocation list namespace has created: {cap_revocation_list_ns_id}"
            );
        }

        Ok(Self { store })
    }
    pub async fn get_agent_node_data_ns(&self) -> MeeDataSyncResult<AgentNodeDataNs> {
        let res = self
            .store
            .get_agent_node_data_ns()
            .await?
            .ok_or_else(MeeDataSyncErr::missing_agent_node_data_namespace)?;

        Ok(res)
    }
    pub async fn get_cap_revoke_list_ns(&self) -> MeeDataSyncResult<CapabilityRevocationListNs> {
        let res = self
            .store
            .get_cap_revoke_list_ns()
            .await?
            .ok_or_else(MeeDataSyncErr::missing_cap_revoke_list_namespace)?;

        Ok(res)
    }
    pub async fn set_other_peer_revocation_list_ns(
        &self,
        ns_id: NamespaceId,
        peer_id: UserId,
    ) -> MeeDataSyncResult {
        self.store
            .set_ns(MdnNamespaceType::OtherPeerCapabilityRevocationNs(
                OtherPeerCapabilityRevocationNs { peer_id, ns_id },
            ))
            .await?;

        Ok(())
    }

    pub async fn get_others_cap_revoke_list_nss(
        &self,
    ) -> MeeDataSyncResult<Vec<OtherPeerCapabilityRevocationNs>> {
        self.store.get_others_cap_revoke_list_nss().await
    }
}

impl MeeDataSyncErr {
    pub fn missing_agent_node_data_namespace() -> Self {
        MeeDataSyncErr::WillowNamespaceHandler("Missing data namespace".to_string())
    }
    pub fn missing_cap_revoke_list_namespace() -> Self {
        MeeDataSyncErr::WillowNamespaceHandler(
            "Missing capability revocation namespace".to_string(),
        )
    }
}
