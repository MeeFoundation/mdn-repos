use crate::{
    mdn_common::{
        mdn_custodian_willow_storage::MdnCustodianWillowStorage, mdn_node::MdnNodeManager,
        meeql_storage::MdnCustodianMeeqlDataManager,
    },
    native_agent::mdn_identity_context::manager::MdnCloudControllerIdentityContextManager,
};
use async_trait::async_trait;
use std::sync::Arc;

pub struct MdnNodeManagerImpl {
    mdn_cloud_controller_identity_context_manager:
        Arc<dyn MdnCloudControllerIdentityContextManager + Send + Sync>,
    mdn_custodian_willow_storage: MdnCustodianWillowStorage,
    mdn_custodian_meeql_storage: Arc<dyn MdnCustodianMeeqlDataManager + Send + Sync>,
}

impl MdnNodeManagerImpl {
    pub fn new(
        mdn_cloud_controller_identity_context_manager: Arc<
            dyn MdnCloudControllerIdentityContextManager + Send + Sync,
        >,
        mdn_custodian_willow_storage: MdnCustodianWillowStorage,
        mdn_custodian_meeql_storage: Arc<dyn MdnCustodianMeeqlDataManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_cloud_controller_identity_context_manager,
            mdn_custodian_willow_storage,
            mdn_custodian_meeql_storage,
        }
    }
}

#[async_trait]
impl MdnNodeManager for MdnNodeManagerImpl {
    fn mdn_custodian_meeql_data_manager(&self) -> Arc<dyn MdnCustodianMeeqlDataManager + Send + Sync> {
        self.mdn_custodian_meeql_storage.clone()
    }
    fn mdn_cloud_controller_identity_context_manager(
        &self,
    ) -> Arc<dyn MdnCloudControllerIdentityContextManager + Send + Sync> {
        self.mdn_cloud_controller_identity_context_manager.clone()
    }
    fn mdn_custodian_willow_storage(&self) -> MdnCustodianWillowStorage {
        self.mdn_custodian_willow_storage.clone()
    }
}
