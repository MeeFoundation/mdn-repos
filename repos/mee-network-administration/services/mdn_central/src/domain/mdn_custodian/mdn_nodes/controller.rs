use super::{
    api::types::{MdnNodeResponse, RegisterMdnNodeRequest},
    repositories::{
        mdn_node_signing_pub_keys::MdnNodeSigningPubKeysRepositoryImpl,
        mdn_nodes::MdnNodesRepositoryImpl,
    },
    services::mdn_nodes::MdnNodesService,
};
use crate::{
    domain::mdn_custodian::account::repositories::mdn_custodians::MdnCustodiansRepositoryImpl,
    error::MdnCentralResult,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;

#[derive(Clone)]
pub struct MdnNodesController {
    rdb_storage: RbdStorage,
}

impl MdnNodesController {
    pub fn new(rdb_storage: RbdStorage) -> Self {
        Self { rdb_storage }
    }
    pub fn mdn_node_service<'a, C: ConnectionTrait>(
        tx: &'a C,
    ) -> MdnNodesService<'a> {
        MdnNodesService::new(
            Box::new(MdnNodesRepositoryImpl::new(tx)),
            Box::new(MdnCustodiansRepositoryImpl::new(tx)),
            Box::new(MdnNodeSigningPubKeysRepositoryImpl::new(tx)),
        )
    }

    pub async fn list_all(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult<Vec<MdnNodeResponse>> {
        let res = Self::mdn_node_service(&*self.rdb_storage.connection())
            .list_all(mdn_custodian_uid)
            .await?;

        Ok(res)
    }
    pub async fn add_node(
        &self,
        payload: RegisterMdnNodeRequest,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult {
        Self::mdn_node_service(&*self.rdb_storage.connection())
            .register_node(payload, mdn_custodian_uid)
            .await?;

        Ok(())
    }
}
