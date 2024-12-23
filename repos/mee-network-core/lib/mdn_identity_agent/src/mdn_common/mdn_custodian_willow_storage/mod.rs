use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;
use mee_data_sync::willow::{
    peer::WillowPeer,
    proto::{data_model::NamespaceId, keys::NamespaceKind},
};
use namespace_storage_manager::NamespaceStorageManager;
use serde::{Deserialize, Serialize};
use std::sync::Arc;

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

#[async_trait]
pub trait MdnCustodianWillowStorage {
    fn willow_peer(&self) -> WillowPeer;
    fn namespace_storage_manager(&self) -> Arc<dyn NamespaceStorageManager + Send + Sync>;

    async fn all_namespaces(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentNamespace>> {
        todo!()
    }
    async fn context_namespaces(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentNamespace>> {
        todo!()
    }

    async fn create_context_namespace(
        &self,
        mdn_identity_context_uid: String,
        mdn_context_scoped_uid: String,
    ) -> MdnIdentityAgentResult<MdnIdentityAgentIdentityContextNamespace> {
        let willow_ns = self
            .willow_peer()
            .willow_namespace_manager
            .create_namespace(NamespaceKind::Owned)
            .await?;

        let rec = MdnIdentityAgentIdentityContextNamespace {
            willow_ns,
            mdn_identity_context_uid,
            mdn_context_scoped_uid,
        };

        self.namespace_storage_manager()
            .write_context_namespace(&rec)
            .await?;

        Ok(rec)
    }
}
