use crate::{
    native_agent::idm::user_auth::MdnUserAccountManager,
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_custodian_storage::{
        api_client::MdnCustodianStorageApiClient,
        api_types::{MdnCustodianStorageResponse, RegisterMdnCustodianStorageRequest},
    },
    mdn_common::mdn_custodian_storage_auth::{
        EncodeMdnCustodianStorageIdTokenParams, MdnCustodianStorageIdToken,
    },
};
use async_trait::async_trait;
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver, VerificationRelationship};
use std::sync::Arc;

#[async_trait]
pub trait MdnCustodianStorageManager {
    async fn register_storage(&self) -> MdnIdentityAgentResult<()>;
    async fn list_all_storages(&self) -> MdnIdentityAgentResult<Vec<MdnCustodianStorageResponse>>;
}

pub struct MdnCustodianStorageManagerDefault {
    mdn_custodian_storage_api_client: Arc<dyn MdnCustodianStorageApiClient + Send + Sync>,
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
}

impl MdnCustodianStorageManagerDefault {
    pub fn new(
        mdn_custodian_storage_api_client: Arc<dyn MdnCustodianStorageApiClient + Send + Sync>,
        mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_custodian_storage_api_client,
            mdn_user_account_manager,
        }
    }
}

#[async_trait]
impl MdnCustodianStorageManager for MdnCustodianStorageManagerDefault {
    async fn register_storage(&self) -> MdnIdentityAgentResult<()> {
        let iroh_node_id = self
            .mdn_user_account_manager
            .get_iroh_node_key()
            .await?
            .public()
            .to_string();

        let mdn_custodian_storage_did = self.mdn_user_account_manager.get_user_device_did().await?;

        let sign_key = self
            .mdn_user_account_manager
            .get_user_device_secret_key()
            .await?;

        let mdn_user_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_decoded_token_required()
            .await?;

        let mdn_custodian_storage_did_proof =
            MdnCustodianStorageIdToken::encode(EncodeMdnCustodianStorageIdTokenParams {
                iss: mdn_custodian_storage_did.clone(),
                sub: mdn_user_auth_token.sub.clone(),
                aud: mdn_user_auth_token.iss,
                sign_key,
                kid: Some(
                    UniversalDidResolver
                        .resolve_did_for_relation(
                            &mdn_custodian_storage_did,
                            VerificationRelationship::Authentication,
                        )
                        .await?,
                ),
            })?;

        let payload = RegisterMdnCustodianStorageRequest {
            mdn_custodian_storage_did,
            mdn_custodian_storage_did_proof,
            // TODO provide willow peer id
            willow_peer_id: "todo willow peer id".to_string(),
            iroh_node_id,
        };

        Ok(self
            .mdn_custodian_storage_api_client
            .register_storage(
                payload,
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
    async fn list_all_storages(&self) -> MdnIdentityAgentResult<Vec<MdnCustodianStorageResponse>> {
        Ok(self
            .mdn_custodian_storage_api_client
            .list_all_storages(
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
}
