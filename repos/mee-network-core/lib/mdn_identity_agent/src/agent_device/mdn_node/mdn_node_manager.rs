use crate::{
    agent_device::idm::user_auth::MdnUserAccountManager,
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_node_hosting_platforms::{
        api_client::MdnNodesApiClient,
        api_types::{MdnNodeHostingPlatformResponse, RegisterMdnNodeHostingPlatformRequest},
    },
    mdn_common::mdn_node_auth::{encode_user_node_id_token, EncodeMdnNodeUserIdTokenParams},
};
use async_trait::async_trait;
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver, VerificationRelationship};
use std::sync::Arc;

#[async_trait]
pub trait MdnUserNodesManager {
    async fn register(&self) -> MdnIdentityAgentResult<()>;
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<MdnNodeHostingPlatformResponse>>;
}

pub struct MdnUserNodesManagerDefault {
    mdn_nodes_api_client: Arc<dyn MdnNodesApiClient + Send + Sync>,
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
}

impl MdnUserNodesManagerDefault {
    pub fn new(
        mdn_nodes_api_client: Arc<dyn MdnNodesApiClient + Send + Sync>,
        mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_nodes_api_client,
            mdn_user_account_manager,
        }
    }
}

#[async_trait]
impl MdnUserNodesManager for MdnUserNodesManagerDefault {
    async fn register(&self) -> MdnIdentityAgentResult<()> {
        let iroh_node_id = self
            .mdn_user_account_manager
            .get_iroh_node_key()
            .await?
            .public()
            .to_string();

        let node_hosting_platform_did = self.mdn_user_account_manager.get_user_device_did().await?;

        let sign_key = self
            .mdn_user_account_manager
            .get_user_device_secret_key()
            .await?;

        let mdn_user_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_decoded_token_required()
            .await?;

        let node_hosting_platform_did_proof =
            encode_user_node_id_token(EncodeMdnNodeUserIdTokenParams {
                iss: node_hosting_platform_did.clone(),
                sub: mdn_user_auth_token.sub.clone(),
                aud: mdn_user_auth_token.iss,
                sign_key,
                kid: Some(
                    UniversalDidResolver
                        .resolve_did_for_relation(
                            &node_hosting_platform_did,
                            VerificationRelationship::Authentication,
                        )
                        .await?,
                ),
            })?;

        let payload = RegisterMdnNodeHostingPlatformRequest {
            node_hosting_platform_did,
            node_hosting_platform_did_proof,
            // TODO provide willow peer id
            willow_peer_id: "todo willow peer id".to_string(),
            iroh_node_id,
        };

        Ok(self
            .mdn_nodes_api_client
            .register(
                payload,
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<MdnNodeHostingPlatformResponse>> {
        Ok(self
            .mdn_nodes_api_client
            .list_all(
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await?)
    }
}
