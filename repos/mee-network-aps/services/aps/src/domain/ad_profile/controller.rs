use super::sda_profiles::{
    api_types::CreateSdaProfileRequest,
    repository::{SdaProfileRepository, SdaProfileRepositoryImpl},
    service::SdaProfileService,
};
use crate::error::ApsServiceResult;
use mee_db_utils::sql_storage::IRbdStorage;
use sea_orm::{ConnectionTrait, TransactionTrait};
use std::sync::Arc;

#[derive(Clone)]
pub struct AdProfileController {
    rdb_storage: Arc<dyn IRbdStorage + Sync + Send>,
}

impl AdProfileController {
    pub fn new(rdb_storage: Arc<dyn IRbdStorage + Sync + Send>) -> Self {
        Self { rdb_storage }
    }
    pub fn user_account_service<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> SdaProfileService<'a> {
        SdaProfileService::new(Box::new(self.user_account_repository(tx)))
    }
    pub fn user_account_repository<'a, C: ConnectionTrait>(
        &self,
        tx: &'a C,
    ) -> impl SdaProfileRepository + 'a {
        SdaProfileRepositoryImpl::new(tx)
    }
    pub async fn add_sda_profile(
        &self,
        payload: CreateSdaProfileRequest,
    ) -> ApsServiceResult {
        let this = self.clone();

        let res = self
            .rdb_storage
            .connection()
            .transaction(|tx| {
                Box::pin(async move {
                    let user_account_service = this.user_account_service(tx);
                    let res =
                        user_account_service.add_sda_profile(payload).await?;

                    Ok(res)
                })
            })
            .await?;

        Ok(res)
    }
}
