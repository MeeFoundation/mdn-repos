use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_identity_context::api_types::MdnIdentityContextResponse,
    mdn_common::{
        mdn_custodian_willow_storage::MdnCustodianWillowStorage,
        meeql_storage::MdnCustodianMeeqlDataManager,
    },
    native_agent::mdn_identity_context::manager::MdnCloudControllerIdentityContextManager,
};
use async_trait::async_trait;
use std::sync::Arc;

pub type MdnIdentityContextMetadata = MdnIdentityContextResponse;

#[async_trait]
/// API for working with MDN Nodes
pub trait MdnNodeManager {
    ///
    fn mdn_custodian_meeql_data_manager(
        &self,
    ) -> Arc<dyn MdnCustodianMeeqlDataManager + Send + Sync>;
    ///
    fn mdn_cloud_controller_identity_context_manager(
        &self,
    ) -> Arc<dyn MdnCloudControllerIdentityContextManager + Send + Sync>;
    ///
    fn mdn_custodian_willow_storage(&self) -> MdnCustodianWillowStorage;
    ///
    async fn create_context(
        &self,
        custodian_uid: String,
        context_description: String,
    ) -> MdnIdentityAgentResult<MdnIdentityContextMetadata> {
        let willow_ns = self
            .mdn_custodian_willow_storage()
            .allocate_context_namespace()
            .await?;

        let res = self
            .mdn_cloud_controller_identity_context_manager()
            .create_context(custodian_uid, willow_ns.to_string(), context_description)
            .await?;

        self.mdn_custodian_willow_storage()
            .create_context_namespace(
                res.mdn_identity_context_uid.clone(),
                res.context_scoped_subject_uid.clone(),
                willow_ns,
            )
            .await?;

        Ok(res)
    }
    ///
    async fn delete_context(
        &self,
        mdn_identity_context: &MdnIdentityContextMetadata,
    ) -> MdnIdentityAgentResult {
        todo!()
    }
    ///
    async fn import_shared_context(
        &self,
        mdn_identity_context: &MdnIdentityContextMetadata,
    ) -> MdnIdentityAgentResult {
        todo!()
    }
    ///
    async fn list_contexts(&self) -> MdnIdentityAgentResult<Vec<MdnIdentityContextMetadata>> {
        self.mdn_cloud_controller_identity_context_manager()
            .list_contexts()
            .await
    }
    // TODO publish persona model attribute updates to the MDN Cloud Controller
    ///
    async fn write_context_data(
        &self,
        mdn_identity_context_uid: &str,
        meeql_query: &str,
        value: Vec<u8>,
    ) -> MdnIdentityAgentResult {
        self.mdn_custodian_meeql_data_manager()
            .write_context_data(mdn_identity_context_uid, meeql_query, value)
            .await
    }
    /// Reads context data from all custodian context containers aggregated by context scoped ID issued for that custodian
    async fn read_context_data(
        &self,
        context_scoped_subject_uid: &str,
        meeql_query: &str,
    ) -> MdnIdentityAgentResult<Vec<Vec<u8>>> {
        self.mdn_custodian_meeql_data_manager()
            .read_context_data(context_scoped_subject_uid, meeql_query)
            .await
    }
}
