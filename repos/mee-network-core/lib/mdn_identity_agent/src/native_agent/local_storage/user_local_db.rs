use crate::{
    error::MdnIdentityAgentResult,
    mdn_common::local_storage::local_kvdb::{LocalKvDbExt, LocalKvDbRedb},
};
use async_trait::async_trait;
use mee_crypto::jwk::Jwk;
use mee_data_sync::iroh::key::SecretKey;
use std::sync::Arc;

#[async_trait]
pub trait MdnUserLocalDb {
    async fn read_user_device_did(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn write_user_device_did(&self, did: &str) -> MdnIdentityAgentResult;

    async fn read_user_device_secret_key(&self) -> MdnIdentityAgentResult<Option<Jwk>>;
    async fn write_user_device_secret_key(&self, jwk: Jwk) -> MdnIdentityAgentResult;

    async fn read_mdn_user_auth_token(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn write_mdn_user_auth_token(&self, token: &str) -> MdnIdentityAgentResult;

    async fn read_mdn_user_ctx_ops_cap_token(&self) -> MdnIdentityAgentResult<Option<String>>;
    async fn write_mdn_user_ctx_ops_cap_token(&self, cap_token: &str) -> MdnIdentityAgentResult;

    async fn read_iroh_node_secret_key(&self) -> MdnIdentityAgentResult<Option<SecretKey>>;
    async fn write_iroh_node_secret_key(&self, secret_key: SecretKey) -> MdnIdentityAgentResult;
}

const MDN_USER_CTX_OPS_CAP_TOKEN: &str = "MDN_USER_CTX_OPS_CAP_TOKEN";
const MDN_USER_DEVICE_DID: &str = "MDN_USER_DEVICE_DID";
const MDN_USER_AUTH_TOKEN: &str = "MDN_USER_AUTH_TOKEN";
const MDN_USER_SECRET_KEY: &str = "MDN_USER_SECRET_KEY";
const IROH_NODE_SECRET_KEY: &str = "IROH_NODE_SECRET_KEY";

pub struct MdnUserLocalDbDefault {
    local_kvdb: LocalKvDbExt,
}

impl MdnUserLocalDbDefault {
    pub async fn try_new(local_db_file_path: String) -> MdnIdentityAgentResult<Self> {
        Ok(Self {
            local_kvdb: LocalKvDbExt::new(Arc::new(
                LocalKvDbRedb::try_new(local_db_file_path.clone(), "USER_TABLE".to_string())
                    .await?,
            )),
        })
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

    async fn read_mdn_user_ctx_ops_cap_token(&self) -> MdnIdentityAgentResult<Option<String>> {
        Ok(self
            .local_kvdb
            .0
            .get_string_value(MDN_USER_CTX_OPS_CAP_TOKEN.to_string())
            .await?)
    }
    async fn write_mdn_user_ctx_ops_cap_token(&self, cap_token: &str) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .0
            .set_string_value(
                MDN_USER_CTX_OPS_CAP_TOKEN.to_string(),
                cap_token.to_string(),
            )
            .await?)
    }

    async fn read_iroh_node_secret_key(&self) -> MdnIdentityAgentResult<Option<SecretKey>> {
        Ok(self
            .local_kvdb
            .get_json_value(IROH_NODE_SECRET_KEY.to_string())
            .await?)
    }
    async fn write_iroh_node_secret_key(&self, secret_key: SecretKey) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .set_json_value(IROH_NODE_SECRET_KEY.to_string(), &secret_key)
            .await?)
    }

    async fn read_user_device_secret_key(&self) -> MdnIdentityAgentResult<Option<Jwk>> {
        Ok(self
            .local_kvdb
            .get_json_value(MDN_USER_SECRET_KEY.to_string())
            .await?)
    }
    async fn write_user_device_secret_key(&self, jwk: Jwk) -> MdnIdentityAgentResult {
        Ok(self
            .local_kvdb
            .set_json_value(MDN_USER_SECRET_KEY.to_string(), &jwk)
            .await?)
    }
}
