use super::{namespace::MdnNamespaceStoreManager, node::MdnAgentDataNodeWillowImpl};
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    mdn::{
        node::{
            MdnAgentDataNodeDelegation, MdnDataDelegationCapabilityPack,
            MdnDataDelegationCapabilityRole, MdnDataRevocationListRecord,
        },
        store::key_components,
    },
    willow::{
        peer::{delegation_manager::cap_granted_components, WillowPeer},
        utils::{is_empty_entry_payload, path_from_bytes_slice},
    },
};
use async_trait::async_trait;
use futures::{future::join_all, StreamExt};
use iroh_net::ticket::NodeTicket;
use iroh_willow::{
    interest::{
        AreaSelector, CapSelector, CapabilityPack, DelegateTo, Interests, ReceiverSelector,
        RestrictArea,
    },
    proto::{
        data_model::{Path, WriteCapability},
        grouping::{Area, AreaExt, AreaSubspace, Range, Range3d},
        keys::UserId,
        meadowcap::{AccessMode, McCapability},
    },
    session::{intents::IntentHandle, SessionInit, SessionMode},
};
use std::time::Duration;
use tokio::{task::JoinHandle, time::sleep};

pub fn revocation_list_record_path(user_id: UserId) -> MeeDataSyncResult<Path> {
    path_from_bytes_slice(&[b"revocation_list", user_id.as_bytes()])
}

#[derive(Clone)]
pub struct MdnDelegationManager {
    willow_peer: WillowPeer,
    mdn_ns_store_manager: MdnNamespaceStoreManager,
}

impl MdnDelegationManager {
    pub fn new(willow_peer: WillowPeer, mdn_ns_store_manager: MdnNamespaceStoreManager) -> Self {
        Self {
            willow_peer,
            mdn_ns_store_manager,
        }
    }
    async fn revoke_capabilities(
        &self,
        caps: Vec<MdnDataRevocationListRecord>,
    ) -> MeeDataSyncResult<Vec<McCapability>> {
        let tasks = caps.into_iter().map(|cap| async move {
            let comps = key_components(&cap.shared_data_path)?;
            let path = MdnAgentDataNodeWillowImpl::data_entry_path_from_key_components(comps)?;

            let cap_selector = CapSelector::new(
                cap.data_owner_ns,
                ReceiverSelector::Exact(
                    self.willow_peer
                        .willow_user_manager
                        .get_active_user_profile()
                        .await?,
                ),
                AreaSelector::ContainsArea(Area::new(
                    AreaSubspace::Id(cap.data_owner),
                    path,
                    Default::default(),
                )),
            );

            // TODO maybe we have to remove deleted cap area of interests from active session intent (reload session)
            let deleted = self
                .willow_peer
                .willow_delegation_manager
                .delete_capabilities(cap_selector)
                .await?;

            let mut entries_to_delete = vec![];

            for cap in deleted.iter() {
                let cap_ns = cap.granted_namespace();
                let cap_area = cap.granted_area();

                let entries = self
                    .willow_peer
                    .willow_data_manager
                    .get_entries(*cap_ns, cap_area.to_range())
                    .await?;

                entries_to_delete.extend(entries);
            }

            self.willow_peer
                .willow_data_manager
                .remove_entries_completely(entries_to_delete)
                .await?;

            Ok(deleted) as MeeDataSyncResult<Vec<McCapability>>
        });

        let res = join_all(tasks)
            .await
            .into_iter()
            .filter_map(|cap| match cap {
                Ok(v) => Some(v),
                Err(e) => {
                    log::error!("Error removing capability: {e}");
                    None
                }
            })
            .flatten()
            .collect();

        Ok(res)
    }
    pub fn run_revocation_handler(self) -> JoinHandle<()> {
        tokio::spawn(async move {
            loop {
                let block = async {
                    let res = self.read_revocation_list().await?;

                    self.revoke_capabilities(res).await?;

                    Ok(()) as MeeDataSyncResult
                };

                if let Err(e) = block.await {
                    log::error!("Error during capability revocation list handler: {e}");
                }

                sleep(Duration::from_secs(2)).await;
            }
        })
    }
}

pub struct ImportCapabilitiesFromRemotePeer {
    pub node_ticket: String,
    pub caps: Vec<MdnDataDelegationCapabilityPack>,
}

#[async_trait]
impl MdnAgentDataNodeDelegation for MdnDelegationManager {
    async fn import_capabilities_from_remote_peer(
        &self,
        caps: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle> {
        for cap in caps.caps.iter() {
            if let MdnDataDelegationCapabilityRole::RevocationListReceiver = cap.cap_role {
                let (ns, _) = cap_granted_components(&cap.cap_pack);

                self.mdn_ns_store_manager
                    .set_other_peer_revocation_list_ns(ns, cap.cap_issuer)
                    .await?;
            }
        }

        let ticket: NodeTicket = caps.node_ticket.parse()?;

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(
                caps.caps.iter().map(|c| c.cap_pack.clone()).collect(),
                &ticket,
            )
            .await?;

        let mut interests = Interests::builder();

        for cap in caps.caps.iter() {
            match cap.cap_role {
                MdnDataDelegationCapabilityRole::MdnDataSharing
                | MdnDataDelegationCapabilityRole::RevocationListReceiver => {
                    let (ns, area) = cap_granted_components(&cap.cap_pack);

                    interests = interests.add_area(ns, [area]);
                }
                _ => (),
            }
        }

        let init = SessionInit::new(interests, SessionMode::Continuous);

        let sync_intent = self
            .willow_peer
            .willow_session_manager
            .sync_with_peer(ticket.node_addr().node_id, init)
            .await?;

        Ok(sync_intent)
    }
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListRecord>> {
        let mut entries = vec![];

        let caps = self
            .mdn_ns_store_manager
            .get_others_cap_revoke_list_nss()
            .await?;

        for cap in caps {
            let ent = self
                .willow_peer
                .willow_data_manager
                .get_entries(
                    cap.ns_id,
                    Range3d::new(
                        Range::new_open(cap.peer_id),
                        Range::new_open(Path::new_empty()),
                        Default::default(),
                    ),
                )
                .await?;

            entries.extend(ent);
        }

        let res = futures::stream::iter(entries.into_iter())
            .then(move |entry| {
                let willow_peer = self.willow_peer.clone();

                async move {
                    let payload = willow_peer
                        .willow_data_manager
                        .read_entry_payload(entry.clone())
                        .await?;

                    let record = if let Some(payload) = payload {
                        if is_empty_entry_payload(&payload) {
                            return Ok(None);
                        }

                        Some(MdnDataRevocationListRecord::decode(&payload)?)
                    } else {
                        None
                    };

                    Ok(record) as MeeDataSyncResult<Option<MdnDataRevocationListRecord>>
                }
            })
            .filter_map(|record| async {
                match record {
                    Ok(record) => record,
                    Err(e) => {
                        log::error!("Error processing entry: {e}");
                        None
                    }
                }
            })
            .collect()
            .await;

        Ok(res)
    }
    async fn revoke_shared_access(
        &self,
        shared_data_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult {
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;
        let path = revocation_list_record_path(revoke_from)?;

        let payload = MdnDataRevocationListRecord {
            data_owner: self
                .willow_peer
                .willow_user_manager
                .get_active_user_profile()
                .await?,
            data_owner_ns: self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0,
            shared_data_path: shared_data_path.to_string(),
        };

        self.willow_peer
            .willow_data_manager
            .insert_entry(revoke_list_ns, path, payload.encode()?)
            .await?;

        Ok(())
    }
    async fn delegate_read_access(
        &self,
        shared_data_path: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<Vec<MdnDataDelegationCapabilityPack>> {
        let data_ns = self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0;
        // TODO subscribe to this namespace and check signals from peers with revoked capabilities
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;

        let shared_data_path = MdnAgentDataNodeWillowImpl::data_entry_path_from_key_components(
            key_components(&shared_data_path)?,
        )?;

        let cap_issuer = self
            .willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await?;

        let data_subset_restriction = RestrictArea::Restrict(Area::new(
            AreaSubspace::Any,
            shared_data_path,
            Range::full(),
        ));

        let mut data_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(data_ns),
                AccessMode::Read,
                DelegateTo::new(delegate_to, data_subset_restriction),
            )
            .await?
            .into_iter()
            .map(|cap_pack| MdnDataDelegationCapabilityPack {
                cap_pack,
                cap_issuer,
                cap_role: MdnDataDelegationCapabilityRole::MdnDataSharing,
            })
            .collect::<Vec<_>>();

        let revoke_list_restriction = RestrictArea::Restrict(Area::new(
            AreaSubspace::Id(
                self.willow_peer
                    .willow_user_manager
                    .get_active_user_profile()
                    .await?,
            ),
            Path::new_empty(),
            Range::full(),
        ));

        // Read capability for destination peer to check revocation list
        let revoke_list_read_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(revoke_list_ns),
                AccessMode::Read,
                DelegateTo::new(delegate_to, revoke_list_restriction),
            )
            .await?
            .into_iter()
            .map(|cap_pack| MdnDataDelegationCapabilityPack {
                cap_issuer,
                cap_pack,
                cap_role: MdnDataDelegationCapabilityRole::RevocationListReceiver,
            })
            .collect::<Vec<_>>();

        // Write capability for destination peer to signal their act of shared data access revocation
        let revoke_list_write_cap =
            WriteCapability::new_communal(revoke_list_ns, delegate_to, AccessMode::Write).map_err(
                |e| {
                    MeeDataSyncErr::WillowNamespaceHandler(format!(
                        "Error creating communal write capability: {e}"
                    ))
                },
            )?;

        let revoke_list_write_cap = MdnDataDelegationCapabilityPack {
            cap_issuer,
            cap_pack: CapabilityPack::Write(revoke_list_write_cap.into()),
            cap_role: MdnDataDelegationCapabilityRole::RevocationListSignalingSender,
        };

        data_caps.extend(revoke_list_read_caps);
        data_caps.push(revoke_list_write_cap);

        Ok(data_caps)
    }
}
