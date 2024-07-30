use super::{domain::SdaProfileDomainModel, dto::CreateSdaProfileDto};
use crate::{
    db_models::sda_profiles,
    error::{ApsServiceErr, ApsServiceResult},
};
use sea_orm::{
    entity::*,
    query::*,
    sea_query::{self},
};

#[async_trait::async_trait]
pub trait SdaProfileRepository {
    async fn update_sda_profile(
        &self,
        create_dto: CreateSdaProfileDto,
    ) -> ApsServiceResult<sda_profiles::Model>;
    // async fn list_all(&self) -> ApsServiceResult<Vec<sda_profiles::Model>>;
}

pub struct SdaProfileRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> SdaProfileRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> SdaProfileRepository
    for SdaProfileRepositoryImpl<'a, C>
{
    async fn update_sda_profile(
        &self,
        CreateSdaProfileDto {
            sda_profile,
            user_uid,
        }: CreateSdaProfileDto,
    ) -> ApsServiceResult<sda_profiles::Model> {
        let record_uid = uuid::Uuid::new_v4();

        let profile = sda_profiles::ActiveModel {
            record_id: NotSet,
            record_uid: Set(record_uid.to_string()),
            user_uid: Set(user_uid.clone()),
            sda_profile: Set(sda_profile.clone()),
        };

        let res = sda_profiles::Entity::insert(profile)
            .on_conflict(
                sea_query::OnConflict::column(sda_profiles::Column::UserUid)
                    .update_column(sda_profiles::Column::SdaProfile)
                    .to_owned(),
            )
            .exec(self.db_conn)
            .await?;

        Ok(sda_profiles::Model {
            record_id: res.last_insert_id,
            record_uid: record_uid.to_string(),
            user_uid,
            sda_profile,
        })
    }
    // async fn list_all(&self) -> ApsServiceResult<Vec<sda_profiles::Model>> {
    //     let res = SdaProfiles::find().all(self.db_conn).await?;

    //     Ok(res)
    // }
}

impl TryFrom<sda_profiles::Model> for SdaProfileDomainModel {
    type Error = ApsServiceErr;

    fn try_from(
        sda_profiles::Model {
            user_uid,
            sda_profile,
            ..
        }: sda_profiles::Model,
    ) -> Result<Self, Self::Error> {
        Ok(Self {
            user_uid,
            sda_profile,
        })
    }
}
