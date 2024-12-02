use crate::{
    agent_device::idm::user_auth::MdnUserAccountManager,
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_nodes::{
        api_client::MdnNodesApiClient,
        api_types::{MdnNodeResponse, RegisterMdnNodeRequest},
    },
    mdn_common::mdn_node_auth::{encode_user_node_id_token, EncodeMdnNodeUserIdTokenParams},
};
use async_trait::async_trait;
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver, VerificationRelationship};
use std::sync::Arc;

#[async_trait]
pub trait MdnUserNodesManager {
    async fn register(&self) -> MdnIdentityAgentResult<()>;
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<MdnNodeResponse>>;
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
        let mdn_node_iroh_node_id = self
            .mdn_user_account_manager
            .get_iroh_node_key()
            .await?
            .public()
            .to_string();

        let mdn_node_did = self.mdn_user_account_manager.get_user_device_did().await?;

        let sign_key = self
            .mdn_user_account_manager
            .get_user_device_secret_key()
            .await?;

        let mdn_user_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_decoded_token_required()
            .await?;

        let mdn_node_did_proof = encode_user_node_id_token(EncodeMdnNodeUserIdTokenParams {
            iss: mdn_node_did.clone(),
            sub: mdn_user_auth_token.sub.clone(),
            aud: mdn_user_auth_token.iss,
            sign_key,
            kid: Some(
                UniversalDidResolver
                    .resolve_did_for_relation(
                        &mdn_node_did,
                        VerificationRelationship::Authentication,
                    )
                    .await?,
            ),
        })?;

        let payload = RegisterMdnNodeRequest {
            mdn_node_did,
            mdn_node_did_proof,
            mdn_node_subject_id: mdn_user_auth_token.sub,
            // TODO provide willow peer id
            mdn_node_willow_peer_id: "todo willow peer id".to_string(),
            mdn_node_iroh_node_id,
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
    async fn list_all(&self) -> MdnIdentityAgentResult<Vec<MdnNodeResponse>> {
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
