use super::{
    api::devices::types::{
        ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest,
        UserDeviceLinkageRequest,
    },
    repositories::{
        device_requests_for_linkage::{
            MdnUserDeviceRequestsForLinkageRepository,
            MdnUserDeviceRequestsForLinkageRepositoryImpl,
        },
        mdn_user_devices::{
            MdnUserDevicesRepository, MdnUserDevicesRepositoryImpl,
        },
    },
    services::device_manager::MdnUserDeviceManagerService,
};
use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_user::user_account::{
            api::account::middlewares::LoggedInMdnUser,
            controller::MdnUserAccountController,
        },
    },
    error::MdnCentralResult,
};
use mdn_identity_agent::mdn_cloud::user_devices::api_types::UserDeviceResponse;
use mee_db_utils::sql_storage::RbdStorage;
use sea_orm::ConnectionTrait;
use std::sync::Arc;

#[derive(Clone)]
pub struct MdnUserDevicesController {
    rdb_storage: RbdStorage,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl MdnUserDevicesController {
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

    pub fn user_device_manager_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> MdnUserDeviceManagerService<'a> {
        MdnUserDeviceManagerService::new(
            Box::new(self.mdn_user_devices_repository(tx)),
            Box::new(self.mdn_user_device_requests_for_linkage_repository(tx)),
            MdnUserAccountController::user_account_service(
                tx,
                self.mdn_central_authority_signature.clone(),
            ),
            self.mdn_central_authority_signature.clone(),
        )
    }
    pub fn mdn_user_devices_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl MdnUserDevicesRepository + 'a {
        MdnUserDevicesRepositoryImpl::new(tx)
    }
    pub fn mdn_user_device_requests_for_linkage_repository<
        'a,
        C: ConnectionTrait,
    >(
        &self,
        tx: &'a C,
    ) -> impl MdnUserDeviceRequestsForLinkageRepository + 'a {
        MdnUserDeviceRequestsForLinkageRepositoryImpl::new(tx)
    }

    pub async fn approve_user_device_linkage(
        &self,
        user: LoggedInMdnUser,
        approve: ApproveUserDeviceLinkageRequest,
    ) -> MdnCentralResult {
        self.user_device_manager_service(&*self.rdb_storage.connection())
            .approve_user_device_linkage(user, approve)
            .await
    }
    pub async fn list_user_device_linkage_requests(
        &self,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<UserDeviceLinkageRequest>> {
        self.user_device_manager_service(&*self.rdb_storage.connection())
            .list_user_device_linkage_requests(user)
            .await
    }
    pub async fn list_user_devices(
        &self,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<UserDeviceResponse>> {
        self.user_device_manager_service(&*self.rdb_storage.connection())
            .list_user_devices(user)
            .await
    }
    pub async fn register_user_device(
        &self,
        dev: RegisterUserDeviceRequest,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        self.user_device_manager_service(&*self.rdb_storage.connection())
            .register_user_device(dev, user)
            .await
    }
}
