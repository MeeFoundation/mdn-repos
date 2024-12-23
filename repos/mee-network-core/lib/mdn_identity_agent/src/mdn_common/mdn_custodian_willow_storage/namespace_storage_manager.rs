use super::MdnIdentityAgentIdentityContextNamespace;
use crate::{
    error::MdnIdentityAgentResult,
    mdn_common::local_storage::local_kvdb::{LocalKvDbExt, LocalKvDbRedb},
};
use async_trait::async_trait;
use std::sync::Arc;

#[async_trait]
pub trait NamespaceStorageManager {
    async fn write_context_namespace(
        &self,
        record: &MdnIdentityAgentIdentityContextNamespace,
    ) -> MdnIdentityAgentResult;
    async fn read_context_namespace(
        &self,
        context_id: &str,
    ) -> MdnIdentityAgentResult<Option<MdnIdentityAgentIdentityContextNamespace>>;
    async fn all_context_namespaces(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentIdentityContextNamespace>>;
}

const WILLOW_STORAGE_CONTEXT_NS: &str = "WILLOW_STORAGE_CONTEXT_NS";

pub struct NamespaceStorageManagerEmbeddedRedb {
    local_kvdb: LocalKvDbExt,
}

impl NamespaceStorageManagerEmbeddedRedb {
    pub async fn try_new(local_db_file_path: String) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            local_kvdb: LocalKvDbExt::new(Arc::new(
                LocalKvDbRedb::try_new(local_db_file_path.clone(), "WILLOW_NS_TABLE".to_string())
                    .await?,
            )),
        })
    }
    fn make_ns_key(&self, id: &str) -> String {
        format!("{WILLOW_STORAGE_CONTEXT_NS}/{id}")
    }
}

#[async_trait]
impl NamespaceStorageManager for NamespaceStorageManagerEmbeddedRedb {
    async fn write_context_namespace(
        &self,
        record: &MdnIdentityAgentIdentityContextNamespace,
    ) -> MdnIdentityAgentResult {
        self.local_kvdb
            .set_json_value(self.make_ns_key(&uuid::Uuid::new_v4().to_string()), record)
            .await?;

        Ok(())
    }
    async fn read_context_namespace(
        &self,
        context_id: &str,
    ) -> MdnIdentityAgentResult<Option<MdnIdentityAgentIdentityContextNamespace>> {
        self.local_kvdb
            .get_json_value(self.make_ns_key(&context_id))
            .await
    }
    async fn all_context_namespaces(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentIdentityContextNamespace>> {
        Ok(vec![])
    }
}
