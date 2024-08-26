use super::namespace::MdnNamespaceStoreManager;
use crate::{
    error::MeeDataSyncResult,
    mdn::traits::{
        delegation::{
            revocation_done_record_path, revocation_list_record_path,
            revocation_list_record_path_prefix, REVOCATION_LIST_PATH_PREFIX,
        },
        store::{data_entry_path_from_key_components, key_components},
    },
    willow::{
        peer::{delegation_manager::cap_granted_components, WillowPeer},
        utils::{display_path, is_empty_entry_payload, path_from_bytes_slice, path_suffix},
    },
};
use async_trait::async_trait;
use futures::{future::join_all, StreamExt};
use iroh_net::ticket::NodeTicket;
use iroh_willow::{interest::CapabilityPack, proto::data_model::NamespaceId};
use iroh_willow::{
    interest::{AreaSelector, CapSelector, DelegateTo, Interests, ReceiverSelector, RestrictArea},
    proto::{
        data_model::{Entry, Path},
        grouping::{Area, AreaExt, AreaSubspace, Range, Range3d},
        keys::UserId,
        meadowcap::AccessMode,
    },
    session::{intents::IntentHandle, SessionInit, SessionMode},
};
use serde::{Deserialize, Serialize};
use std::{str::FromStr, sync::Arc, time::Duration};
use tokio::{task::JoinHandle, time::sleep};

#[derive(Debug)]
pub struct MdnDataDelegationCapabilityPack {
    pub data_source_namespace: MdnDataDelegationCapabilityPackObject,
    pub revocation_list_receiver_namespace: MdnDataDelegationCapabilityPackObject,
    pub revocation_list_sender_namespace: MdnDataDelegationCapabilityPackObject,
}

#[derive(Debug)]
pub struct MdnDataDelegationCapabilityPackObject {
    pub cap_pack: Vec<CapabilityPack>,
    pub cap_issuer: UserId,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnDataRevocationListResponse {
    pub record: MdnDataRevocationListRecord,
    pub signal_revocation_ns: NamespaceId,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct MdnDataRevocationListRecord {
    pub shared_data_path: String,
    pub data_owner: UserId,
    pub data_owner_ns: NamespaceId,
    pub revocation_id: String,
    pub revocation_receiver: UserId,
}

impl MdnDataRevocationListRecord {
    pub fn encode(&self) -> MeeDataSyncResult<Vec<u8>> {
        Ok(serde_json::to_vec(self)?)
    }
    pub fn decode(bytes: &[u8]) -> MeeDataSyncResult<Self> {
        Ok(serde_json::from_slice(bytes)?)
    }
}

// TODO make abstract over willow specific details
#[async_trait]
pub trait MdnAgentProviderNodeDelegation {
    /// Imports permission to write the provider list of their capabilities into data owner namespace
    async fn import_cap_list_from_data_owner(
        &self,
        data_owner_cap_list_ns: NamespaceId,
    ) -> MeeDataSyncResult<()>;

    async fn import_capabilities_from_provider(
        &self,
        caps: ImportCapabilitiesFromProvider,
    ) -> MeeDataSyncResult<IntentHandle>;

    /// Delegates read access from one provider to another one
    async fn delegate_read_access_to_provider(
        &self,
        data_subset_path: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnDataDelegationCapabilityPack>;

    /// Revokes data access from one provider by another one
    async fn revoke_shared_access_from_provider(
        &self,
        data_subset_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult;

    /// Owner means MDN user (e.g. local/virtual wallet holder)
    async fn delegate_full_access_to_owner(
        &self,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnDataDelegationCapabilityPack>;

    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListResponse>>;
    async fn is_revocation_list_empty(&self) -> MeeDataSyncResult<bool>;
}

#[derive(Clone)]
pub struct MdnProviderDelegationManager {
    willow_peer: WillowPeer,
    mdn_ns_store_manager: MdnNamespaceStoreManager,
    revocation_record_prefix_path: Path,
    current_user_id: UserId,
}

impl MdnProviderDelegationManager {
    pub async fn new(
        willow_peer: WillowPeer,
        mdn_ns_store_manager: MdnNamespaceStoreManager,
    ) -> MeeDataSyncResult<Self> {
        let user_id = willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await?;

        let revocation_record_prefix_path = revocation_list_record_path_prefix(user_id)?;

        Ok(Self {
            willow_peer,
            mdn_ns_store_manager,
            revocation_record_prefix_path,
            current_user_id: user_id,
        })
    }
    async fn send_signal_to_remove_revocation_cap(
        &self,
        MdnDataRevocationListResponse {
            record,
            signal_revocation_ns,
        }: MdnDataRevocationListResponse,
    ) -> MeeDataSyncResult {
        let path = revocation_done_record_path(self.current_user_id, &record.revocation_id)?;

        self.willow_peer
            .willow_data_manager
            .insert_entry(signal_revocation_ns, path, record.encode()?)
            .await?;

        Ok(())
    }
    async fn revoke_capabilities(
        &self,
        caps: Vec<MdnDataRevocationListResponse>,
    ) -> MeeDataSyncResult {
        let tasks = caps.into_iter().map(|cap| async move {
            let comps = key_components(&cap.record.shared_data_path)?;
            let path = data_entry_path_from_key_components(comps)?;

            let cap_selector = CapSelector::new(
                cap.record.data_owner_ns,
                ReceiverSelector::Exact(self.current_user_id),
                AreaSelector::ContainsArea(Area::new(
                    AreaSubspace::Id(cap.record.data_owner),
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

            self.send_signal_to_remove_revocation_cap(cap).await?;

            Ok(()) as MeeDataSyncResult
        });

        let res = join_all(tasks).await;

        for r in res {
            if let Err(e) = r {
                log::error!("Error removing capability: {e}");
            }
        }

        Ok(())
    }
    async fn revocation_list_entries(&self) -> MeeDataSyncResult<Vec<Entry>> {
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?;

        let revocation_list = self
            .willow_peer
            .willow_data_manager
            .get_entries(revoke_list_ns.0, Range3d::new_full())
            .await?;

        Ok(revocation_list)
    }
    async fn is_revocation_list_empty(
        &self,
        revocation_list: &Vec<Entry>,
    ) -> MeeDataSyncResult<bool> {
        let mut payloads = vec![];

        for e in revocation_list.iter() {
            let p = self
                .willow_peer
                .willow_data_manager
                .read_entry_payload(e.clone())
                .await?;
            if let Some(p) = p {
                payloads.push((display_path(e.path()), p));
            }
        }

        let pred = payloads.iter().all(|(_, p)| is_empty_entry_payload(p));

        Ok(pred)
    }
    async fn clean_up_revocation_list(&self) -> MeeDataSyncResult {
        let revocation_list = self.revocation_list_entries().await?;

        if self.is_revocation_list_empty(&revocation_list).await? {
            return Ok(());
        }

        let pref = path_from_bytes_slice(&[REVOCATION_LIST_PATH_PREFIX.as_bytes()])?;

        let (request_list, readiness_list): (Vec<_>, Vec<_>) = revocation_list
            .into_iter()
            .partition(|e| e.path().is_prefixed_by(&pref));

        for req in request_list {
            let common_path = path_suffix(req.path(), 1)?;

            let req_res = readiness_list.iter().find_map(|e| {
                let res = || {
                    let path = path_suffix(e.path(), 1)?;
                    let user_id = path.get_component(0);

                    if let Some(user_id) = user_id {
                        let user = UserId::from_str(&String::from_utf8(user_id.to_vec())?)?;

                        if &user == e.subspace_id() && path == common_path {
                            return MeeDataSyncResult::Ok(Some((user, req.clone(), e.clone())));
                        }
                    }

                    MeeDataSyncResult::Ok(None)
                };

                match res() {
                    Ok(v) => v,
                    Err(e) => {
                        log::error!("Error looking for revocation list readiness entries: {e}");
                        None
                    }
                }
            });

            if let Some((user, req, res)) = req_res {
                self.willow_peer
                    .willow_data_manager
                    .remove_entries_softly(vec![req])
                    .await?;

                self.willow_peer
                    .willow_data_manager
                    .remove_entries_softly_for_subspace(vec![res], user)
                    .await?;
            }
        }

        Ok(())
    }
    pub fn run_revocation_handlers(self) -> (JoinHandle<()>, JoinHandle<()>) {
        let this = Arc::new(self);

        let t1 = tokio::spawn({
            let this = this.clone();

            async move {
                loop {
                    let block = async {
                        let res = this.read_revocation_list().await?;

                        this.revoke_capabilities(res).await?;

                        Ok(()) as MeeDataSyncResult
                    };

                    if let Err(e) = block.await {
                        log::error!("Error reading revocation list: {e}");
                    }

                    sleep(Duration::from_secs(2)).await;
                }
            }
        });

        let t2 = tokio::spawn({
            let this = this.clone();

            async move {
                loop {
                    let block = async {
                        this.clean_up_revocation_list().await?;

                        Ok(()) as MeeDataSyncResult
                    };

                    if let Err(e) = block.await {
                        log::error!("Error signaling revocation list cap deletion: {e}");
                    }

                    sleep(Duration::from_secs(2)).await;
                }
            }
        });

        (t1, t2)
    }
}

pub struct ImportCapabilitiesFromProvider {
    pub node_ticket: String,
    pub caps: MdnDataDelegationCapabilityPack,
}

pub struct ImportCapabilitiesForDataOwner {
    pub node_ticket: String,
    pub caps: String,
}

#[async_trait]
impl MdnAgentProviderNodeDelegation for MdnProviderDelegationManager {
    async fn import_cap_list_from_data_owner(
        &self,
        data_owner_cap_list_ns: NamespaceId,
    ) -> MeeDataSyncResult<()> {
        self.mdn_ns_store_manager
            .set_data_owner_cap_list(data_owner_cap_list_ns)
            .await
    }
    async fn is_revocation_list_empty(&self) -> MeeDataSyncResult<bool> {
        Ok(self
            .is_revocation_list_empty(&self.revocation_list_entries().await?)
            .await?)
    }

    async fn import_capabilities_from_provider(
        &self,
        ImportCapabilitiesFromProvider { node_ticket, caps }: ImportCapabilitiesFromProvider,
    ) -> MeeDataSyncResult<IntentHandle> {
        if let Some(cap) = caps.revocation_list_receiver_namespace.cap_pack.first() {
            let (revocation_ns, _) = cap_granted_components(&cap);

            self.mdn_ns_store_manager
                .set_other_peer_revocation_list_ns(
                    revocation_ns,
                    caps.revocation_list_receiver_namespace.cap_issuer,
                )
                .await?;
        }

        let ticket: NodeTicket = node_ticket.parse()?;

        let mut caps_for_import = vec![];
        caps_for_import.extend(caps.revocation_list_sender_namespace.cap_pack);
        caps_for_import.extend(caps.revocation_list_receiver_namespace.cap_pack.clone());
        caps_for_import.extend(caps.data_source_namespace.cap_pack.clone());

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps_for_import, &ticket)
            .await?;

        let mut interests = Interests::builder();

        let mut interest_caps = vec![];

        interest_caps.extend(caps.revocation_list_receiver_namespace.cap_pack);
        interest_caps.extend(caps.data_source_namespace.cap_pack);

        for cap in interest_caps.iter() {
            let (ns, area) = cap_granted_components(&cap);

            interests = interests.add_area(ns, [area]);
        }

        let init = SessionInit::new(interests, SessionMode::Continuous);

        let sync_intent = self
            .willow_peer
            .willow_session_manager
            .sync_with_peer(ticket.node_addr().node_id, init)
            .await?;

        Ok(sync_intent)
    }
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListResponse>> {
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
                    cap.revocation_ns,
                    Range3d::new(
                        Default::default(),
                        Range::new_open(Path::new_empty()),
                        Default::default(),
                    ),
                )
                .await?
                .into_iter()
                .filter_map(|entry| {
                    if self
                        .revocation_record_prefix_path
                        .is_prefix_of(entry.path())
                    {
                        Some((entry, cap.revocation_ns))
                    } else {
                        None
                    }
                });

            entries.extend(ent);
        }

        let res = futures::stream::iter(entries.into_iter())
            .then(move |(entry, signal_revocation_ns)| {
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

                        Some(MdnDataRevocationListResponse {
                            record: MdnDataRevocationListRecord::decode(&payload)?,
                            signal_revocation_ns,
                        })
                    } else {
                        None
                    };

                    Ok(record) as MeeDataSyncResult<Option<MdnDataRevocationListResponse>>
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
    async fn revoke_shared_access_from_provider(
        &self,
        shared_data_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult {
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;
        let revocation_id = uuid::Uuid::new_v4().to_string();
        let path = revocation_list_record_path(revoke_from, &revocation_id)?;

        let payload = MdnDataRevocationListRecord {
            revocation_receiver: revoke_from,
            revocation_id,
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
    async fn delegate_full_access_to_owner(
        &self,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnDataDelegationCapabilityPack> {
        todo!()
    }
    async fn delegate_read_access_to_provider(
        &self,
        shared_data_path: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnDataDelegationCapabilityPack> {
        let data_ns = self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0;
        // TODO subscribe to this namespace and check signals from peers with revoked capabilities
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;

        let shared_data_path =
            data_entry_path_from_key_components(key_components(&shared_data_path)?)?;

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

        let data_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(data_ns),
                AccessMode::Read,
                DelegateTo::new(delegate_to, data_subset_restriction),
            )
            .await?;

        let data_source_namespace = MdnDataDelegationCapabilityPackObject {
            cap_pack: data_caps,
            cap_issuer,
        };

        let revoke_list_restriction = RestrictArea::Restrict(Area::new(
            AreaSubspace::Any,
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
            .await?;

        let revocation_list_receiver_namespace = MdnDataDelegationCapabilityPackObject {
            cap_issuer,
            cap_pack: revoke_list_read_caps,
        };

        let revoke_list_response_restriction = RestrictArea::Restrict(Area::new(
            AreaSubspace::Id(delegate_to),
            // TODO maybe also limit access to some prefix path
            Path::new_empty(),
            Range::full(),
        ));

        let revoke_list_write_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::widest(revoke_list_ns),
                AccessMode::Write,
                DelegateTo::new(delegate_to, revoke_list_response_restriction),
            )
            .await?;

        let revocation_list_sender_namespace = MdnDataDelegationCapabilityPackObject {
            cap_issuer,
            cap_pack: revoke_list_write_caps,
        };

        let res = MdnDataDelegationCapabilityPack {
            data_source_namespace,
            revocation_list_receiver_namespace,
            revocation_list_sender_namespace,
        };

        Ok(res)
    }
}
