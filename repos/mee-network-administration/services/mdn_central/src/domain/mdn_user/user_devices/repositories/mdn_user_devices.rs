use crate::{
    db_models::{mdn_user_devices, prelude::*},
    error::{MdnCentralErr, MdnCentralResult},
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct AddDeviceDto {
    pub mdn_user_id: i64,
    pub mdn_user_device_uid: String,
    pub device_description: String,
    pub is_device_linked: bool,
    pub device_did: String,
    pub willow_peer_id: String,
    pub iroh_node_id: String,
}

#[async_trait]
pub trait MdnUserDevicesRepository {
    async fn add_device(
        &self,
        add_dev: AddDeviceDto,
    ) -> MdnCentralResult<mdn_user_devices::Model>;
    async fn mark_device_as_linked(
        &self,
        user_id: i64,
        dev_id: i64,
    ) -> MdnCentralResult<mdn_user_devices::Model>;
    async fn list_devices(
        &self,
        user_id: i64,
    ) -> MdnCentralResult<Vec<mdn_user_devices::Model>>;
    async fn get_device_by_id(
        &self,
        user_id: i64,
        dev_id: i64,
    ) -> MdnCentralResult<Option<mdn_user_devices::Model>>;
    async fn get_device_by_did(
        &self,
        user_id: i64,
        dev_did: &str,
    ) -> MdnCentralResult<Option<mdn_user_devices::Model>>;
}

pub struct MdnUserDevicesRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnUserDevicesRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnUserDevicesRepository
    for MdnUserDevicesRepositoryImpl<'a, C>
{
    async fn add_device(
        &self,
        AddDeviceDto {
            mdn_user_id,
            mdn_user_device_uid,
            device_description,
            is_device_linked,
            device_did,
            willow_peer_id,
            iroh_node_id,
        }: AddDeviceDto,
    ) -> MdnCentralResult<mdn_user_devices::Model> {
        let dev = mdn_user_devices::ActiveModel {
            mdn_user_device_id: NotSet,
            mdn_user_id: Set(mdn_user_id),
            mdn_user_device_uid: Set(mdn_user_device_uid),
            device_description: Set(device_description),
            is_device_linked: Set(is_device_linked),
            device_did: Set(device_did),
            willow_peer_id: Set(willow_peer_id),
            iroh_node_id: Set(iroh_node_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(dev)
    }
    async fn list_devices(
        &self,
        user_id: i64,
    ) -> MdnCentralResult<Vec<mdn_user_devices::Model>> {
        let dev = MdnUserDevices::find()
            .filter(mdn_user_devices::Column::MdnUserId.eq(user_id))
            .all(self.db_conn)
            .await?;

        Ok(dev)
    }
    async fn get_device_by_id(
        &self,
        user_id: i64,
        dev_id: i64,
    ) -> MdnCentralResult<Option<mdn_user_devices::Model>> {
        let dev = MdnUserDevices::find()
            .filter(mdn_user_devices::Column::MdnUserDeviceId.eq(dev_id))
            .filter(mdn_user_devices::Column::MdnUserId.eq(user_id))
            .one(self.db_conn)
            .await?;

        Ok(dev)
    }
    async fn get_device_by_did(
        &self,
        user_id: i64,
        dev_did: &str,
    ) -> MdnCentralResult<Option<mdn_user_devices::Model>> {
        let dev = MdnUserDevices::find()
            .filter(mdn_user_devices::Column::DeviceDid.eq(dev_did))
            .filter(mdn_user_devices::Column::MdnUserId.eq(user_id))
            .one(self.db_conn)
            .await?;

        Ok(dev)
    }
    async fn mark_device_as_linked(
        &self,
        user_id: i64,
        dev_id: i64,
    ) -> MdnCentralResult<mdn_user_devices::Model> {
        let dev = self.get_device_by_id(user_id, dev_id).await?;

        match dev {
            Some(dev) => {
                let mut dev = dev.into_active_model();
                dev.is_device_linked = Set(true);

                Ok(dev.update(self.db_conn).await?)
            }
            None => Err(MdnCentralErr::MissingDbEntity(format!(
                "user device with DID={dev_id}"
            ))),
        }
    }
}
