use super::namespace::MdnDataOwnerNamespaceStoreManager;
use crate::{error::MeeDataSyncResult, willow::peer::WillowPeer};
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, RestrictArea},
    proto::{grouping::Area, keys::UserId, meadowcap::AccessMode},
};

pub trait MdnAgentDataOwnerNodeDelegation {}

#[derive(Clone)]
pub struct MdnDataOwnerDelegationManager {
    willow_peer: WillowPeer,
    mdn_ns_store_manager: MdnDataOwnerNamespaceStoreManager,
}

impl MdnDataOwnerDelegationManager {
    pub fn new(
        willow_peer: WillowPeer,
        mdn_ns_store_manager: MdnDataOwnerNamespaceStoreManager,
    ) -> Self {
        Self {
            willow_peer,
            mdn_ns_store_manager,
        }
    }
    pub async fn share_cap_list_with_provider(
        &self,
        provider_id: UserId,
    ) -> MeeDataSyncResult<Vec<CapabilityPack>> {
        let cap_list_ns = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?
            .0;

        let data_subset_restriction = RestrictArea::Restrict(Area::new_subspace(provider_id));

        let data_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(cap_list_ns),
                AccessMode::Write,
                DelegateTo::new(provider_id, data_subset_restriction),
            )
            .await?;

        Ok(data_caps)
    }
}
