use super::{
    api_types::CreateSdaProfileRequest, dto::CreateSdaProfileDto,
    repository::SdaProfileRepository,
};
use crate::error::ApsServiceResult;

pub struct SdaProfileService<'a> {
    sda_profile_repository: Box<dyn SdaProfileRepository + Send + Sync + 'a>,
}

impl<'a> SdaProfileService<'a> {
    pub fn new(
        sda_profile_repository: Box<
            dyn SdaProfileRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            sda_profile_repository,
        }
    }
    pub async fn update_sda_profile(
        &self,
        CreateSdaProfileRequest {
            user_uid,
            sda_profile,
        }: CreateSdaProfileRequest,
    ) -> ApsServiceResult<()> {
        self.sda_profile_repository
            .update_sda_profile(CreateSdaProfileDto {
                user_uid,
                sda_profile,
            })
            .await?;

        Ok(())
    }
}
