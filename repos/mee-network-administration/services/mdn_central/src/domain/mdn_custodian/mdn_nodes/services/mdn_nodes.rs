use crate::{
    domain::mdn_custodian::{
        account::repositories::mdn_custodians::MdnCustodiansRepository,
        mdn_nodes::{
            api::types::{MdnNodeResponse, RegisterMdnNodeRequest},
            repositories::{
                mdn_node_signing_pub_keys::{
                    AddPubKeyDto, MdnNodeSigningPubKeysRepository,
                },
                mdn_nodes::{AddMdnNodeDto, MdnNodesRepository},
            },
        },
    },
    error::MdnCentralResult,
};

pub struct MdnNodesService<'a> {
    mdn_nodes_repository: Box<dyn MdnNodesRepository + Send + Sync + 'a>,
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
    mdn_node_signing_pub_keys_repository:
        Box<dyn MdnNodeSigningPubKeysRepository + Send + Sync + 'a>,
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
    ) -> Self {
        Self {
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
        }: RegisterMdnNodeRequest,
        mdn_custodian_uid: &str,
    ) -> MdnCentralResult {
        let mdn_node_uid = uuid::Uuid::new_v4().to_string();

        // TODO check did and proof

        let mdn_node_custodian_id = self
            .mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await?
            .mdn_custodian_id;

        let res = self
            .mdn_nodes_repository
            .register_node(AddMdnNodeDto {
                mdn_node_custodian_id,
                mdn_node_uid: format!("mdn_node-{mdn_node_uid}"),
                mdn_node_willow_peer_id,
                mdn_node_iroh_node_id,
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
