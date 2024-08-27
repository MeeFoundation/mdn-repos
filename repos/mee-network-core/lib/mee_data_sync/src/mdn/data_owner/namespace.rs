use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::peer::namespace_manager::WillowNamespaceManager,
};
use async_trait::async_trait;
use iroh_willow::proto::{data_model::NamespaceId, keys::NamespaceKind};
use std::{collections::HashMap, sync::Arc};
use tokio::sync::Mutex;

#[derive(Debug, Clone, Copy)]
pub struct DataOwnerCapabilityListNs(pub NamespaceId);

#[derive(Debug, Clone)]
pub enum MdnDataOwnerNamespaceType {
    DataOwnerCapabilityListNs(DataOwnerCapabilityListNs),
}

impl MdnDataOwnerNamespaceType {
    pub fn namespace_id(&self) -> NamespaceId {
        match self {
            MdnDataOwnerNamespaceType::DataOwnerCapabilityListNs(ns) => ns.0,
        }
    }
}

#[async_trait]
pub trait MdnDataOwnerNamespaceStore {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool>;
    async fn set_ns(&self, ns_type: MdnDataOwnerNamespaceType) -> MeeDataSyncResult;
    async fn get_data_owner_cap_list_ns(
        &self,
    ) -> MeeDataSyncResult<Option<DataOwnerCapabilityListNs>>;
}

#[async_trait]
impl MdnDataOwnerNamespaceStore for MdnDataOwnerNamespaceStoreInMemory {
    async fn has_ns(&self, ns_id: NamespaceId) -> MeeDataSyncResult<bool> {
        let res = self.store.lock().await.contains_key(&ns_id);

        Ok(res)
    }
    async fn set_ns(&self, ns_type: MdnDataOwnerNamespaceType) -> MeeDataSyncResult {
        self.store
            .lock()
            .await
            .insert(ns_type.namespace_id(), ns_type);

        Ok(())
    }
    async fn get_data_owner_cap_list_ns(
        &self,
    ) -> MeeDataSyncResult<Option<DataOwnerCapabilityListNs>> {
        let ns = self
            .store
            .lock()
            .await
            .iter()
            .find_map(|(_, ns)| match ns {
                MdnDataOwnerNamespaceType::DataOwnerCapabilityListNs(v) => Some(v),
            })
            .cloned();

        Ok(ns)
    }
}

#[derive(Clone)]
pub struct MdnDataOwnerNamespaceStoreInMemory {
    store: Arc<Mutex<HashMap<NamespaceId, MdnDataOwnerNamespaceType>>>,
}

impl MdnDataOwnerNamespaceStoreInMemory {
    pub fn new() -> Self {
        Self {
            store: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

#[derive(Clone)]
pub struct MdnDataOwnerNamespaceStoreManager {
    store: Arc<dyn MdnDataOwnerNamespaceStore + Send + Sync>,
}

impl MdnDataOwnerNamespaceStoreManager {
    pub async fn new(
        store: Arc<dyn MdnDataOwnerNamespaceStore + Send + Sync>,
        willow_namespace_manager: WillowNamespaceManager,
    ) -> MeeDataSyncResult<Self> {
        if store.get_data_owner_cap_list_ns().await?.is_none() {
            let data_owner_cap_list_namespace_id = willow_namespace_manager
                .create_namespace(NamespaceKind::Owned)
                .await?;

            store
                .set_ns(MdnDataOwnerNamespaceType::DataOwnerCapabilityListNs(
                    DataOwnerCapabilityListNs(data_owner_cap_list_namespace_id),
                ))
                .await?;

            log::info!("Willow data owner cap list namespace has created: {data_owner_cap_list_namespace_id}");
        }

        Ok(Self { store })
    }
    pub async fn get_data_owner_cap_list_ns(&self) -> MeeDataSyncResult<DataOwnerCapabilityListNs> {
        let res = self
            .store
            .get_data_owner_cap_list_ns()
            .await?
            .ok_or_else(MeeDataSyncErr::missing_data_owner_cap_list_namespace)?;

        Ok(res)
    }
}

impl MeeDataSyncErr {
    fn missing_data_owner_cap_list_namespace() -> Self {
        MeeDataSyncErr::WillowNamespaceHandler(
            "Missing data owner capability list namespace".to_string(),
        )
    }
}
