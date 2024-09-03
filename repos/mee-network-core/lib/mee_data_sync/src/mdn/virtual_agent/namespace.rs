use crate::error::{MeeDataSyncErr, MeeDataSyncResult};
use async_trait::async_trait;
use iroh_willow::proto::keys::NamespaceId;
use std::{collections::HashMap, sync::Arc};
use tokio::sync::Mutex;

#[derive(Debug, Clone, Copy)]
pub struct VirtualAgentSchemasNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub enum VirtualAgentNamespaceType {
    VirtualAgentSchemasNs(VirtualAgentSchemasNs),
}

impl VirtualAgentNamespaceType {
    pub fn namespace_id(&self) -> NamespaceId {
        match self {
            VirtualAgentNamespaceType::VirtualAgentSchemasNs(ns) => ns.0,
        }
    }
}

#[async_trait]
pub trait VirtualAgentNamespaceStore {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool>;
    async fn set_ns(&self, ns_type: VirtualAgentNamespaceType) -> MeeDataSyncResult;
    async fn get_schemas_ns(&self) -> MeeDataSyncResult<Option<VirtualAgentSchemasNs>>;
}

#[async_trait]
impl VirtualAgentNamespaceStore for VirtualAgentNamespaceStoreInMemory {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool> {
        let res = self.store.lock().await.contains_key(&ns_id);

        Ok(res)
    }
    async fn set_ns(&self, ns_type: VirtualAgentNamespaceType) -> MeeDataSyncResult {
        self.store
            .lock()
            .await
            .insert(ns_type.namespace_id(), ns_type);

        Ok(())
    }
    async fn get_schemas_ns(&self) -> MeeDataSyncResult<Option<VirtualAgentSchemasNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                VirtualAgentNamespaceType::VirtualAgentSchemasNs(v) => Some(v),
            })
            .cloned();

        Ok(ns)
    }
}

#[derive(Clone)]
pub struct VirtualAgentNamespaceStoreInMemory {
    store: Arc<Mutex<HashMap<NamespaceId, VirtualAgentNamespaceType>>>,
}

impl VirtualAgentNamespaceStoreInMemory {
    fn new() -> Self {
        Self {
            store: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

#[derive(Clone)]
pub struct VirtualAgentNamespaceStoreManager {
    store: Arc<dyn VirtualAgentNamespaceStore + Send + Sync>,
}

impl VirtualAgentNamespaceStoreManager {
    fn new(store: Arc<dyn VirtualAgentNamespaceStore + Send + Sync>) -> Self {
        Self { store }
    }
    pub fn new_in_memory() -> Self {
        Self::new(Arc::new(VirtualAgentNamespaceStoreInMemory::new()))
    }
    pub async fn get_schemas_ns(&self) -> MeeDataSyncResult<VirtualAgentSchemasNs> {
        let res = self
            .store
            .get_schemas_ns()
            .await?
            .ok_or_else(MeeDataSyncErr::missing_pda_schemas_namespace)?;

        Ok(res)
    }
}

impl MeeDataSyncErr {
    fn missing_pda_schemas_namespace() -> Self {
        MeeDataSyncErr::WillowNamespaceHandler(
            "Missing virtual agent PDA schemas namespace".to_string(),
        )
    }
}
