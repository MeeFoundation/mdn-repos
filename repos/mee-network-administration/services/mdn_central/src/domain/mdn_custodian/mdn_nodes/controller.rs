use super::{
    api::types::{MdnNodeHostingPlatformResponse, RegisterMdnNodeHostingPlatformRequest},
    repositories::mdn_node_hosting_platforms::MdnNodesRepositoryImpl,
    services::mdn_nodes::MdnNodesService,
};
use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::account::repositories::mdn_custodians::MdnCustodiansRepositoryImpl,
        mdn_user::{
            identity_context::repositories::mdn_context_scoped_ids::MdnContextScopedIdsRepositoryImpl,
            user_account::{
                api::middlewares::LoggedInMdnUser,
                controller::MdnUserAccountController,
                repositories::mdn_user_signing_pub_keys::MdnNodeSigningPubKeysRepositoryImpl,
            },
        },
    },
    error::MdnCentralResult,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnNodesController {
    rdb_storage: RbdStorage,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnNodesController {
    pub fn new(
        rdb_storage: RbdStorage,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mdn_central_authority_signature,
        }
    }
    pub fn mdn_node_service<'a, C: ConnectionTrait>(
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnNodesService<'a> {
        MdnNodesService::new(
            Box::new(MdnNodesRepositoryImpl::new(tx)),
            Box::new(MdnCustodiansRepositoryImpl::new(tx)),
            Box::new(MdnNodeSigningPubKeysRepositoryImpl::new(tx)),
            Box::new(MdnContextScopedIdsRepositoryImpl::new(tx)),
            MdnUserAccountController::user_account_service(
                tx,
                mdn_central_authority_signature.clone(),
            ),
            mdn_central_authority_signature.clone(),
        )
    }

    pub async fn list_all_node_hosting_platforms(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult<Vec<MdnNodeHostingPlatformResponse>> {
        let res = Self::mdn_node_service(
            self.mdn_central_authority_signature.clone(),
            &*self.rdb_storage.connection(),
        )
        .list_all_node_hosting_platforms(mdn_custodian_uid)
        .await?;

        Ok(res)
    }
    pub async fn register_node_hosting_platform(
        &self,
        payload: RegisterMdnNodeHostingPlatformRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        Self::mdn_node_service(
            self.mdn_central_authority_signature.clone(),
            &*self.rdb_storage.connection(),
        )
        .register_node_hosting_platform(payload, logged_in_mdn_user)
        .await?;

        Ok(())
    }
}
