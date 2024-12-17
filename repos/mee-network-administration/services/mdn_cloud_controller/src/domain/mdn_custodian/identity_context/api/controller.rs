use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            identity_context::{
                repositories::{
                    mdn_context_scoped_ids::MdnContextScopedIdsRepositoryImpl,
                    mdn_identity_contexts::MdnIdentityContextsRepositoryImpl,
                    mdn_identity_contexts_in_storages::MdnContextInStorageRepositoryImpl,
                },
                services::mdn_identity_context::MdnIdentityContextService,
            },
            storage::api::controller::MdnCustodianStoragesController,
        },
        mdn_user::user_account::api::{
            controller::MdnUserAccountController, middlewares::LoggedInMdnUser,
        },
    },
    error::MdnCloudControllerResult,
};
use mdn_identity_agent::mdn_cloud::mdn_identity_context::api_types::{
    CreateMdnIdentityContextRequest, MdnIdentityContextResponse,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnIdentityContextController {
    rdb_storage: RbdStorage,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnIdentityContextController {
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

    pub fn mdn_identity_context_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> MdnIdentityContextService<'a> {
        Self::mdn_identity_context_service_factory(
            self.mdn_cloud_controller_authority_signature.clone(),
            tx,
        )
    }
    pub fn mdn_identity_context_service_factory<'a, C: ConnectionTrait>(
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnIdentityContextService<'a> {
        MdnIdentityContextService::new(
            Box::new(MdnIdentityContextsRepositoryImpl::new(tx)),
            Box::new(MdnContextScopedIdsRepositoryImpl::new(tx)),
            MdnUserAccountController::user_account_service_factory(
                tx,
                mdn_cloud_controller_authority_signature.clone(),
            ),
            MdnUserAccountController::mdn_custodians_service_factory(tx),
            Box::new(MdnContextInStorageRepositoryImpl::new(tx)),
            MdnCustodianStoragesController::mdn_custodian_storage_service_factory(mdn_cloud_controller_authority_signature.clone(), tx)
        )
    }
    pub async fn create_context(
        &self,
        create_ctx_request: CreateMdnIdentityContextRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult<MdnIdentityContextResponse> {
        self.mdn_identity_context_service(
            self.rdb_storage.connection().as_ref(),
        )
        .create_context(create_ctx_request, logged_in_mdn_user)
        .await
    }

    pub async fn list_contexts(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult<Vec<MdnIdentityContextResponse>> {
        self.mdn_identity_context_service(
            self.rdb_storage.connection().as_ref(),
        )
        .list_contexts(logged_in_mdn_user)
        .await
    }
}
