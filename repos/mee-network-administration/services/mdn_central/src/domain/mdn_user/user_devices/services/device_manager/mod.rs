use std::sync::Arc;

use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_user::{
            user_account::{
                api::account::middlewares::LoggedInMdnUser,
                services::account::MdnUserAccountService,
            },
            user_devices::{
                api::devices::types::{
                    ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest,
                    UserDeviceLinkageRequest,
                },
                repositories::{
                    device_requests_for_linkage::{
                        CreateRequestForLinkageDto,
                        DeviceLinkageRequestWithDevice,
                        MdnUserDeviceRequestsForLinkageRepository,
                    },
                    mdn_user_devices::{
                        AddDeviceDto, MdnUserDevicesRepository,
                    },
                },
            },
        },
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use device_did_utils::verify_device_did_signature;
use mdn_identity_agent::mdn_cloud::user_devices::api_types::UserDeviceResponse;

pub mod device_did_utils;

pub struct MdnUserDeviceManagerService<'a> {
    mdn_user_devices_repository:
        Box<dyn MdnUserDevicesRepository + Send + Sync + 'a>,
    mdn_user_device_requests_for_linkage_repository:
        Box<dyn MdnUserDeviceRequestsForLinkageRepository + Send + Sync + 'a>,
    mdn_user_auth_service: MdnUserAccountService<'a>,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl<'a> MdnUserDeviceManagerService<'a> {
    pub fn new(
        mdn_user_devices_repository: Box<
            dyn MdnUserDevicesRepository + Send + Sync + 'a,
        >,
        mdn_user_device_requests_for_linkage_repository: Box<
            dyn MdnUserDeviceRequestsForLinkageRepository + Send + Sync + 'a,
        >,
        mdn_user_auth_service: MdnUserAccountService<'a>,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            mdn_user_device_requests_for_linkage_repository,
            mdn_user_devices_repository,
            mdn_user_auth_service,
            mdn_central_authority_signature,
        }
    }

    pub async fn list_user_devices(
        &self,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<UserDeviceResponse>> {
        let acc = self
            .mdn_user_auth_service
            .get_account_by_uid_required(&user.mdn_user_uid)
            .await?;

        let user_devices = self
            .mdn_user_devices_repository
            .list_devices(acc.mdn_user_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(user_devices)
    }

    pub async fn list_user_device_linkage_requests(
        &self,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<UserDeviceLinkageRequest>> {
        let acc = self
            .mdn_user_auth_service
            .get_account_by_uid_required(&user.mdn_user_uid)
            .await?;

        Ok(self
            .mdn_user_device_requests_for_linkage_repository
            .list_requests(acc.mdn_user_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect())
    }
    pub async fn register_user_device(
        &self,
        RegisterUserDeviceRequest {
            user_device_did,
            user_device_jwt_proof,
            willow_peer_id,
            iroh_node_id,
            device_description,
        }: RegisterUserDeviceRequest,
        user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        let acc = self
            .mdn_user_auth_service
            .get_account_by_uid_required(&user.mdn_user_uid)
            .await?;

        let device_id_token = verify_device_did_signature(
            &user_device_did,
            &user_device_jwt_proof,
        )
        .await?;

        if device_id_token.iss != user_device_did {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "Issuer DID mismatch".to_string(),
            ))?;
        }

        if device_id_token.sub != user.mdn_user_uid {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "MDN user uid mismatch".to_string(),
            ))?;
        }

        if device_id_token.aud
            != self.mdn_central_authority_signature.mee_sig_did().await?
        {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "Audience mismatch".to_string(),
            ))?;
        }

        let user_devices = self
            .mdn_user_devices_repository
            .list_devices(acc.mdn_user_id)
            .await?;

        let is_device_linked = user_devices.len() == 0;

        let new_dev = self
            .mdn_user_devices_repository
            .add_device(AddDeviceDto {
                mdn_user_id: acc.mdn_user_id,
                mdn_user_device_uid: uuid::Uuid::new_v4().to_string(),
                device_description: device_description.unwrap_or(format!(
                    "User device with DID={user_device_did}"
                )),
                device_did: user_device_did,
                willow_peer_id,
                iroh_node_id,
                is_device_linked,
            })
            .await?;

        if !is_device_linked {
            self.mdn_user_device_requests_for_linkage_repository
                .create_request(CreateRequestForLinkageDto {
                    mdn_user_device_request_for_linkage_uid:
                        uuid::Uuid::new_v4().to_string(),
                    mdn_user_id: acc.mdn_user_id,
                    from_device_id: new_dev.mdn_user_device_id,
                })
                .await?;
        }

        Ok(())
    }

    pub async fn approve_user_device_linkage(
        &self,
        user: LoggedInMdnUser,
        ApproveUserDeviceLinkageRequest {
            device_approver_did,
            device_approver_jwt_proof,
            mdn_user_device_request_for_linkage_uid,
        }: ApproveUserDeviceLinkageRequest,
    ) -> MdnCentralResult {
        let acc = self
            .mdn_user_auth_service
            .get_account_by_uid_required(&user.mdn_user_uid)
            .await?;

        let dev_approver = self
            .mdn_user_devices_repository
            .get_device_by_did(acc.mdn_user_id, &device_approver_did)
            .await?
            .ok_or_else(|| {
                MdnCentralErr::MissingDbEntity(format!(
                    "Device approver with DID={device_approver_did}"
                ))
            })?;

        if !dev_approver.is_device_linked {
            Err(
                MdnCentralErr::MdnUserDeviceManagement(
                    format!("Device approver with DID={device_approver_did} has not approved (linked) itself.")
                )
            )?
        }

        let DeviceLinkageRequestWithDevice(_req, dev) = self
            .mdn_user_device_requests_for_linkage_repository
            .get_request_by_uid(
                acc.mdn_user_id,
                &mdn_user_device_request_for_linkage_uid,
            )
            .await?.ok_or_else(|| MdnCentralErr::MdnUserDeviceManagement(
                format!("Missing request ({mdn_user_device_request_for_linkage_uid}) for adding new device")))?;

        let device_id_token = verify_device_did_signature(
            &device_approver_did,
            &device_approver_jwt_proof,
        )
        .await?;

        if device_id_token.sub != dev.device_did {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "MDN user device DID subject mismatch".to_string(),
            ))?;
        }

        if device_id_token.iss != device_approver_did {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "Issuer DID mismatch".to_string(),
            ))?;
        }

        // TODO add real MDN central DID retrieval mechanism
        if device_id_token.aud != "did:key:mdn_central" {
            Err(MdnCentralErr::InvalidMdnDeviceUserAuthToken(
                "Audience mismatch".to_string(),
            ))?;
        }

        self.mdn_user_devices_repository
            .mark_device_as_linked(acc.mdn_user_id, dev.mdn_user_device_id)
            .await?;

        self.mdn_user_device_requests_for_linkage_repository
            .delete_request(
                acc.mdn_user_id,
                &mdn_user_device_request_for_linkage_uid,
            )
            .await?;

        Ok(())
    }
}
