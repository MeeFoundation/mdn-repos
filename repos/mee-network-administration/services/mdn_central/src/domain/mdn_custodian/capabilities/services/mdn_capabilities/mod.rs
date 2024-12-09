use crate::{
    domain::{
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepository,
            capabilities::{
                api::types::{
                    IssueContextOpsCapTokenRequest,
                    MdnCustodianContextOperationCapsResponse,
                },
                repositories::mdn_custodian_context_operation_caps::{
                    AddCustodianContextOperationCapsDto,
                    CustodianContextOperationCapsRepository,
                },
            },
        },
        mdn_user::user_account::{
            api::middlewares::{DirectlyLoggedInMdnUser, LoggedInMdnUser},
            services::account::MdnUserAccountService,
        },
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use anyhow::Context;
use mdn_identity_agent::mdn_common::cap_definitions::MdnCapability;
use mee_did::universal_resolver::{DIDResolverExt, UniversalDidResolver};

pub struct MdnCapabilitiesService<'a> {
    custodian_context_operation_caps_repository:
        Box<dyn CustodianContextOperationCapsRepository + Send + Sync + 'a>,
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
    mdn_user_account_service: MdnUserAccountService<'a>,
}

impl<'a> MdnCapabilitiesService<'a> {
    pub fn new(
        custodian_context_operation_caps_repository: Box<
            dyn CustodianContextOperationCapsRepository + Send + Sync + 'a,
        >,
        mdn_custodians_repository: Box<
            dyn MdnCustodiansRepository + Send + Sync + 'a,
        >,
        mdn_user_account_service: MdnUserAccountService<'a>,
    ) -> Self {
        Self {
            mdn_custodians_repository,
            custodian_context_operation_caps_repository,
            mdn_user_account_service,
        }
    }
    async fn validate_cap_token(
        &self,
        token: &str,
    ) -> MdnCentralResult<MdnCapability> {
        let token_header = MdnCapability::decode_header(&token)?;
        let sign_did_id = token_header
            .claim("kid")
            .context("missing 'kid' in the MDN cap token")?
            .as_str()
            .context("invalid 'kid' format of the MDN cap token")?;

        let auth_did_jwk = UniversalDidResolver
            .get_verification_method_jwk_by_id(
                sign_did_id
                    .split("#")
                    .collect::<Vec<_>>()
                    .first()
                    .context("missing ctx ops cap token did")?,
                &sign_did_id,
            )
            .await?;

        let token = MdnCapability::decode(&token, auth_did_jwk)?;

        Ok(token)
    }
    async fn issue_context_ops_cap_for_provider_custodian(
        &self,
        user_issued_cap_token: &str,
    ) -> MdnCentralResult {
        todo!()
    }
    async fn issue_context_ops_cap_for_user_custodian(
        &self,
        directly_logged_in_mdn_user: DirectlyLoggedInMdnUser,
        user_issued_cap_token: String,
    ) -> MdnCentralResult {
        let to_mdn_custodian_id = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(
                &directly_logged_in_mdn_user.mdn_user_custodian_uid,
            )
            .await?
            .mdn_custodian_id;

        let from_mdn_user_id = self
            .mdn_user_account_service
            .get_account_by_uid_required(
                &directly_logged_in_mdn_user.mdn_user_uid,
            )
            .await?
            .mdn_user_id;

        let token = self.validate_cap_token(&user_issued_cap_token).await?;

        let exp = chrono::DateTime::from_timestamp(token.exp, 0).ok_or_else(
            || {
                MdnCentralErr::MdnCapabilities(
                    "cap token exp time handling".to_string(),
                )
            },
        )?;

        self.custodian_context_operation_caps_repository
            .add_cap(AddCustodianContextOperationCapsDto {
                mdn_custodian_context_operation_cap_uid: format!(
                    "mdn_custodian_ctx_ops_cap-{}",
                    uuid::Uuid::new_v4()
                ),
                mdn_custodian_context_operation_cap_token:
                    user_issued_cap_token,
                mdn_custodian_context_operation_cap_expires: exp.into(),
                from_mdn_user_id,
                to_mdn_custodian_id,
            })
            .await?;

        Ok(())
    }
    pub async fn issue_context_ops_cap(
        &self,
        IssueContextOpsCapTokenRequest {
            cap_token,
        }: IssueContextOpsCapTokenRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        match logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(user_auth_token) => {
                self.issue_context_ops_cap_for_user_custodian(
                    user_auth_token,
                    cap_token,
                )
                .await?;
            }
            LoggedInMdnUser::OAuthLoggedInUser => {
                self.issue_context_ops_cap_for_provider_custodian(&cap_token)
                    .await?;
            }
        };

        Ok(())
    }
    pub async fn context_ops_caps(
        &self,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult<Vec<MdnCustodianContextOperationCapsResponse>> {
        let user_id = match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(user_auth_token) => {
                self.mdn_user_account_service
                    .get_account_by_uid_required(&user_auth_token.mdn_user_uid)
                    .await?
                    .mdn_user_id
            }
            LoggedInMdnUser::OAuthLoggedInUser => {
                todo!()
            }
        };

        Ok(self
            .custodian_context_operation_caps_repository
            .list_issued_caps(user_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect())
    }
}
