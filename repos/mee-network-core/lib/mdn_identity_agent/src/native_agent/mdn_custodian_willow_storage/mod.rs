use crate::mdn_common::mdn_custodian_willow_storage::{
    namespace_storage_manager::NamespaceStorageManager, MdnCustodianWillowStorage,
};
use async_trait::async_trait;
use mee_data_sync::willow::peer::WillowPeer;
use std::sync::Arc;

pub struct MdnUserCustodianWillowStorage {
    namespace_storage_manager: Arc<dyn NamespaceStorageManager + Send + Sync>,
    willow_peer: WillowPeer,
}

impl MdnUserCustodianWillowStorage {
    pub fn new(
        namespace_storage_manager: Arc<dyn NamespaceStorageManager + Send + Sync>,
        willow_peer: WillowPeer,
    ) -> Self {
        Self {
            willow_peer,
            namespace_storage_manager,
        }
    }
}

#[async_trait]
impl MdnCustodianWillowStorage for MdnUserCustodianWillowStorage {
    fn willow_peer(&self) -> WillowPeer {
        self.willow_peer.clone()
    }

    fn namespace_storage_manager(&self) -> Arc<dyn NamespaceStorageManager + Send + Sync> {
        self.namespace_storage_manager.clone()
    }
}
