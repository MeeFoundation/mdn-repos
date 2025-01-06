use crate::{
    db_models::mdn_identity_contexts_in_storages,
    domain::{
        mdn_custodian::{
            account::services::account::MdnCustodiansService,
            identity_context::repositories::{
                mdn_context_scoped_ids::{
                    CreateScopedIdDto, MdnContextScopedIdsRepository,
                },
                mdn_identity_contexts::{
                    CreateContextDto, MdnIdentityContextsRepository,
                },
                mdn_identity_contexts_in_storages::{
                    CreateMdnContextInStorageDto, MdnContextInStorageRepository,
                },
            },
            storage::services::mdn_custodian_storage::MdnCustodianStorageService,
        },
        mdn_user::user_account::{
            api::middlewares::LoggedInMdnUser,
            services::account::MdnUserAccountService,
        },
    },
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use mdn_identity_agent::{
    mdn_cloud::mdn_identity_context::api_types::{
        CreateMdnIdentityContextRequest, MdnIdentityContextResponse,
    },
    mdn_common::cap_definitions::MdnCapability,
};

pub struct MdnIdentityContextService<'a> {
    mdn_identity_contexts_repository:
        Box<dyn MdnIdentityContextsRepository + Send + Sync + 'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
    mdn_user_account_service: MdnUserAccountService<'a>,
    mdn_custodians_service: MdnCustodiansService<'a>,
    mdn_context_in_storage_repository:
        Box<dyn MdnContextInStorageRepository + Send + Sync + 'a>,
    mdn_custodian_storage_service: MdnCustodianStorageService<'a>,
}

impl<'a> MdnIdentityContextService<'a> {
    pub fn new(
        mdn_identity_contexts_repository: Box<
            dyn MdnIdentityContextsRepository + Send + Sync + 'a,
        >,
        mdn_context_scoped_ids_repository: Box<
            dyn MdnContextScopedIdsRepository + Send + Sync + 'a,
        >,
        mdn_user_account_service: MdnUserAccountService<'a>,
        mdn_custodians_service: MdnCustodiansService<'a>,
        mdn_context_in_storage_repository: Box<
            dyn MdnContextInStorageRepository + Send + Sync + 'a,
        >,
        mdn_custodian_storage_service: MdnCustodianStorageService<'a>,
    ) -> Self {
        Self {
            mdn_custodians_service,
            mdn_identity_contexts_repository,
            mdn_context_scoped_ids_repository,
            mdn_user_account_service,
            mdn_context_in_storage_repository,
            mdn_custodian_storage_service,
        }
    }

    pub async fn create_context(
        &self,
        CreateMdnIdentityContextRequest {
            willow_namespace_id,
            context_ops_cap_token,
            custodian_uid,
            context_description,
        }: CreateMdnIdentityContextRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult<MdnIdentityContextResponse> {
        let (mdn_cap, sig_did) =
            MdnCapability::decode(&context_ops_cap_token).await?;

        if !self
            .mdn_user_account_service
            .check_user_did(&sig_did, logged_in_mdn_user.mdn_user_uid())
            .await?
        {
            Err(MdnCloudControllerErr::MdnCapabilities(format!(
                "No user with DID({sig_did}) signature exists"
            )))?
        }

        // TODO check context_ops_cap_token permissions
        // 1) custodian_id == context_ops_cap_token.to

        let custodian = self
            .mdn_custodians_service
            .get_custodian_by_uid(&custodian_uid)
            .await?;

        let user = self
            .mdn_user_account_service
            .get_account_by_uid_required(logged_in_mdn_user.mdn_user_uid())
            .await?;

        let context_scoped_id = match self
            .mdn_context_scoped_ids_repository
            .get_context_scoped_id_by_custodian_id(
                user.mdn_user_id,
                custodian.mdn_custodian_id,
            )
            .await?
        {
            Some(v) => v,
            None => {
                let res = self
                    .mdn_context_scoped_ids_repository
                    .create_context_scoped_id(CreateScopedIdDto {
                        mdn_user_id: user.mdn_user_id,
                        for_mdn_custodian_id: custodian.mdn_custodian_id,
                    })
                    .await?;

                res
            }
        };

        let ctx = self
            .mdn_identity_contexts_repository
            .create_context(CreateContextDto {
                delegated_from_context_id: None,
                willow_namespace_id,
                context_description,
                context_scoped_subject_id: context_scoped_id
                    .mdn_context_scoped_id,
                mdn_user_subject_id: user.mdn_user_id,
                mdn_custodian_id: custodian.mdn_custodian_id,
            })
            .await?;

        self.link_context_to_storage(
            &ctx.mdn_identity_context_uid,
            &logged_in_mdn_user,
        )
        .await?;

        let res = self
            .mdn_identity_contexts_repository
            .get_context_with_custodian_name(
                &ctx.mdn_identity_context_uid,
                Some(user.mdn_user_id),
            )
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MissingDbEntity(format!(
                    "identity context({})",
                    ctx.mdn_identity_context_uid
                ))
            })?
            .into();

        Ok(res)
    }
    pub async fn list_contexts(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult<Vec<MdnIdentityContextResponse>> {
        let mdn_user_id = self
            .mdn_user_account_service
            .get_account_by_uid_required(logged_in_mdn_user.mdn_user_uid())
            .await?
            .mdn_user_id;

        let res = self
            .mdn_identity_contexts_repository
            .list_contexts_with_custodian_name(mdn_user_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    async fn link_context_to_storage(
        &self,
        mdn_identity_context_uid: &str,
        logged_in_mdn_user: &LoggedInMdnUser,
    ) -> MdnCloudControllerResult<mdn_identity_contexts_in_storages::Model>
    {
        let mdn_user_id = self
            .mdn_user_account_service
            .get_account_by_uid_required(logged_in_mdn_user.mdn_user_uid())
            .await?
            .mdn_user_id;

        let ctx = self
            .mdn_identity_contexts_repository
            .get_context_with_custodian_name_required(
                mdn_identity_context_uid,
                Some(mdn_user_id),
            )
            .await?;

        let storage = self
            .mdn_custodian_storage_service
            .get_custodian_storage_by_did(
                logged_in_mdn_user.mdn_custodian_uid(),
                logged_in_mdn_user.mdn_custodian_storage_did(),
            )
            .await?;

        self.mdn_context_in_storage_repository
            .link_context_to_storage(CreateMdnContextInStorageDto {
                mdn_identity_context_id: ctx.mdn_identity_context_id,
                mdn_custodian_storage_id: storage.mdn_custodian_storage_id,
            })
            .await
    }
}
