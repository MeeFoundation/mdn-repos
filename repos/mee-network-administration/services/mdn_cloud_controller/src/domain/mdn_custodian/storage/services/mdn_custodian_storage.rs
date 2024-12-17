use crate::{
    domain::{
        mdn_authority::utils::MdnSignaturesService,
        mdn_custodian::{
            account::repositories::mdn_custodians::MdnCustodiansRepository,
            storage::{
                api::types::{
                    MdnCustodianStorageResponse,
                    RegisterMdnCustodianStorageRequest,
                },
                repositories::mdn_custodian_storage::{
                    AddMdnCustodianStorageDto, MdnCustodianStoragesRepository,
                },
                utils::custodian_storage_utils::verify_user_custodian_storage_did_signature,
            },
        },
        mdn_user::user_account::{
            api::middlewares::LoggedInMdnUser,
            repositories::mdn_user_signing_pub_keys::{
                AddPubKeyDto, MdnUserSigningPubKeysRepository,
            },
            services::account::MdnUserAccountService,
        },
    },
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};
use std::sync::Arc;

pub struct MdnNodesService<'a> {
    mdn_custodian_storages_repository:
        Box<dyn MdnCustodianStoragesRepository + Send + Sync + 'a>,
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
    mdn_user_signing_pub_keys_repository:
        Box<dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a>,
    mdn_user_account_service: MdnUserAccountService<'a>,
    mdn_cloud_controller_authority_signature:
        Arc<dyn MdnSignaturesService + Send + Sync>,
}

impl<'a> MdnNodesService<'a> {
    pub fn new(
        mdn_custodian_storages_repository: Box<
            dyn MdnCustodianStoragesRepository + Send + Sync + 'a,
        >,
        mdn_custodians_repository: Box<
            dyn MdnCustodiansRepository + Send + Sync + 'a,
        >,
        mdn_user_signing_pub_keys_repository: Box<
            dyn MdnUserSigningPubKeysRepository + Send + Sync + 'a,
        >,
        mdn_user_account_service: MdnUserAccountService<'a>,
        mdn_cloud_controller_authority_signature: Arc<
            dyn MdnSignaturesService + Send + Sync,
        >,
    ) -> Self {
        Self {
            mdn_cloud_controller_authority_signature,
            mdn_user_account_service,
            mdn_custodian_storages_repository,
            mdn_custodians_repository,
            mdn_user_signing_pub_keys_repository,
        }
    }
    pub async fn list_all_custodian_storages(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<Vec<MdnCustodianStorageResponse>> {
        let custodian = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await?;

        let res = self
            .mdn_custodian_storages_repository
            .list_all(custodian.mdn_custodian_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    pub async fn register_custodian_storage(
        &self,
        RegisterMdnCustodianStorageRequest {
            willow_peer_id,
            iroh_node_id,
            mdn_custodian_storage_did,
            mdn_custodian_storage_did_proof,
        }: RegisterMdnCustodianStorageRequest,
        logged_in_mdn_user: LoggedInMdnUser,
    ) -> MdnCloudControllerResult {
        let mdn_custodian_storage_uid = uuid::Uuid::new_v4().to_string();
        let mdn_custodian_uid = logged_in_mdn_user.mdn_custodian_uid();

        let mdn_custodian_storage_id_token =
            verify_user_custodian_storage_did_signature(
                &mdn_custodian_storage_did,
                &mdn_custodian_storage_did_proof,
            )
            .await?;

        if mdn_custodian_storage_id_token.iss != mdn_custodian_storage_did {
            Err(MdnCloudControllerErr::InvalidMdnNodeUserAuthToken(
                "Issuer DID mismatch".to_string(),
            ))?;
        }

        if mdn_custodian_storage_id_token.aud
            != self.mdn_cloud_controller_authority_signature.mee_sig_did().await?
        {
            Err(MdnCloudControllerErr::InvalidMdnNodeUserAuthToken(
                "Audience mismatch".to_string(),
            ))?;
        }

        match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                if mdn_custodian_storage_id_token.sub != token.mdn_user_uid {
                    Err(MdnCloudControllerErr::InvalidMdnNodeUserAuthToken(
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

        let res = self
            .mdn_custodian_storages_repository
            .register_custodian_storage(AddMdnCustodianStorageDto {
                mdn_custodian_id,
                mdn_custodian_storage_uid: format!(
                    "mdn_custodian_storage-{mdn_custodian_storage_uid}"
                ),
                willow_peer_id,
                iroh_node_id,
            })
            .await?;

        match &logged_in_mdn_user {
            LoggedInMdnUser::DirectlyLoggedInMdnUser(token) => {
                let mdn_user_id = self
                    .mdn_user_account_service
                    .get_account_by_uid_required(&token.mdn_user_uid)
                    .await?
                    .mdn_user_id;

                self.mdn_user_signing_pub_keys_repository
                    .add_pub_key(AddPubKeyDto {
                        mdn_user_signing_pub_key_did: mdn_custodian_storage_did,
                        mdn_custodian_storage_id: Some(
                            res.mdn_custodian_storage_id,
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
