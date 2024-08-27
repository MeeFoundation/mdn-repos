use super::delegation::manager::MdnProviderCapabilityPack;
use crate::error::MeeDataSyncResult;
use std::{
    collections::HashMap,
    sync::{Arc, Mutex},
};

pub trait MdnProviderCapabilityStore {
    fn insert_cap(&self, cap: MdnProviderCapabilityPack) -> MeeDataSyncResult;
    fn get_cap(&self, cap_id: &str) -> MeeDataSyncResult<Option<MdnProviderCapabilityPack>>;
    fn del_cap(&self, cap_id: &str) -> MeeDataSyncResult<Option<MdnProviderCapabilityPack>>;
    fn list_caps(&self) -> MeeDataSyncResult<Vec<MdnProviderCapabilityPack>>;
}

#[derive(Clone)]
pub struct MdnProviderCapabilityInMemoryStore {
    inner: Arc<Mutex<HashMap<String, MdnProviderCapabilityPack>>>,
}

impl MdnProviderCapabilityInMemoryStore {
    pub fn new() -> Self {
        Self {
            inner: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

impl MdnProviderCapabilityStore for MdnProviderCapabilityInMemoryStore {
    fn insert_cap(&self, cap: MdnProviderCapabilityPack) -> MeeDataSyncResult {
        self.inner.lock()?.insert(cap.capability_id.clone(), cap);

        Ok(())
    }

    fn get_cap(&self, cap_id: &str) -> MeeDataSyncResult<Option<MdnProviderCapabilityPack>> {
        Ok(self.inner.lock()?.get(cap_id).cloned())
    }

    fn del_cap(&self, cap_id: &str) -> MeeDataSyncResult<Option<MdnProviderCapabilityPack>> {
        Ok(self.inner.lock()?.remove(cap_id))
    }

    fn list_caps(&self) -> MeeDataSyncResult<Vec<MdnProviderCapabilityPack>> {
        Ok(self.inner.lock()?.iter().map(|(_, v)| v).cloned().collect())
    }
}

#[derive(Clone)]
pub struct MdnProviderCapabilityManager {
    pub store: Arc<dyn MdnProviderCapabilityStore + Send + Sync>,
}

impl MdnProviderCapabilityManager {
    pub fn new(store: Arc<dyn MdnProviderCapabilityStore + Send + Sync>) -> Self {
        Self { store }
    }
}
