use crate::db_models::mdn_user_devices;
pub use mdn_identity_agent::mdn_cloud::user_devices::api_types::*;

impl From<mdn_user_devices::Model> for UserDeviceResponse {
    fn from(
        mdn_user_devices::Model {
            mdn_user_device_uid,
            device_description,
            is_device_linked,
            device_did,
            ..
        }: mdn_user_devices::Model,
    ) -> Self {
        Self {
            mdn_user_device_uid,
            device_description,
            is_device_linked,
            device_did,
        }
    }
}
