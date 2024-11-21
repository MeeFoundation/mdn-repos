use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::user_devices::{
        api_client::MdnUserDevicesApiClient,
        api_types::{
            ApproveUserDeviceLinkageRequest, RegisterUserDeviceRequest, UserDeviceLinkageRequest,
            UserDeviceResponse,
        },
    },
    mdn_device::idm::{
        device_auth::{encode_mdn_device_user_id_token, EncodeMdnDeviceUserIdTokenParams},
        user_auth::MdnUserAccountManager,
    },
};
use async_trait::async_trait;
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver, VerificationRelationship};
use std::sync::Arc;

#[async_trait]
pub trait MdnUserDevicesManager {
    async fn register(&self, device_description: Option<String>) -> MdnIdentityAgentResult<()>;
    async fn linkage_requests(&self) -> MdnIdentityAgentResult<Vec<UserDeviceLinkageRequest>>;
    async fn approve_linkage(
        &self,
        payload: ApproveUserDeviceLinkageRequest,
    ) -> MdnIdentityAgentResult<()>;
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<UserDeviceResponse>>;
}

pub struct MdnUserDevicesManagerDefault {
    mdn_user_devices_api_client: Arc<dyn MdnUserDevicesApiClient + Send + Sync>,
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
}

impl MdnUserDevicesManagerDefault {
    pub fn new(
        mdn_user_devices_api_client: Arc<dyn MdnUserDevicesApiClient + Send + Sync>,
        mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_user_devices_api_client,
            mdn_user_account_manager,
        }
    }
}

#[async_trait]
impl MdnUserDevicesManager for MdnUserDevicesManagerDefault {
    async fn register(&self, device_description: Option<String>) -> MdnIdentityAgentResult<()> {
        let iroh_node_id = self
            .mdn_user_account_manager
            .get_iroh_node_key()
            .await?
            .public()
            .to_string();

        let device_did = self.mdn_user_account_manager.get_user_device_did().await?;

        let sign_key = self
            .mdn_user_account_manager
            .get_user_device_secret_key()
            .await?;

        let mdn_user_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_decoded_token_required()
            .await?;

        let user_device_jwt_proof =
            encode_mdn_device_user_id_token(EncodeMdnDeviceUserIdTokenParams {
                iss: device_did.clone(),
                sub: mdn_user_auth_token.sub,
                aud: mdn_user_auth_token.iss,
                sign_key,
                kid: Some(
                    UniversalDidResolver
                        .resolve_did_for_relation(
                            &device_did,
                            VerificationRelationship::Authentication,
                        )
                        .await?,
                ),
            })?;

        let payload = RegisterUserDeviceRequest {
            user_device_did: device_did,
            user_device_jwt_proof,
            // TODO provide willow peer id
            willow_peer_id: "todo willow peer id".to_string(),
            iroh_node_id,
            device_description,
        };

        Ok(self
            .mdn_user_devices_api_client
            .register(
                payload,
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
    async fn linkage_requests(&self) -> MdnIdentityAgentResult<Vec<UserDeviceLinkageRequest>> {
        Ok(self
            .mdn_user_devices_api_client
            .linkage_requests(
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
    async fn approve_linkage(
        &self,
        payload: ApproveUserDeviceLinkageRequest,
    ) -> MdnIdentityAgentResult<()> {
        Ok(self
            .mdn_user_devices_api_client
            .approve_linkage(
                payload,
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<UserDeviceResponse>> {
        Ok(self
            .mdn_user_devices_api_client
            .list_all(
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
}
