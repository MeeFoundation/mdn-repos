use crate::{error::MeeDataSyncResult, willow::peer::namespace_manager::WillowNamespaceManager};
use async_trait::async_trait;
use iroh_willow::proto::{data_model::NamespaceId, keys::NamespaceKind};
use std::{collections::HashMap, sync::Arc};
use tokio::sync::Mutex;

#[derive(Debug, Clone)]
pub struct AgentNodeDataNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub struct CapabilityRevocationListNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub enum NamespaceType {
    /// Owned namespace for storing actual data (persona model attributes)
    AgentNodeDataNs(AgentNodeDataNs),

    /// Communal namespace for capability revocation list
    CapabilityRevocationListNs(CapabilityRevocationListNs),
}

impl NamespaceType {
    pub fn namespace_id(&self) -> NamespaceId {
        match self {
            NamespaceType::AgentNodeDataNs(ns) => ns.0,
            NamespaceType::CapabilityRevocationListNs(ns) => ns.0,
        }
    }
}

#[async_trait]
pub trait NamespaceStore {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool>;
    async fn set_ns(&self, ns_type: NamespaceType) -> MeeDataSyncResult;
    async fn get_agent_node_data_ns(&self) -> MeeDataSyncResult<Option<AgentNodeDataNs>>;
    async fn get_cap_revoke_list_ns(&self)
        -> MeeDataSyncResult<Option<CapabilityRevocationListNs>>;
}

#[async_trait]
impl NamespaceStore for NamespaceStoreInMemory {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool> {
        let res = self.store.lock().await.contains_key(&ns_id);

        Ok(res)
    }
    async fn set_ns(&self, ns_type: NamespaceType) -> MeeDataSyncResult {
        self.store
            .lock()
            .await
            .insert(ns_type.namespace_id(), ns_type);

        Ok(())
    }
    async fn get_agent_node_data_ns(&self) -> MeeDataSyncResult<Option<AgentNodeDataNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                NamespaceType::AgentNodeDataNs(v) => Some(v),
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
                NamespaceType::CapabilityRevocationListNs(v) => Some(v),
                _ => None,
            })
            .cloned();

        Ok(ns)
    }
}

#[derive(Clone)]
pub struct NamespaceStoreInMemory {
    store: Arc<Mutex<HashMap<NamespaceId, NamespaceType>>>,
}

impl NamespaceStoreInMemory {
    pub fn new() -> Self {
        Self {
            store: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

#[derive(Clone)]
pub struct NamespaceStoreManager {
    pub(crate) store: Arc<dyn NamespaceStore + Send + Sync>,
    willow_namespace_manager: WillowNamespaceManager,
}

impl NamespaceStoreManager {
    pub async fn new(
        store: Arc<dyn NamespaceStore + Send + Sync>,
        willow_namespace_manager: WillowNamespaceManager,
    ) -> MeeDataSyncResult<Self> {
        if store.get_agent_node_data_ns().await?.is_none() {
            let own_data_namespace_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Owned)
                .await?;

            store
                .set_ns(NamespaceType::AgentNodeDataNs(AgentNodeDataNs(
                    own_data_namespace_id,
                )))
                .await?;
        }

        if store.get_cap_revoke_list_ns().await?.is_none() {
            let cap_revocation_list_ns_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Communal)
                .await?;

            store
                .set_ns(NamespaceType::CapabilityRevocationListNs(
                    CapabilityRevocationListNs(cap_revocation_list_ns_id),
                ))
                .await?;
        }

        Ok(Self {
            store,
            willow_namespace_manager,
        })
    }
}
