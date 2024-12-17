use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepositoryImpl,
            storage::{
                repositories::mdn_custodian_storage::MdnCustodianStoragesRepositoryImpl,
                services::mdn_custodian_storage::MdnCustodianStorageService,
            },
        },
        mdn_user::user_account::{
            api::controller::MdnUserAccountController,
            api::middlewares::LoggedInMdnUser,
            repositories::mdn_user_signing_pub_keys::MdnUserSigningPubKeysRepositoryImpl,
        },
    },
    error::MdnCloudControllerResult,
};
use mdn_identity_agent::mdn_cloud::mdn_custodian_storage::api_types::{
    MdnCustodianStorageResponse, RegisterMdnCustodianStorageRequest,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnCustodianStoragesController {
    rdb_storage: RbdStorage,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnCustodianStoragesController {
    pub fn new(
        rdb_storage: RbdStorage,
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            rdb_storage,
            mdn_cloud_controller_authority_signature,
        }
    }
    pub fn mdn_custodian_storage_service_factory<'a, C: ConnectionTrait>(
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnCustodianStorageService<'a> {
        MdnCustodianStorageService::new(
            Box::new(MdnCustodianStoragesRepositoryImpl::new(tx)),
            Box::new(MdnCustodiansRepositoryImpl::new(tx)),
            Box::new(MdnUserSigningPubKeysRepositoryImpl::new(tx)),
            MdnUserAccountController::user_account_service_factory(
                tx,
                mdn_cloud_controller_authority_signature.clone(),
            ),
            mdn_cloud_controller_authority_signature.clone(),
        )
    }

    pub async fn list_all_custodian_storages(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<Vec<MdnCustodianStorageResponse>> {
        let res = Self::mdn_custodian_storage_service_factory(
            self.mdn_cloud_controller_authority_signature.clone(),
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
    ) -> MdnCloudControllerResult {
        Self::mdn_custodian_storage_service_factory(
            self.mdn_cloud_controller_authority_signature.clone(),
            &*self.rdb_storage.connection(),
        )
        .register_custodian_storage(payload, logged_in_mdn_user)
        .await?;

        Ok(())
    }
}
