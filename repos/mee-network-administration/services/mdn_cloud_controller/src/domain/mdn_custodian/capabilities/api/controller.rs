use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepositoryImpl,
            capabilities::{
                api::types::{
                    IssueContextOpsCapTokenRequest,
                    MdnCustodianContextOperationCapsResponse,
                },
                repositories::mdn_custodian_context_operation_caps::CustodianContextOperationCapsRepositoryImpl,
                services::mdn_capabilities::MdnCapabilitiesService,
            },
        },
        mdn_user::user_account::api::{
            controller::MdnUserAccountController, middlewares::LoggedInMdnUser,
        },
    },
    error::MdnCloudControllerResult,
};
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnCapabilitiesController {
    rdb_storage: RbdStorage,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnCapabilitiesController {
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
    pub fn mdn_capabilities_service_factory<'a, C: ConnectionTrait>(
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
        tx: &'a C,
    ) -> MdnCapabilitiesService<'a> {
        MdnCapabilitiesService::new(
            Box::new(CustodianContextOperationCapsRepositoryImpl::new(tx)),
            Box::new(MdnCustodiansRepositoryImpl::new(tx)),
            MdnUserAccountController::user_account_service_factory(
                tx,
                mdn_cloud_controller_authority_signature,
            ),
        )
    }
    fn mdn_capabilities_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> MdnCapabilitiesService<'a> {
        Self::mdn_capabilities_service_factory(
            self.mdn_cloud_controller_authority_signature.clone(),
            tx,
        )
    }
    pub async fn issue_context_ops_cap(
        &self,
        req: IssueContextOpsCapTokenRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult {
        self.mdn_capabilities_service(self.rdb_storage.connection().as_ref())
            .issue_context_ops_cap(req, logged_in_mdn_user)
            .await
    }
    pub async fn context_ops_caps(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult<Vec<MdnCustodianContextOperationCapsResponse>> {
        let res = self
            .mdn_capabilities_service(self.rdb_storage.connection().as_ref())
            .context_ops_caps(logged_in_mdn_user)
            .await?;

        Ok(res)
    }
}
