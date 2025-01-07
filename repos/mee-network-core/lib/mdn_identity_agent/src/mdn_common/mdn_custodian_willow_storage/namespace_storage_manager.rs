use super::MdnIdentityAgentIdentityContextNamespace;
use crate::{
    error::MdnIdentityAgentResult,
    mdn_common::local_storage::local_kvdb::{LocalKvDbExt, LocalKvDbRedb},
};
use async_trait::async_trait;
use std::sync::Arc;

#[async_trait]
pub trait WillowNamespaceStorageManager {
    async fn write_context_namespace(
        &self,
        record: &MdnIdentityAgentIdentityContextNamespace,
    ) -> MdnIdentityAgentResult;
    async fn read_context_namespace(
        &self,
        mdn_context_scoped_uid: &str,
        mdn_identity_context_uid: &str,
    ) -> MdnIdentityAgentResult<Option<MdnIdentityAgentIdentityContextNamespace>>;
    async fn list_context_namespaces(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentIdentityContextNamespace>>;
}

const WILLOW_STORAGE_CONTEXT_NS: &str = "WILLOW_STORAGE_CONTEXT_NS";

pub struct WillowNamespaceStorageManagerEmbeddedRedb {
    local_kvdb: LocalKvDbExt,
}

impl WillowNamespaceStorageManagerEmbeddedRedb {
    pub async fn try_new(local_db_file_path: String) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            local_kvdb: LocalKvDbExt::new(Arc::new(
                LocalKvDbRedb::try_new(local_db_file_path.clone(), "WILLOW_NS_TABLE".to_string())
                    .await?,
            )),
        })
    }
    fn make_context_ns_key(&self, ctx_scoped_id: &str, ctx_id: &str) -> String {
        format!("{WILLOW_STORAGE_CONTEXT_NS}/{ctx_scoped_id}/{ctx_id}")
    }
    fn make_wildcard_context_ns_key(&self) -> String {
        format!("{WILLOW_STORAGE_CONTEXT_NS}/")
    }
}

#[async_trait]
impl WillowNamespaceStorageManager for WillowNamespaceStorageManagerEmbeddedRedb {
    async fn write_context_namespace(
        &self,
        record: &MdnIdentityAgentIdentityContextNamespace,
    ) -> MdnIdentityAgentResult {
        self.local_kvdb
            .set_json_value(
                self.make_context_ns_key(
                    &record.mdn_context_scoped_uid,
                    &record.mdn_identity_context_uid,
                ),
                record,
            )
            .await?;

        Ok(())
    }
    async fn read_context_namespace(
        &self,
        mdn_context_scoped_uid: &str,
        mdn_identity_context_uid: &str,
    ) -> MdnIdentityAgentResult<Option<MdnIdentityAgentIdentityContextNamespace>> {
        self.local_kvdb
            .get_json_value(
                self.make_context_ns_key(mdn_context_scoped_uid, mdn_identity_context_uid),
            )
            .await
    }
    async fn list_context_namespaces(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnIdentityAgentIdentityContextNamespace>> {
        let mut res = vec![];

        for (_k, v) in self
            .local_kvdb
            .0
            .range_inclusive(Some(self.make_wildcard_context_ns_key()), None)
            .await?
        {
            let ctx_ns = serde_json::from_slice(&v)?;

            res.push(ctx_ns);
        }

        Ok(res)
    }
}
