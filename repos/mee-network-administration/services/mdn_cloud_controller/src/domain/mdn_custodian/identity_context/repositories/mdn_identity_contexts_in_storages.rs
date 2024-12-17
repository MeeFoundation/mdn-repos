use crate::error::MdnCloudControllerResult;
use async_trait::async_trait;

pub struct CreateMdnContextInStorageDto {
    pub mdn_identity_context_id: i64,
    pub mdn_custodian_storage_id: i64,
}

#[async_trait]
pub trait MdnContextInStorageRepository {
    async fn link_context_to_storage(
        &self,
        payload: CreateMdnContextInStorageDto,
    ) -> MdnCloudControllerResult;
}
