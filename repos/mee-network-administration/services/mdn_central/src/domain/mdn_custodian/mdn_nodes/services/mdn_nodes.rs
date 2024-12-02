use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepository,
            mdn_nodes::{
                api::types::{MdnNodeResponse, RegisterMdnNodeRequest},
                repositories::{
                    mdn_node_signing_pub_keys::{
                        AddPubKeyDto, MdnNodeSigningPubKeysRepository,
                    },
                    mdn_nodes::{AddMdnNodeDto, MdnNodesRepository},
                },
                utils::node_auth_utils::verify_mdn_node_did_signature,
            },
        },
        mdn_user::{
            identity_context::repositories::mdn_context_scoped_ids::MdnContextScopedIdsRepository,
            user_account::{
                api::middlewares::LoggedInMdnUser,
                services::account::MdnUserAccountService,
            },
        },
    },
    error::{MdnCentralErr, MdnCentralResult},
};
use std::sync::Arc;

pub struct MdnNodesService<'a> {
    mdn_nodes_repository: Box<dyn MdnNodesRepository + Send + Sync + 'a>,
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
    mdn_node_signing_pub_keys_repository:
        Box<dyn MdnNodeSigningPubKeysRepository + Send + Sync + 'a>,
    mdn_context_scoped_ids_repository:
        Box<dyn MdnContextScopedIdsRepository + Send + Sync + 'a>,
    mdn_user_account_service: MdnUserAccountService<'a>,
    mdn_central_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl<'a> MdnNodesService<'a> {
    pub fn new(
        mdn_nodes_repository: Box<dyn MdnNodesRepository + Send + Sync + 'a>,
        mdn_custodians_repository: Box<
            dyn MdnCustodiansRepository + Send + Sync + 'a,
        >,
        mdn_node_signing_pub_keys_repository: Box<
            dyn MdnNodeSigningPubKeysRepository + Send + Sync + 'a,
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
            mdn_node_signing_pub_keys_repository,
        }
    }
    pub async fn list_all(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult<Vec<MdnNodeResponse>> {
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
    pub async fn register_node(
        &self,
        RegisterMdnNodeRequest {
            mdn_node_willow_peer_id,
            mdn_node_iroh_node_id,
            mdn_node_did,
            mdn_node_did_proof,
            mdn_node_subject_id,
        }: RegisterMdnNodeRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCentralResult {
        let mdn_node_uid = uuid::Uuid::new_v4().to_string();
        let mdn_custodian_uid = logged_in_mdn_user.mdn_custodian_uid();

        let mdn_node_id_token =
            verify_mdn_node_did_signature(&mdn_node_did, &mdn_node_did_proof)
                .await?;

        if mdn_node_id_token.iss != mdn_node_did {
            Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                "Issuer DID mismatch".to_string(),
            ))?;
        }

        if mdn_node_id_token.aud
            != self.mdn_central_authority_signature.mee_sig_did().await?
        {
            Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                "Audience mismatch".to_string(),
            ))?;
        }

        match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                if mdn_node_id_token.sub != token.mdn_user_uid {
                    Err(MdnCentralErr::InvalidMdnNodeUserAuthToken(
                        "MDN user uid mismatch".to_string(),
                    ))?;
                }
            }
            // TODO check provider hosted node case
            LoggedInMdnUser::OAuthLoggedInUser => todo!(),
        };

        let mdn_node_custodian_id = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await?
            .mdn_custodian_id;

        let mdn_node_subject_id = match logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                self.mdn_user_account_service
                    .get_account_by_uid_required(&token.mdn_user_uid)
                    .await?
                    .mdn_user_id
            }
            LoggedInMdnUser::OAuthLoggedInUser => {
                self.mdn_context_scoped_ids_repository
                    .get_context_scoped_id_by_uid_required(&mdn_node_subject_id)
                    .await?
                    .mdn_user_id
            }
        };

        let res = self
            .mdn_nodes_repository
            .register_node(AddMdnNodeDto {
                mdn_node_custodian_id,
                mdn_node_uid: format!("mdn_node-{mdn_node_uid}"),
                mdn_node_willow_peer_id,
                mdn_node_iroh_node_id,
                mdn_node_subject_id,
            })
            .await?;

        self.mdn_node_signing_pub_keys_repository
            .add_pub_key(AddPubKeyDto {
                mdn_node_signing_pub_key_did: mdn_node_did,
                mdn_node_id: res.mdn_node_id,
            })
            .await?;

        Ok(())
    }
}
