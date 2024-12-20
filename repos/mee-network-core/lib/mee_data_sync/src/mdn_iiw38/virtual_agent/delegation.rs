use super::namespace::VirtualAgentNamespaceStoreManager;
use crate::{error::MeeDataSyncResult, willow::peer::WillowPeer};
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, RestrictArea},
    proto::{grouping::Area, keys::UserId, meadowcap::AccessMode},
};

#[derive(Clone)]
pub struct VirtualAgentDelegationManager {
    willow_peer: WillowPeer,
    pub virtual_agent_ns_store_manager: VirtualAgentNamespaceStoreManager,
}

impl VirtualAgentDelegationManager {
    pub fn new(
        willow_peer: WillowPeer,
        virtual_agent_ns_store_manager: VirtualAgentNamespaceStoreManager,
    ) -> Self {
        Self {
            willow_peer,
            virtual_agent_ns_store_manager,
        }
    }
    pub async fn share_search_schemas_ns_with_provider(
        &self,
        provider_id: UserId,
    ) -> MeeDataSyncResult<Vec<CapabilityPack>> {
        let schemas_ns = self
            .virtual_agent_ns_store_manager
            .get_schemas_ns()
            .await?
            .0;

        let data_subset_restriction = RestrictArea::Restrict(Area::new_subspace(provider_id));

        let mut write_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::any(schemas_ns),
                AccessMode::Write,
                DelegateTo::new(provider_id, data_subset_restriction),
            )
            .await?;

        let mut read_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::any(schemas_ns),
                AccessMode::Read,
                DelegateTo::new(provider_id, RestrictArea::None),
            )
            .await?;

        write_caps.append(&mut read_caps);

        Ok(write_caps)
    }
}
