use super::{
    api::types::{
        MdnCustodianStorageResponse, RegisterMdnCustodianStorageRequest,
    },
    repositories::mdn_custodian_storage::MdnCustodianStoragesRepositoryImpl,
    services::mdn_custodian_storage::MdnNodesService,
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
pub struct MdnCustodianStoragesController {
    rdb_storage: RbdStorage,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnCustodianStoragesController {
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
    pub fn mdn_custodian_storage_service<'a, C: ConnectionTrait>(
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnNodesService<'a> {
        MdnNodesService::new(
            Box::new(MdnCustodianStoragesRepositoryImpl::new(tx)),
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

    pub async fn list_all_custodian_storages(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult<Vec<MdnCustodianStorageResponse>> {
        let res = Self::mdn_custodian_storage_service(
            self.mdn_central_authority_signature.clone(),
            &*self.rdb_storage.connection(),
        )
        .list_all_custodian_storages(mdn_custodian_uid)
        .await?;

        Ok(res)
    }
    pub async fn register_custodian_storage(
        &self,
        payload: RegisterMdnCustodianStorageRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        Self::mdn_custodian_storage_service(
            self.mdn_central_authority_signature.clone(),
            &*self.rdb_storage.connection(),
        )
        .register_custodian_storage(payload, logged_in_mdn_user)
        .await?;

        Ok(())
    }
}
