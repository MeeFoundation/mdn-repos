use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh_willow::{
    auth::{CapSelector, CapabilityPack, DelegateTo},
    proto::meadowcap::AccessMode,
};

#[derive(Clone)]
pub struct WillowDelegationManager {
    willow_node: WillowNode,
}

impl WillowDelegationManager {
    pub fn new(willow_node: WillowNode) -> Self {
        Self { willow_node }
    }
    pub async fn delegate_capabilities(
        &self,
        from: CapSelector,
        access_mode: AccessMode,
        to: DelegateTo,
    ) -> MeeDataSyncResult<Vec<CapabilityPack>> {
        let caps = self
            .willow_node
            .engine
            .delegate_caps(from, access_mode, to)
            .await?;

        Ok(caps)
    }
}
