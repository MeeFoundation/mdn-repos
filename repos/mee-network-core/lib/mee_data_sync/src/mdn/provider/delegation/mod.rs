use super::{caps::MdnProviderCapabilityManager, namespace::MdnProviderNamespaceStoreManager};
use crate::{
    error::MeeDataSyncResult,
    mdn::traits::{
        delegation::{
            revocation_done_record_path, revocation_list_record_path_prefix,
            REVOCATION_LIST_PATH_PREFIX,
        },
        store::{data_entry_path_from_key_components, key_components},
    },
    willow::{
        peer::WillowPeer,
        utils::{display_path, is_empty_entry_payload, path_from_bytes_slice, path_suffix},
    },
};
use futures::future::join_all;
use iroh_willow::proto::data_model::NamespaceId;
use iroh_willow::{
    interest::{AreaSelector, CapSelector, ReceiverSelector},
    proto::{
        data_model::{Entry, Path},
        grouping::{Area, AreaExt, AreaSubspace, Range3d},
        keys::UserId,
    },
};
use manager::{MdnDataRevocationListResponse, MdnProviderDelegationManager};
use std::{str::FromStr, sync::Arc, time::Duration};
use tokio::{task::JoinHandle, time::sleep};

pub mod manager;

#[derive(Clone)]
pub struct MdnProviderDelegationManagerImpl {
    willow_peer: WillowPeer,
    mdn_ns_store_manager: MdnProviderNamespaceStoreManager,
    mdn_provider_capability_manager: MdnProviderCapabilityManager,
    revocation_record_prefix_path: Path,
    current_user_id: UserId,
}

impl MdnProviderDelegationManagerImpl {
    pub async fn new(
        willow_peer: WillowPeer,
        mdn_ns_store_manager: MdnProviderNamespaceStoreManager,
        mdn_provider_capability_manager: MdnProviderCapabilityManager,
    ) -> MeeDataSyncResult<Self> {
        let user_id = willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await?;

        let revocation_record_prefix_path = revocation_list_record_path_prefix(user_id)?;

        Ok(Self {
            mdn_provider_capability_manager,
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
    pub fn run_background_jobs(self) -> Vec<JoinHandle<()>> {
        static CHECK_INTERVAL_MS: u64 = 2000;

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

                    sleep(Duration::from_millis(CHECK_INTERVAL_MS)).await;
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

                    sleep(Duration::from_millis(CHECK_INTERVAL_MS)).await;
                }
            }
        });

        let t3 = tokio::spawn({
            let this = this.clone();

            async move {
                loop {
                    let block = async {
                        if let Some(cap_list_ns) = this
                            .mdn_ns_store_manager
                            .get_data_owner_cap_list_ns()
                            .await?
                        {
                            this.update_data_owner_cap_list(cap_list_ns.0).await?;
                        }

                        Ok(()) as MeeDataSyncResult
                    };

                    if let Err(e) = block.await {
                        log::error!("Error handling data owner cap list update: {e}");
                    }

                    sleep(Duration::from_millis(CHECK_INTERVAL_MS)).await;
                }
            }
        });

        vec![t1, t2, t3]
    }
    async fn update_data_owner_cap_list(&self, cap_list_ns: NamespaceId) -> MeeDataSyncResult {
        Ok(())
    }
}
