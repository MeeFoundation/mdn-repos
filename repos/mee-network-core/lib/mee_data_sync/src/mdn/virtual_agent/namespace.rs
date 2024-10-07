use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::peer::namespace_manager::WillowNamespaceManager,
};
use async_trait::async_trait;
use iroh_willow::proto::keys::{NamespaceId, NamespaceKind};
use std::{collections::HashMap, sync::Arc};
use tokio::sync::Mutex;

#[derive(Debug, Clone, Copy)]
pub struct VirtualAgentSearchSchemasNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub enum VirtualAgentNamespaceType {
    VirtualAgentSearchSchemasNs(VirtualAgentSearchSchemasNs),
}

impl VirtualAgentNamespaceType {
    pub fn namespace_id(&self) -> NamespaceId {
        match self {
            VirtualAgentNamespaceType::VirtualAgentSearchSchemasNs(ns) => ns.0,
        }
    }
}

#[async_trait]
pub trait VirtualAgentNamespaceStore {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool>;
    async fn set_ns(&self, ns_type: VirtualAgentNamespaceType) -> MeeDataSyncResult;
    async fn get_search_schemas_ns(&self)
        -> MeeDataSyncResult<Option<VirtualAgentSearchSchemasNs>>;
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
    async fn get_search_schemas_ns(
        &self,
    ) -> MeeDataSyncResult<Option<VirtualAgentSearchSchemasNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                VirtualAgentNamespaceType::VirtualAgentSearchSchemasNs(v) => Some(v),
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
    async fn new(
        store: Arc<dyn VirtualAgentNamespaceStore + Send + Sync>,
        willow_namespace_manager: WillowNamespaceManager,
    ) -> MeeDataSyncResult<Self> {
        if store.get_search_schemas_ns().await?.is_none() {
            let search_schemas_ns_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Owned)
                .await?;

            store
                .set_ns(VirtualAgentNamespaceType::VirtualAgentSearchSchemasNs(
                    VirtualAgentSearchSchemasNs(search_schemas_ns_id),
                ))
                .await?;

            log::info!(
                "Willow search schemas virtual agent namespace has created: {search_schemas_ns_id}"
            );
        }

        Ok(Self { store })
    }
    pub async fn new_in_memory(
        willow_namespace_manager: WillowNamespaceManager,
    ) -> MeeDataSyncResult<Self> {
        Ok(Self::new(
            Arc::new(VirtualAgentNamespaceStoreInMemory::new()),
            willow_namespace_manager,
        )
        .await?)
    }
    pub async fn get_schemas_ns(&self) -> MeeDataSyncResult<VirtualAgentSearchSchemasNs> {
        let res = self
            .store
            .get_search_schemas_ns()
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
