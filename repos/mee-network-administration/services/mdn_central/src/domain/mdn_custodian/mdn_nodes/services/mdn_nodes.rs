use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepository,
            mdn_nodes::{
                api::types::{
                    MdnNodeHostingPlatformResponse,
                    RegisterMdnNodeHostingPlatformRequest,
                },
                repositories::mdn_node_hosting_platforms::{
                    AddMdnNodeHostingPlatformDto,
                    MdnNodeHostingPlatformsRepository,
                },
                utils::node_auth_utils::verify_mdn_node_hoster_did_signature,
            },
        },
        mdn_user::{
            identity_context::repositories::mdn_context_scoped_ids::MdnContextScopedIdsRepository,
            user_account::{
                api::middlewares::LoggedInMdnUser,
                repositories::mdn_user_signing_pub_keys::{
                    AddPubKeyDto, MdnUserSigningPubKeysRepository,
                },
                services::account::MdnUserAccountService,
            },
        },
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use std::sync::Arc;

pub struct MdnNodesService<'a> {
    mdn_nodes_repository:
        Box<dyn MdnNodeHostingPlatformsRepository + Send + Sync + 'a>,
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
    mdn_user_signing_pub_keys_repository:
        Box<dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
    mdn_user_account_service: MdnUserAccountService<'a>,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl<'a> MdnNodesService<'a> {
    pub fn new(
        mdn_nodes_repository: Box<
            dyn MdnNodeHostingPlatformsRepository + Send + Sync + 'a,
        >,
        mdn_custodians_repository: Box<
            dyn MdnCustodiansRepository + Send + Sync + 'a,
        >,
        mdn_user_signing_pub_keys_repository: Box<
            dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a,
        >,
        mdn_context_scoped_ids_repository: Box<
            dyn MdnContextScopedIdsRepository + Send + Sync + 'a,
        >,
        mdn_user_account_service: MdnUserAccountService<'a>,
        mdn_central_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            mdn_central_authority_signature,
            mdn_user_account_service,
            mdn_context_scoped_ids_repository,
            mdn_nodes_repository,
            mdn_custodians_repository,
            mdn_user_signing_pub_keys_repository,
        }
    }
    pub async fn list_all_node_hosting_platforms(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult<Vec<MdnNodeHostingPlatformResponse>> {
        let custodian = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await?;

        let res = self
            .mdn_nodes_repository
            .list_all(custodian.mdn_custodian_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    pub async fn register_node_hosting_platform(
        &self,
        RegisterMdnNodeHostingPlatformRequest {
            willow_peer_id,
            iroh_node_id,
            node_hosting_platform_did,
            node_hosting_platform_did_proof,
        }: RegisterMdnNodeHostingPlatformRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        let mdn_node_hosting_platform_uid = uuid::Uuid::new_v4().to_string();
        let mdn_custodian_uid = logged_in_mdn_user.mdn_custodian_uid();

        let mdn_node_hoster_id_token = verify_mdn_node_hoster_did_signature(
            &node_hosting_platform_did,
            &node_hosting_platform_did_proof,
        )
        .await?;

        if mdn_node_hoster_id_token.iss != node_hosting_platform_did {
            Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                "Issuer DID mismatch".to_string(),
            ))?;
        }

        if mdn_node_hoster_id_token.aud
            != self.mdn_central_authority_signature.mee_sig_did().await?
        {
            Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                "Audience mismatch".to_string(),
            ))?;
        }

        match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                if mdn_node_hoster_id_token.sub != token.mdn_user_uid {
                    Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                        "MDN user uid mismatch".to_string(),
                    ))?;
                }
            }
            // TODO check provider hosted node case
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        };

        let mdn_custodian_id = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await?
            .mdn_custodian_id;

        // let mdn_node_subject_id = match logged_in_mdn_user {
        //     LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
        //         self.mdn_user_account_service
        //             .get_account_by_uid_required(&token.mdn_user_uid)
        //             .await?
        //             .mdn_user_id
        //     }
        //     LoggedInMdnUser::OAuthLoggedInUser => {
        //         self.mdn_context_scoped_ids_repository
        //             .get_context_scoped_id_by_uid_required(&mdn_node_subject_id)
        //             .await?
        //             .mdn_user_id
        //     }
        // };

        let res = self
            .mdn_nodes_repository
            .register_node_platform(AddMdnNodeHostingPlatformDto {
                mdn_custodian_id,
                mdn_node_hosting_platform_uid: format!(
                    "mdn_node_hosting_platform-{mdn_node_hosting_platform_uid}"
                ),
                willow_peer_id,
                iroh_node_id,
            })
            .await?;

        // TODO handle both cases: user hosting platform (mobile device) and provider hosting platform (provider multi-tenant server)
        match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                let mdn_user_id = self
                    .mdn_user_account_service
                    .get_account_by_uid_required(&token.mdn_user_uid)
                    .await?
                    .mdn_user_id;

                self.mdn_user_signing_pub_keys_repository
                    .add_pub_key(AddPubKeyDto {
                        mdn_user_signing_pub_key_did: node_hosting_platform_did,
                        mdn_node_hosting_platform_id: Some(
                            res.mdn_node_hosting_platform_id,
                        ),
                        mdn_user_id,
                    })
                    .await?;
            }
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        };

        Ok(())
    }
}
