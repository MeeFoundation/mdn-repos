use crate::error::MdnIdentityAgentResult;
use data_storage_manager::WillowDataStorageManager;
use mee_data_sync::willow::{
    peer::WillowPeer,
    proto::{data_model::NamespaceId, keys::NamespaceKind},
};
use namespace_storage_manager::WillowNamespaceStorageManager;
use serde::{Deserialize, Serialize};
use std::sync::Arc;

pub mod data_storage_manager;
pub mod namespace_storage_manager;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct MdnIdentityAgentIdentityContextNamespace {
    // Owned Willow namespace ID
    pub willow_ns: NamespaceId,

    // MDN Cloud Controller generated context ID
    pub mdn_identity_context_uid: String,

    // MDN Cloud Controller generated context-scoped user ID
    pub mdn_context_scoped_uid: String,
}

// TODO more namespaces in future: revocation list and others
pub enum MdnIdentityAgentNamespace {
    IdentityContext(MdnIdentityAgentIdentityContextNamespace),
}

#[derive(Clone)]
pub struct MdnCustodianWillowStorage {
    willow_namespace_storage_manager: Arc<dyn WillowNamespaceStorageManager + Send + Sync>,
    pub(crate) willow_data_storage_manager: Arc<dyn WillowDataStorageManager + Send + Sync>,
    willow_peer: WillowPeer,
}

impl MdnCustodianWillowStorage {
    pub fn new(
        willow_namespace_storage_manager: Arc<dyn WillowNamespaceStorageManager + Send + Sync>,
        willow_data_storage_manager: Arc<dyn WillowDataStorageManager + Send + Sync>,
        willow_peer: WillowPeer,
    ) -> Self {
        Self {
            willow_peer,
            willow_data_storage_manager,
            willow_namespace_storage_manager,
        }
    }
    ///
    pub async fn all_namespaces(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentNamespace>> {
        todo!()
    }
    ///
    pub async fn context_namespaces(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentIdentityContextNamespace>> {
        self.willow_namespace_storage_manager
            .list_context_namespaces()
            .await
    }
    // TODO GC dangled willow namespaces
    ///
    pub async fn allocate_context_namespace(&self) -> MdnIdentityAgentResult<NamespaceId> {
        let willow_ns = self
            .willow_peer
            .willow_namespace_manager
            .create_namespace(NamespaceKind::Owned)
            .await?;

        Ok(willow_ns)
    }
    ///
    pub async fn create_context_namespace(
        &self,
        mdn_identity_context_uid: String,
        mdn_context_scoped_uid: String,
        willow_ns: NamespaceId,
    ) -> MdnIdentityAgentResult<MdnIdentityAgentIdentityContextNamespace> {
        let rec = MdnIdentityAgentIdentityContextNamespace {
            willow_ns,
            mdn_identity_context_uid,
            mdn_context_scoped_uid,
        };

        self.willow_namespace_storage_manager
            .write_context_namespace(&rec)
            .await?;

        Ok(rec)
    }
}
