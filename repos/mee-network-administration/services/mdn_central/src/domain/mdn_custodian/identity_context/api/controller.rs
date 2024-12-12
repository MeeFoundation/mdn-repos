use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::identity_context::{
            repositories::{
                mdn_context_scoped_ids::MdnContextScopedIdsRepositoryImpl,
                mdn_identity_contexts::MdnIdentityContextsRepositoryImpl,
            },
            services::mdn_identity_context::MdnIdentityContextService,
        },
        mdn_user::user_account::api::{
            controller::MdnUserAccountController, middlewares::LoggedInMdnUser,
        },
    },
    error::MdnCentralResult,
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
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnIdentityContextController {
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

    pub fn mdn_identity_context_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> MdnIdentityContextService<'a> {
        Self::mdn_identity_context_service_factory(
            self.mdn_central_authority_signature.clone(),
            tx,
        )
    }
    pub fn mdn_identity_context_service_factory<'a, C: ConnectionTrait>(
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnIdentityContextService<'a> {
        MdnIdentityContextService::new(
            Box::new(MdnIdentityContextsRepositoryImpl::new(tx)),
            Box::new(MdnContextScopedIdsRepositoryImpl::new(tx)),
            MdnUserAccountController::user_account_service_factory(
                tx,
                mdn_central_authority_signature,
            ),
            MdnUserAccountController::mdn_custodians_service_factory(tx),
        )
    }
    pub async fn create_context(
        &self,
        create_ctx_request: CreateMdnIdentityContextRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<MdnIdentityContextResponse> {
        self.mdn_identity_context_service(
            self.rdb_storage.connection().as_ref(),
        )
        .create_context(create_ctx_request, logged_in_mdn_user)
        .await
    }

    pub async fn list_contexts(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<MdnIdentityContextResponse>> {
        self.mdn_identity_context_service(
            self.rdb_storage.connection().as_ref(),
        )
        .list_contexts(logged_in_mdn_user)
        .await
    }
}
