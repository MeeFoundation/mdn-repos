use crate::{
    error::{MdnIdentityAgentErr, MdnIdentityAgentResult},
    mdn_cloud::mdn_capabilities::{
        api_client::MdnCapabilitiesApiClient,
        api_types::{IssueContextOpsCapTokenRequest, MdnCustodianContextOperationCapsResponse},
    },
    mdn_common::cap_definitions::{
        ContextOperationsCapabilityDefinition, MdnCapability, MdnCapabilityDefinition,
    },
    native_agent::{
        device_storage::user_local_db::MdnUserLocalDb, idm::user_auth::MdnUserAccountManager,
    },
};
use anyhow::Context;
use async_trait::async_trait;
use chrono::{Months, Utc};
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver, VerificationRelationship};
use std::sync::Arc;

#[async_trait]
pub trait MdnCapabilitiesManager {
    async fn issue_owner_context_ops_cap(&self) -> MdnIdentityAgentResult<()>;
    async fn context_ops_caps_remote(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianContextOperationCapsResponse>>;
    async fn context_ops_cap_local(&self) -> MdnIdentityAgentResult<String>;
}

pub struct MdnCapabilitiesManagerDefault {
    user_local_db: Arc<dyn MdnUserLocalDb + Send + Sync>,
    mdn_capabilities_api_client: Arc<dyn MdnCapabilitiesApiClient + Send + Sync>,
    mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
}

impl MdnCapabilitiesManagerDefault {
    pub fn new(
        user_local_db: Arc<dyn MdnUserLocalDb + Send + Sync>,
        mdn_capabilities_api_client: Arc<dyn MdnCapabilitiesApiClient + Send + Sync>,
        mdn_user_account_manager: Arc<dyn MdnUserAccountManager + Send + Sync>,
    ) -> Self {
        Self {
            mdn_user_account_manager,
            user_local_db,
            mdn_capabilities_api_client,
        }
    }
}

#[async_trait]
impl MdnCapabilitiesManager for MdnCapabilitiesManagerDefault {
    async fn issue_owner_context_ops_cap(&self) -> MdnIdentityAgentResult {
        let existing_cap_token = self.user_local_db.read_mdn_user_ctx_ops_cap_token().await?;

        if let Some(_cap_token) = existing_cap_token {
            // TODO check expiration time and refresh if required
            return Ok(());
        }

        let mdn_cloud_controller_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_token_required()
            .await?;

        let now = Utc::now();
        let exp = now
            .checked_add_months(Months::new(1))
            .context("chrono time manipulation issue")?
            .timestamp();

        let user_auth_token = self
            .mdn_user_account_manager
            .get_user_auth_decoded_token_required()
            .await?;

        let cap = MdnCapability {
            from: user_auth_token.mdn_user_context_scoped_uid.clone(),
            to: user_auth_token.mdn_user_custodian_uid,
            sub: user_auth_token.mdn_user_context_scoped_uid,
            cap: MdnCapabilityDefinition::ContextOperations(
                ContextOperationsCapabilityDefinition::Any,
            ),
            exp,
        };

        let device_did = self.mdn_user_account_manager.get_user_device_did().await?;

        let sign_key = self
            .mdn_user_account_manager
            .get_user_device_secret_key()
            .await?;

        let auth_did_id = UniversalDidResolver
            .resolve_did_for_relation(&device_did, VerificationRelationship::Authentication)
            .await?;

        let cap_token = cap.encode(sign_key, auth_did_id)?;

        self.mdn_capabilities_api_client
            .issue_context_ops_cap(
                IssueContextOpsCapTokenRequest {
                    cap_token: cap_token.clone(),
                },
                &mdn_cloud_controller_auth_token,
            )
            .await?;

        self.user_local_db
            .write_mdn_user_ctx_ops_cap_token(&cap_token)
            .await?;

        Ok(())
    }
    async fn context_ops_cap_local(&self) -> MdnIdentityAgentResult<String> {
        let res = self
            .user_local_db
            .read_mdn_user_ctx_ops_cap_token()
            .await?
            .ok_or_else(|| {
                MdnIdentityAgentErr::MdnCapabilities(
                    "Missing context operations cap token".to_string(),
                )
            })?;

        Ok(res)
    }
    async fn context_ops_caps_remote(
        &self,
    ) -> MdnIdentityAgentResult<Vec<MdnCustodianContextOperationCapsResponse>> {
        self.mdn_capabilities_api_client
            .context_ops_caps(
                &self
                    .mdn_user_account_manager
                    .get_user_auth_token_required()
                    .await?,
            )
            .await
    }
}
