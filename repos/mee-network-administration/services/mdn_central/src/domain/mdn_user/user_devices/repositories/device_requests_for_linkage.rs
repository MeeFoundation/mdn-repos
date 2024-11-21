use crate::{
    db_models::{
        mdn_user_device_requests_for_linkage, mdn_user_devices, prelude::*,
    },
    domain::mdn_user::user_devices::api::devices::types::UserDeviceLinkageRequest,
    error::MdnCentralResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct CreateRequestForLinkageDto {
    pub mdn_user_id: i64,
    pub from_device_id: i64,
    pub mdn_user_device_request_for_linkage_uid: String,
}

pub struct DeviceLinkageRequestWithDevice(
    pub mdn_user_device_requests_for_linkage::Model,
    pub mdn_user_devices::Model,
);

impl From<DeviceLinkageRequestWithDevice> for UserDeviceLinkageRequest {
    fn from(
        DeviceLinkageRequestWithDevice(req, dev): DeviceLinkageRequestWithDevice,
    ) -> Self {
        UserDeviceLinkageRequest {
            device_description: dev.device_description,
            device_did: dev.device_did,
            mdn_user_device_uid: dev.mdn_user_device_uid,
            mdn_user_device_request_for_linkage_uid: req
                .mdn_user_device_request_for_linkage_uid,
        }
    }
}

#[async_trait]
pub trait MdnUserDeviceRequestsForLinkageRepository {
    async fn create_request(
        &self,
        req: CreateRequestForLinkageDto,
    ) -> MdnCentralResult<mdn_user_device_requests_for_linkage::Model>;
    async fn list_requests(
        &self,
        user_id: i64,
    ) -> MdnCentralResult<Vec<DeviceLinkageRequestWithDevice>>;
    async fn delete_request(
        &self,
        user_id: i64,
        mdn_user_device_request_for_linkage_uid: &str,
    ) -> MdnCentralResult;
    async fn get_request_by_uid(
        &self,
        user_id: i64,
        mdn_user_device_request_for_linkage_uid: &str,
    ) -> MdnCentralResult<Option<DeviceLinkageRequestWithDevice>>;
}

pub struct MdnUserDeviceRequestsForLinkageRepositoryImpl<'a, C: ConnectionTrait>
{
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait>
    MdnUserDeviceRequestsForLinkageRepositoryImpl<'a, C>
{
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnUserDeviceRequestsForLinkageRepository
    for MdnUserDeviceRequestsForLinkageRepositoryImpl<'a, C>
{
    async fn create_request(
        &self,
        CreateRequestForLinkageDto {
            mdn_user_id,
            from_device_id,
            mdn_user_device_request_for_linkage_uid,
        }: CreateRequestForLinkageDto,
    ) -> MdnCentralResult<mdn_user_device_requests_for_linkage::Model> {
        Ok(mdn_user_device_requests_for_linkage::ActiveModel {
            mdn_user_device_request_for_linkage_id: NotSet,
            mdn_user_device_request_for_linkage_uid: Set(
                mdn_user_device_request_for_linkage_uid,
            ),
            mdn_user_id: Set(mdn_user_id),
            from_device_id: Set(from_device_id),
        }
        .insert(self.db_conn)
        .await?)
    }
    async fn list_requests(
        &self,
        user_id: i64,
    ) -> MdnCentralResult<Vec<DeviceLinkageRequestWithDevice>> {
        let res = MdnUserDeviceRequestsForLinkage::find()
            .filter(
                mdn_user_device_requests_for_linkage::Column::MdnUserId
                    .eq(user_id),
            )
            .find_also_related(MdnUserDevices)
            .all(self.db_conn)
            .await?;

        let res = res
            .into_iter()
            .filter_map(|(req, dev)| {
                dev.map(|d| DeviceLinkageRequestWithDevice(req, d))
            })
            .collect();

        Ok(res)
    }

    async fn get_request_by_uid(
        &self,
        user_id: i64,
        mdn_user_device_request_for_linkage_uid: &str,
    ) -> MdnCentralResult<Option<DeviceLinkageRequestWithDevice>> {
        let res = MdnUserDeviceRequestsForLinkage::find()
            .filter(
                mdn_user_device_requests_for_linkage::Column::MdnUserId
                    .eq(user_id),
            )
            .filter(
                mdn_user_device_requests_for_linkage::Column::MdnUserDeviceRequestForLinkageUid
                    .eq(mdn_user_device_request_for_linkage_uid)
            )
            .find_also_related(MdnUserDevices)
            .one(self.db_conn)
            .await?;

        let res = res.and_then(|(req, dev)| {
            dev.map(|d| DeviceLinkageRequestWithDevice(req, d))
        });

        Ok(res)
    }
    async fn delete_request(
        &self,
        user_id: i64,
        mdn_user_device_request_for_linkage_uid: &str,
    ) -> MdnCentralResult {
        let res = MdnUserDeviceRequestsForLinkage::find()
            .filter(
                mdn_user_device_requests_for_linkage::Column::MdnUserId
                    .eq(user_id),
            )
            .filter(
                mdn_user_device_requests_for_linkage::Column::MdnUserDeviceRequestForLinkageUid
                    .eq(mdn_user_device_request_for_linkage_uid)
            )
            .one(self.db_conn)
            .await?;

        if let Some(res) = res {
            res.delete(self.db_conn).await?;
        }

        Ok(())
    }
}
