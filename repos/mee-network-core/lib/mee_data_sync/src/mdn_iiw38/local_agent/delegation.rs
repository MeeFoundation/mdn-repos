use super::namespace::MdnDataOwnerNamespaceStoreManager;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    mdn_iiw38::{
        common::delegation::{
            revocation_request_record_path, CAPABILITY_LIST_PATH_PREFIX,
            REVOCATION_DONE_PATH_PREFIX, REVOCATION_REQUEST_PATH_PREFIX,
        },
        provider_agent::delegation::manager::{
            DelegatePrivilegedAccessToOwner, MdnDataRevocationListRecord,
            MdnProviderCapabilityPackForOwner,
        },
    },
    willow::{
        peer::{delegation_manager::cap_granted_components, WillowPeer},
        utils::path_suffix,
    },
};
use futures::TryStreamExt;
use iroh_base::ticket::NodeTicket;
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, Interests, RestrictArea},
    proto::{
        data_model::{Entry, Path, PathExt},
        grouping::{Area, Range3d},
        keys::UserId,
        meadowcap::AccessMode,
    },
    session::{SessionInit, SessionMode},
};
use mee_async_utils::async_move;
use mee_macro_utils::let_clone;
use std::{sync::Arc, time::Duration};
use tokio::{task::JoinHandle, time::sleep};

pub trait MdnAgentDataOwnerNodeDelegation {}

#[derive(Clone)]
pub struct MdnDataOwnerDelegationManager {
    willow_peer: WillowPeer,
    mdn_ns_store_manager: MdnDataOwnerNamespaceStoreManager,
    cap_list_prefix: Path,
    revoke_req_prefix: Path,
    revoke_res_prefix: Path,
}

impl MdnDataOwnerDelegationManager {
    pub fn new(
        willow_peer: WillowPeer,
        mdn_ns_store_manager: MdnDataOwnerNamespaceStoreManager,
    ) -> MeeDataSyncResult<Self> {
        Ok(Self {
            cap_list_prefix: Path::from_bytes(&[CAPABILITY_LIST_PATH_PREFIX.as_bytes()])?,
            revoke_req_prefix: Path::from_bytes(&[REVOCATION_REQUEST_PATH_PREFIX.as_bytes()])?,
            revoke_res_prefix: Path::from_bytes(&[REVOCATION_DONE_PATH_PREFIX.as_bytes()])?,
            willow_peer,
            mdn_ns_store_manager,
        })
    }
    pub async fn revoke_shared_access_from_provider(
        &self,
        MdnProviderCapabilityPackForOwner {
            capability_id,
            cap_receiver,
            shared_data_path,
            mut data_source_namespace,
            ..
        }: MdnProviderCapabilityPackForOwner,
    ) -> MeeDataSyncResult {
        let revoke_list_ns = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?
            .0;

        let path = revocation_request_record_path(cap_receiver, &capability_id)?;

        let data_cap = data_source_namespace.cap_pack.pop().ok_or_else(|| {
            MeeDataSyncErr::WillowDelegationHandler(format!(
                "Missing capability for data namespace {data_source_namespace:#?}"
            ))
        })?;

        let (data_owner_ns, _) = cap_granted_components(&data_cap);

        let payload = MdnDataRevocationListRecord {
            revocation_receiver: cap_receiver,
            revocation_id: capability_id,
            data_owner: data_source_namespace.cap_issuer,
            data_owner_ns,
            shared_data_path,
        };

        self.willow_peer
            .willow_data_manager
            .insert_entry(revoke_list_ns, path, payload.encode()?)
            .await?;

        Ok(())
    }
    pub async fn import_privileged_access_from_provider(
        &self,
        DelegatePrivilegedAccessToOwner {
            provider_node_ticket,
            caps,
        }: DelegatePrivilegedAccessToOwner,
    ) -> MeeDataSyncResult {
        let ticket: NodeTicket = provider_node_ticket.parse()?;

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps, &ticket)
            .await?;

        Ok(())
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

        let mut write_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::any(cap_list_ns),
                AccessMode::Write,
                DelegateTo::new(provider_id, data_subset_restriction),
            )
            .await?;

        let mut read_caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::any(cap_list_ns),
                AccessMode::Read,
                DelegateTo::new(provider_id, RestrictArea::None),
            )
            .await?;

        write_caps.append(&mut read_caps);

        Ok(write_caps)
    }
    pub async fn data_owner_cap_list(
        &self,
    ) -> MeeDataSyncResult<Vec<MdnProviderCapabilityPackForOwner>> {
        let cap_list_ns = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?
            .0;

        let cap_list: Vec<_> = self
            .willow_peer
            .willow_data_manager
            .get_entries_stream(cap_list_ns, Range3d::new_full())
            .await?
            .try_filter(|e| async_move! { e.path().is_prefixed_by(&self.cap_list_prefix) })
            .try_collect()
            .await?;

        let cap_list: Vec<_> = self
            .willow_peer
            .willow_data_manager
            .map_payload(
                cap_list,
                |e| e.clone(),
                |_, p| MdnProviderCapabilityPackForOwner::decode(&p),
            )
            .await?;

        Ok(cap_list)
    }
    async fn sync_cap_list_with_providers(&self) -> MeeDataSyncResult {
        let cap_list_ns = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?
            .0;

        let peers = self.willow_peer.willow_network_manager.remote_peers()?;

        for peer in peers {
            let this = self.clone();

            // TODO attach task for proper cancellation
            tokio::spawn(async move {
                let task = async {
                    let interests = Interests::builder().add_full_cap(cap_list_ns).build();

                    // TODO replace with live session
                    let init = SessionInit::new(interests, SessionMode::ReconcileOnce);

                    let mut sync_intent = this
                        .willow_peer
                        .willow_session_manager
                        .sync_with_peer(peer.node_id, init)
                        .await?;

                    // let mut sync_intent = progress_session_intents(sync_intent).await;

                    sync_intent.complete().await.map_err(anyhow::Error::msg)?;

                    MeeDataSyncResult::Ok(())
                };

                if let Err(e) = task.await {
                    log::error!("Error handling cap list syncing with providers: {e}");
                }
            });
        }

        Ok(())
    }
    pub async fn cap_list_entries(&self) -> MeeDataSyncResult<Vec<Entry>> {
        let cap_list_ns = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?;

        let cap_list = self
            .willow_peer
            .willow_data_manager
            .get_entries(cap_list_ns.0, Range3d::new_full())
            .await?;

        Ok(cap_list)
    }
    async fn clean_up_cap_list(&self) -> MeeDataSyncResult {
        let cap_list = self.cap_list_entries().await?;

        let mut cap_list_entries = vec![];
        let mut req_list_entries = vec![];
        let mut res_list_entries = vec![];
        let mut cap_req_res_list_entries = vec![];

        for cap in cap_list {
            if cap.path().is_prefixed_by(&self.cap_list_prefix) {
                cap_list_entries.push(cap);
            } else if cap.path().is_prefixed_by(&self.revoke_req_prefix) {
                req_list_entries.push(cap);
            } else if cap.path().is_prefixed_by(&self.revoke_res_prefix) {
                res_list_entries.push(cap);
            }
        }

        for cap in cap_list_entries {
            let cap_prefix = path_suffix(cap.path(), 1)?;

            let req = req_list_entries.iter().enumerate().find_map(|(i, e)| {
                let req_prefix = path_suffix(e.path(), 1);

                if let Ok(req_prefix) = req_prefix {
                    if cap_prefix == req_prefix {
                        return Some(i);
                    }
                }

                None
            });

            let res = res_list_entries.iter().enumerate().find_map(|(i, e)| {
                let res_prefix = path_suffix(e.path(), 1);

                if let Ok(res_prefix) = res_prefix {
                    if cap_prefix == res_prefix {
                        return Some(i);
                    }
                }

                None
            });

            if let (Some(req), Some(res)) = (
                req.map(|i| req_list_entries.remove(i)),
                res.map(|i| res_list_entries.remove(i)),
            ) {
                cap_req_res_list_entries.push((cap, req, res));
            }
        }

        for (cap, req, res) in cap_req_res_list_entries {
            let task = async {
                self.willow_peer
                    .willow_data_manager
                    .remove_entries_softly(vec![req])
                    .await?;

                let user = cap.subspace_id().clone();

                self.willow_peer
                    .willow_data_manager
                    .remove_entries_softly_for_subspace(vec![cap], user)
                    .await?;

                let user = res.subspace_id().clone();

                self.willow_peer
                    .willow_data_manager
                    .remove_entries_softly_for_subspace(vec![res], user)
                    .await?;

                MeeDataSyncResult::Ok(())
            };

            if let Err(e) = task.await {
                log::error!("Error during data owner cap list cleaning up: {e}");
            }
        }

        Ok(())
    }

    pub fn run_background_jobs(self) -> Vec<JoinHandle<()>> {
        static CHECK_INTERVAL_MS: u64 = 2000;

        let this = Arc::new(self);

        let t1 = tokio::spawn({
            let_clone!(this);

            async move {
                loop {
                    if let Err(e) = this.sync_cap_list_with_providers().await {
                        log::error!("Error reading data owner cap list: {e}");
                    }

                    sleep(Duration::from_millis(CHECK_INTERVAL_MS)).await;
                }
            }
        });

        let t2 = tokio::spawn({
            let_clone!(this);

            async move {
                loop {
                    if let Err(e) = this.clean_up_cap_list().await {
                        log::error!("Error cleaning up owner cap list: {e}");
                    }

                    sleep(Duration::from_millis(CHECK_INTERVAL_MS)).await;
                }
            }
        });

        vec![t1, t2]
    }
}
