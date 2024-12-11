use crate::{
    domain::{
        mdn_custodian::identity_context::repositories::{
            mdn_context_scoped_ids::MdnContextScopedIdsRepository,
            mdn_identity_contexts::{
                CreateContextDto, MdnIdentityContextsRepository,
            },
        },
        mdn_user::user_account::api::middlewares::LoggedInMdnUser,
    },
    error::MdnCentralResult,
};
use mdn_identity_agent::mdn_cloud::mdn_identity_context::api_types::{
    CreateMdnIdentityContextRequest, MdnIdentityContextResponse,
};

pub struct MdnIdentityContextService<'a> {
    mdn_identity_contexts_repository:
        Box<dyn MdnIdentityContextsRepository + Send + Sync + 'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
}

impl<'a> MdnIdentityContextService<'a> {
    pub fn new(
        mdn_identity_contexts_repository: Box<
            dyn MdnIdentityContextsRepository + Send + Sync + 'a,
        >,
        mdn_context_scoped_ids_repository: Box<
            dyn MdnContextScopedIdsRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            mdn_identity_contexts_repository,
            mdn_context_scoped_ids_repository,
        }
    }

    pub async fn create_context(
        &self,
        CreateMdnIdentityContextRequest {
            willow_namespace_id,
            // TODO check context_ops_cap_token
            context_ops_cap_token,
        }: CreateMdnIdentityContextRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<MdnIdentityContextResponse> {
        let mdn_user_context_scoped_uid = match logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(
                directly_logged_in_mdn_user,
            ) => directly_logged_in_mdn_user.mdn_user_context_scoped_uid,
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        };

        let context_scoped_id = self
            .mdn_context_scoped_ids_repository
            .get_context_scoped_id_by_uid_required(&mdn_user_context_scoped_uid)
            .await?;

        let ctx = self
            .mdn_identity_contexts_repository
            .create_context(CreateContextDto {
                mdn_identity_context_uid: format!(
                    "mdn_identity_context-{}",
                    uuid::Uuid::new_v4()
                ),
                willow_namespace_id,
                context_scoped_subject_id: context_scoped_id
                    .mdn_context_scoped_id,
            })
            .await?;

        Ok(MdnIdentityContextResponse {
            mdn_identity_context_uid: ctx.mdn_identity_context_uid,
            willow_namespace_id: ctx.willow_namespace_id,
            context_scoped_subject_id: context_scoped_id.mdn_context_scoped_uid,
        })
    }
    pub async fn list_contexts(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<MdnIdentityContextResponse>> {
        let mdn_user_context_scoped_uid = match logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                token.mdn_user_context_scoped_uid
            }
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        };

        let context_scoped_id = self
            .mdn_context_scoped_ids_repository
            .get_context_scoped_id_by_uid_required(&mdn_user_context_scoped_uid)
            .await?;

        let res = self
            .mdn_identity_contexts_repository
            .list_contexts(context_scoped_id.mdn_context_scoped_id)
            .await?
            .into_iter()
            .map(|r| MdnIdentityContextResponse {
                mdn_identity_context_uid: r.mdn_identity_context_uid,
                willow_namespace_id: r.willow_namespace_id,
                context_scoped_subject_id: context_scoped_id
                    .mdn_context_scoped_uid
                    .clone(),
            })
            .collect();

        Ok(res)
    }
}
