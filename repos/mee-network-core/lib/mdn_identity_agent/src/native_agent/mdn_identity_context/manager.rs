use crate::{
    error::MdnIdentityAgentResult,
    mdn_cloud::mdn_identity_context::api_types::MdnIdentityContextResponse,
};
use async_trait::async_trait;

#[async_trait]
pub trait MdnIdentityContextManager {
    async fn create_context(&self) -> MdnIdentityAgentResult<MdnIdentityContextResponse>;
}
