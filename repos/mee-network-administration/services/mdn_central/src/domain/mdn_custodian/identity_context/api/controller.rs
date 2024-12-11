use crate::{
    domain::{
        mdn_custodian::identity_context::{
            repositories::{
                mdn_context_scoped_ids::MdnContextScopedIdsRepositoryImpl,
                mdn_identity_contexts::MdnIdentityContextsRepositoryImpl,
            },
            services::mdn_identity_context::MdnIdentityContextService,
        },
        mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    },
    error::MdnCentralResult,
};
use mdn_identity_agent::mdn_cloud::mdn_identity_context::api_types::{
    CreateMdnIdentityContextRequest, MdnIdentityContextResponse,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;

#[derive(Clone)]
pub struct MdnIdentityContextController {
    rdb_storage: RbdStorage,
}

impl MdnIdentityContextController {
    pub fn new(rdb_storage: RbdStorage) -> Self {
        Self { rdb_storage }
    }

    pub fn mdn_identity_context_service_factory<'a, C: ConnectionTrait>(
        tx: &'a C,
    ) -> MdnIdentityContextService<'a> {
        MdnIdentityContextService::new(
            Box::new(MdnIdentityContextsRepositoryImpl::new(tx)),
            Box::new(MdnContextScopedIdsRepositoryImpl::new(tx)),
        )
    }
    pub async fn create_context(
        &self,
        create_ctx_request: CreateMdnIdentityContextRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<MdnIdentityContextResponse> {
        Self::mdn_identity_context_service_factory(
            self.rdb_storage.connection().as_ref(),
        )
        .create_context(create_ctx_request, logged_in_mdn_user)
        .await
    }

    pub async fn list_contexts(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<MdnIdentityContextResponse>> {
        Self::mdn_identity_context_service_factory(
            self.rdb_storage.connection().as_ref(),
        )
        .list_contexts(logged_in_mdn_user)
        .await
    }
}
