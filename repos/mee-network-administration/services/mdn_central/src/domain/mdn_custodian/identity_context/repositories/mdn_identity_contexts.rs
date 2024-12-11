use crate::{
    db_models::{mdn_identity_contexts, prelude::*},
    error::MdnCentralResult,
};
use async_trait::async_trait;
use sea_orm::{entity::*, query::*};

pub struct CreateContextDto {
    pub mdn_identity_context_uid: String,
    pub willow_namespace_id: String,
    pub context_scoped_subject_id: i64,
}

#[async_trait]
pub trait MdnIdentityContextsRepository {
    async fn create_context(
        &self,
        create_ctx_dto: CreateContextDto,
    ) -> MdnCentralResult<mdn_identity_contexts::Model>;
    async fn list_contexts(
        &self,
        context_scoped_subject_id: i64,
    ) -> MdnCentralResult<Vec<mdn_identity_contexts::Model>>;
}

pub struct MdnIdentityContextsRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnIdentityContextsRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnIdentityContextsRepository
    for MdnIdentityContextsRepositoryImpl<'a, C>
{
    async fn list_contexts(
        &self,
        context_scoped_subject_id: i64,
    ) -> MdnCentralResult<Vec<mdn_identity_contexts::Model>> {
        Ok(MdnIdentityContexts::find()
            .filter(
                mdn_identity_contexts::Column::ContextScopedSubjectId
                    .eq(context_scoped_subject_id),
            )
            .all(self.db_conn)
            .await?)
    }
    async fn create_context(
        &self,
        CreateContextDto {
            mdn_identity_context_uid,
            willow_namespace_id,
            context_scoped_subject_id,
        }: CreateContextDto,
    ) -> MdnCentralResult<mdn_identity_contexts::Model> {
        let res = mdn_identity_contexts::ActiveModel {
            mdn_identity_context_id: NotSet,
            mdn_identity_context_uid: Set(mdn_identity_context_uid),
            willow_namespace_id: Set(willow_namespace_id),
            context_scoped_subject_id: Set(context_scoped_subject_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
