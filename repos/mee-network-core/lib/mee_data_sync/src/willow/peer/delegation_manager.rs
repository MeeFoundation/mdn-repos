use super::network_manager::WillowNetworkManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::node::WillowNode,
};
use iroh_base::ticket::NodeTicket;
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo},
    proto::{
        grouping::Area,
        keys::NamespaceId,
        meadowcap::{AccessMode, McCapability, ReadAuthorisation},
    },
};

pub fn cap_granted_components(cap_pack: &CapabilityPack) -> (NamespaceId, Area) {
    match cap_pack {
        CapabilityPack::Read(read_cap) => (
            *read_cap.read_cap().granted_namespace(),
            read_cap.read_cap().granted_area(),
        ),
        CapabilityPack::Write(write_cap) => {
            (*write_cap.granted_namespace(), write_cap.granted_area())
        }
    }
}

/// Data sharing, sync management sessions
#[derive(Clone)]
pub struct WillowDelegationManager {
    willow_node: WillowNode,
    willow_network_manager: WillowNetworkManager,
}

impl WillowDelegationManager {
    pub fn new(willow_node: WillowNode, willow_network_manager: WillowNetworkManager) -> Self {
        Self {
            willow_node,
            willow_network_manager,
        }
    }
    pub async fn import_capabilities_from_remote_peer(
        &self,
        caps: Vec<CapabilityPack>,
        ticket: &NodeTicket,
    ) -> MeeDataSyncResult {
        if caps.is_empty() {
            Err(MeeDataSyncErr::WillowDelegationHandler(
                "Attempt to import empty capability list".to_string(),
            ))?;
        }

        self.willow_network_manager
            .add_remote_peer(ticket.node_addr().clone())?;

        self.willow_node.engine.import_caps(caps).await?;

        Ok(())
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

    pub async fn delete_capabilities(
        &self,
        cap_selector: CapSelector,
    ) -> MeeDataSyncResult<Vec<McCapability>> {
        Ok(self.willow_node.engine.del_caps(cap_selector).await?)
    }

    pub async fn list_read_caps(&self) -> MeeDataSyncResult<Vec<ReadAuthorisation>> {
        Ok(self.willow_node.engine.list_read_caps().await?)
    }
}
