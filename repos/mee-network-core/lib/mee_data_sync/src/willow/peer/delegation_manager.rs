use super::network_manager::WillowNetworkManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    mdn::node::{MdnDataDelegationCapabilityPack, MdnDataDelegationCapabilityRole},
    willow::node::WillowNode,
};
use iroh_net::ticket::NodeTicket;
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, Interests},
    proto::{
        grouping::Area,
        keys::NamespaceId,
        meadowcap::{AccessMode, ReadAuthorisation},
    },
    session::{intents::IntentHandle, SessionInit, SessionMode},
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

pub struct ImportCapabilitiesFromRemotePeer {
    pub node_ticket: String,
    pub caps: Vec<MdnDataDelegationCapabilityPack>,
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

        self.willow_node
            .engine
            .import_caps(caps.iter().map(|c| c.cap_pack.clone()).collect())
            .await?;

        let mut interests = Interests::builder();

        for cap in caps.iter() {
            if let MdnDataDelegationCapabilityRole::MdnDataSharing = cap.cap_role {
                let (ns, area) = cap_granted_components(&cap.cap_pack);

                interests = interests.add_area(ns, [area]);
            }
        }

        let init = SessionInit::new(interests, SessionMode::Continuous);

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
