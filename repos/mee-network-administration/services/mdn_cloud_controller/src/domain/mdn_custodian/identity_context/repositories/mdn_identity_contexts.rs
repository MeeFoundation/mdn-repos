use crate::{
    db_models::{
        mdn_context_scoped_ids, mdn_custodians, mdn_identity_contexts,
        mdn_providers, mdn_users, prelude::*,
    },
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use async_trait::async_trait;
use migrations::IntoCondition;
use sea_orm::{entity::*, query::*, sea_query, FromQueryResult};

pub struct CreateContextDto {
    pub delegated_from_context_id: Option<i64>,
    pub willow_namespace_id: String,
    pub context_scoped_subject_id: i64,
    pub context_description: String,
    pub mdn_user_subject_id: i64,
    pub mdn_custodian_id: i64,
}

#[async_trait]
pub trait MdnIdentityContextsRepository {
    async fn create_context(
        &self,
        create_ctx_dto: CreateContextDto,
    ) -> MdnCloudControllerResult<mdn_identity_contexts::Model>;
    async fn list_contexts_with_custodian_name(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Vec<MdnIdentityContextWithCustodianName>>;
    async fn get_context_with_custodian_name(
        &self,
        ctx_uid: &str,
        mdn_user_id: Option<i64>,
    ) -> MdnCloudControllerResult<Option<MdnIdentityContextWithCustodianName>>;
    async fn get_context_with_custodian_name_required(
        &self,
        ctx_uid: &str,
        mdn_user_id: Option<i64>,
    ) -> MdnCloudControllerResult<MdnIdentityContextWithCustodianName> {
        self.get_context_with_custodian_name(ctx_uid, mdn_user_id)
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MissingDbEntity(format!("{ctx_uid}"))
            })
    }
}

pub struct MdnIdentityContextsRepositoryImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> MdnIdentityContextsRepositoryImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[derive(FromQueryResult)]
pub struct MdnIdentityContextWithCustodianName {
    pub mdn_identity_context_id: i64,
    pub mdn_identity_context_uid: String,
    pub willow_namespace_id: String,
    pub context_scoped_subject_uid: String,
    pub custodian_name: String,
    pub context_description: String,
}

fn select_context_with_custodian_name(
    mdn_user_id: Option<i64>,
) -> Select<mdn_identity_contexts::Entity> {
    MdnIdentityContexts::find()
        .select_only()
        .column(mdn_identity_contexts::Column::WillowNamespaceId)
        .column(mdn_identity_contexts::Column::MdnIdentityContextId)
        .column(mdn_identity_contexts::Column::MdnIdentityContextUid)
        .column(mdn_identity_contexts::Column::ContextDescription)
        .expr_as(
            sea_query::Func::coalesce([
                mdn_users::Column::MdnUserName.into_simple_expr(),
                mdn_providers::Column::MdnProviderName.into_simple_expr(),
            ]),
            "custodian_name",
        )
        .clone()
        .column_as(
            mdn_context_scoped_ids::Column::MdnContextScopedUid,
            "context_scoped_subject_uid",
        )
        .join(
            JoinType::InnerJoin,
            mdn_identity_contexts::Relation::MdnContextScopedIds
                .def()
                .on_condition(move |_left, right| match mdn_user_id {
                    Some(mdn_user_id) => sea_query::Expr::col((
                        right,
                        mdn_context_scoped_ids::Column::MdnUserId,
                    ))
                    .eq(mdn_user_id)
                    .into_condition(),
                    None => Condition::all(),
                }),
        )
        .join(
            JoinType::InnerJoin,
            mdn_identity_contexts::Relation::MdnCustodians.def(),
        )
        .join(
            JoinType::LeftJoin,
            mdn_custodians::Relation::MdnProviders.def(),
        )
        .join(JoinType::LeftJoin, mdn_custodians::Relation::MdnUsers.def())
}

#[async_trait]
impl<'a, C: ConnectionTrait> MdnIdentityContextsRepository
    for MdnIdentityContextsRepositoryImpl<'a, C>
{
    async fn list_contexts_with_custodian_name(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<Vec<MdnIdentityContextWithCustodianName>>
    {
        let res = select_context_with_custodian_name(Some(mdn_user_id))
            .into_model()
            .all(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn get_context_with_custodian_name(
        &self,
        ctx_uid: &str,
        mdn_user_id: Option<i64>,
    ) -> MdnCloudControllerResult<Option<MdnIdentityContextWithCustodianName>>
    {
        let res = select_context_with_custodian_name(mdn_user_id)
            .filter(
                mdn_identity_contexts::Column::MdnIdentityContextUid
                    .eq(ctx_uid),
            )
            .into_model()
            .one(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn create_context(
        &self,
        CreateContextDto {
            delegated_from_context_id,
            willow_namespace_id,
            context_scoped_subject_id,
            context_description,
            mdn_user_subject_id,
            mdn_custodian_id,
        }: CreateContextDto,
    ) -> MdnCloudControllerResult<mdn_identity_contexts::Model> {
        let mdn_identity_context_uid =
            format!("mdn_identity_context-{}", uuid::Uuid::new_v4());

        let res = mdn_identity_contexts::ActiveModel {
            mdn_identity_context_id: NotSet,
            delegated_from_context_id: Set(delegated_from_context_id),
            mdn_identity_context_uid: Set(mdn_identity_context_uid),
            willow_namespace_id: Set(willow_namespace_id),
            context_scoped_subject_id: Set(context_scoped_subject_id),
            context_description: Set(context_description),
            mdn_user_subject_id: Set(mdn_user_subject_id),
            mdn_custodian_id: Set(mdn_custodian_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
