use super::network_manager::WillowNetworkManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    willow::node::WillowNode,
};
use iroh_net::ticket::NodeTicket;
use iroh_willow::{
    auth::{CapSelector, CapabilityPack, DelegateTo},
    proto::{grouping::Area, meadowcap::AccessMode, sync::ReadAuthorisation},
    session::{intents::IntentHandle, Interests, SessionInit, SessionMode},
};

pub struct ImportCapabilitiesFromRemotePeer {
    pub node_ticket: String,
    pub caps: Vec<CapabilityPack>,
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
        ImportCapabilitiesFromRemotePeer { caps, node_ticket }: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle> {
        if caps.is_empty() {
            Err(MeeDataSyncErr::WillowDelegationHandler(
                "Attempt to import empty capability list".to_string(),
            ))?;
        }

        let ticket: NodeTicket = node_ticket.parse()?;

        self.willow_network_manager
            .add_remote_peer(ticket.node_addr().clone())?;

        self.willow_node.engine.import_caps(caps.clone()).await?;

        let mut interests = Interests::builder();

        // TODO proper area handling
        for cap in caps.iter() {
            let (ns, area) = match cap {
                CapabilityPack::Read(read_cap) => {
                    (read_cap.namespace(), read_cap.read_cap().granted_area())
                }
                CapabilityPack::Write(write_cap) => {
                    (write_cap.granted_namespace().id(), write_cap.granted_area())
                }
            };

            interests = interests.add_area(ns, [Area::full()]);
        }

        let init = SessionInit::new(interests, SessionMode::Live);

        let sync_intent = self
            .willow_node
            .engine
            .sync_with_peer(ticket.node_addr().node_id, init)
            .await?;

        Ok(sync_intent)
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

    pub async fn list_read_caps(&self) -> MeeDataSyncResult<Vec<ReadAuthorisation>> {
        Ok(self.willow_node.engine.list_read_caps().await?)
    }
}
