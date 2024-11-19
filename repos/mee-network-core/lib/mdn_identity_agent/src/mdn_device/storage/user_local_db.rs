use super::local_kvdb::LocalKvDbExt;
use crate::{error::MdnIdentityAgentResult, mdn_device::storage::local_kvdb::LocalKvDb};
use async_trait::async_trait;
use mee_data_sync::iroh::iroh_net;
use std::sync::Arc;

#[async_trait]
pub trait MdnUserLocalDb {
    async fn read_user_device_did(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn write_user_device_did(&self, did: &str) -> MdnIdentityAgentResult;

    async fn read_mdn_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn write_mdn_user_auth_token(&self, token: &str) -> MdnIdentityAgentResult;

    async fn read_iroh_node_secret_key(
        &self,
    ) -> MdnIdentityAgentResult<Option<iroh_net::key::SecretKey>>;
    async fn write_iroh_node_secret_key(
        &self,
        secret_key: iroh_net::key::SecretKey,
    ) -> MdnIdentityAgentResult;
}

const MDN_USER_DEVICE_DID: &str = "MDN_USER_DEVICE_DID";
const MDN_USER_AUTH_TOKEN: &str = "MDN_USER_AUTH_TOKEN";
const IROH_NODE_SECRET_KEY: &str = "IROH_NODE_SECRET_KEY";

pub struct MdnUserLocalDbDefault {
    local_kvdb: LocalKvDbExt,
}

impl MdnUserLocalDbDefault {
    pub fn new(local_kvdb: Arc<dyn LocalKvDb + Send + Sync>) -> Self {
        Self {
            local_kvdb: LocalKvDbExt::new(local_kvdb),
        }
    }
}

#[async_trait]
impl MdnUserLocalDb for MdnUserLocalDbDefault {
    async fn read_user_device_did(&self) -> MdnIdentityAgentResult<Option<String>> {
        Ok(self
            .local_kvdb
            .0
            .get_string_value(MDN_USER_DEVICE_DID.to_string())
            .await?)
    }
    async fn write_user_device_did(&self, did: &str) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .0
            .set_string_value(MDN_USER_DEVICE_DID.to_string(), did.to_string())
            .await?)
    }

    async fn read_mdn_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>> {
        Ok(self
            .local_kvdb
            .0
            .get_string_value(MDN_USER_AUTH_TOKEN.to_string())
            .await?)
    }
    async fn write_mdn_user_auth_token(&self, token: &str) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .0
            .set_string_value(MDN_USER_AUTH_TOKEN.to_string(), token.to_string())
            .await?)
    }
    async fn read_iroh_node_secret_key(
        &self,
    ) -> MdnIdentityAgentResult<Option<iroh_net::key::SecretKey>> {
        Ok(self
            .local_kvdb
            .get_json_value(IROH_NODE_SECRET_KEY.to_string())
            .await?)
    }
    async fn write_iroh_node_secret_key(
        &self,
        secret_key: iroh_net::key::SecretKey,
    ) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .set_json_value(IROH_NODE_SECRET_KEY.to_string(), &secret_key)
            .await?)
    }
}
