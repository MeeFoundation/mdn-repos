use super::{caps::MdnProviderCapabilityManager, namespace::MdnProviderNamespaceStoreManager};
use crate::{
    error::MeeDataSyncResult,
    mdn::{
        traits::{
            delegation::{
                cap_list_record_path, revocation_done_record_path,
                revocation_request_record_path_prefix, CAPABILITY_LIST_PATH_PREFIX,
                REVOCATION_REQUEST_PATH_PREFIX,
            },
            store::{data_entry_path_from_key_components, key_components},
        },
        utils::find_revocation_cap_pairs,
    },
    willow::{peer::WillowPeer, utils::path_from_bytes_slice},
};
use futures::future::join_all;
use iroh_willow::{interest::UserSelector, proto::data_model::NamespaceId};
use iroh_willow::{
    interest::{AreaSelector, CapSelector},
    proto::{
        data_model::{Entry, Path},
        grouping::{Area, AreaExt, AreaSubspace, Range3d},
        keys::UserId,
    },
};
use manager::{
    MdnDataRevocationListRecord, MdnDataRevocationListResponse, MdnProviderCapabilityPackForOwner,
    MdnProviderDelegationManager,
};
use std::{collections::HashSet, sync::Arc, time::Duration};
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

        let revocation_record_prefix_path = revocation_request_record_path_prefix(user_id)?;

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
                UserSelector::Exact(self.current_user_id),
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

            let mut entries_to_delete = HashSet::new();

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
                .remove_entries_completely(entries_to_delete.into_iter().collect())
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

    async fn send_signal_to_owner_cap_list(&self, req_path: Path) -> MeeDataSyncResult {
        if let Some(owner_cap_list) = self
            .mdn_ns_store_manager
            .get_data_owner_cap_list_ns()
            .await?
        {
            let data_owner_cap_list = self
                .willow_peer
                .willow_data_manager
                .get_entries(owner_cap_list.0, Range3d::new_full())
                .await?;

            let req_in_owner_list = data_owner_cap_list
                .into_iter()
                .find(|e| e.path() == &req_path);

            if let Some(req_in_owner_list) = req_in_owner_list {
                let mut record = self
                    .willow_peer
                    .willow_data_manager
                    .map_payload([req_in_owner_list], |e| e.clone(), |_, p| Ok(p.to_vec()))
                    .await?;

                if let Some(record) = record.pop() {
                    let cap_id = req_path.get_component(2);

                    if let Some(cap_id) = cap_id {
                        let cap_id = String::from_utf8(cap_id.to_vec())?;
                        let local_cap_list =
                            self.mdn_provider_capability_manager.store.list_caps()?;
                        let removed = local_cap_list.iter().find(|c| c.capability_id == cap_id);

                        if let Some(removed) = removed {
                            self.mdn_provider_capability_manager
                                .store
                                .del_cap(&removed.capability_id)?;

                            let path = revocation_done_record_path(
                                removed.cap_receiver,
                                &removed.capability_id,
                            )?;

                            self.willow_peer
                                .willow_data_manager
                                .insert_entry(owner_cap_list.0, path, record)
                                .await?;
                        }
                    }
                }
            }
        }

        Ok(())
    }
    async fn clean_up_revocation_list(&self) -> MeeDataSyncResult {
        let revocation_list = self.revocation_list_entries().await?;

        if self
            .willow_peer
            .willow_data_manager
            .is_entry_list_payload_empty(&revocation_list)
            .await?
        {
            return Ok(());
        }

        let cap_pairs = find_revocation_cap_pairs(revocation_list)?;

        for (user, req, res) in cap_pairs {
            let req_path = req.path().clone();

            self.willow_peer
                .willow_data_manager
                .remove_entries_softly(vec![req])
                .await?;

            self.willow_peer
                .willow_data_manager
                .remove_entries_softly_for_subspace(vec![res], user)
                .await?;

            self.send_signal_to_owner_cap_list(req_path).await?;
        }

        Ok(())
    }
    async fn handle_owner_revocation_list(
        &self,
        cap_list_entries: Vec<Entry>,
    ) -> MeeDataSyncResult {
        let cap_prefix = path_from_bytes_slice(&[CAPABILITY_LIST_PATH_PREFIX.as_bytes()])?;
        let revoke_req_prefix =
            path_from_bytes_slice(&[REVOCATION_REQUEST_PATH_PREFIX.as_bytes()])?;

        let cap_req_list: Vec<_> = cap_list_entries
            .into_iter()
            .filter(|c| {
                c.path().is_prefixed_by(&cap_prefix) || c.path().is_prefixed_by(&revoke_req_prefix)
            })
            .collect();

        let cap_req_pairs = find_revocation_cap_pairs(cap_req_list)?;

        let cap_revoke_req_list = self
            .willow_peer
            .willow_data_manager
            .map_payload(
                cap_req_pairs.into_iter().map(|c| c.1),
                |p| p.clone(),
                |_e, p| Ok(MdnDataRevocationListRecord::decode(&p)?),
            )
            .await?;

        let local_caps = self.mdn_provider_capability_manager.store.list_caps()?;

        for cap in cap_revoke_req_list {
            let local_cap = local_caps
                .iter()
                .find(|c| c.capability_id == cap.revocation_id);

            if local_cap.is_some() {
                self.revoke_shared_access_from_provider(
                    &cap.revocation_id,
                    &cap.shared_data_path,
                    cap.revocation_receiver,
                )
                .await?;
            }
        }

        Ok(())
    }
    async fn check_data_owner_cap_list(&self, cap_list_ns: NamespaceId) -> MeeDataSyncResult {
        let local_cap_list = self.mdn_provider_capability_manager.store.list_caps()?;

        let mut data_owner_cap_list = self
            .willow_peer
            .willow_data_manager
            .get_entries(cap_list_ns, Range3d::new_full())
            .await?;

        for local_cap in local_cap_list.iter() {
            let cap_path = cap_list_record_path(local_cap.cap_receiver, &local_cap.capability_id)?;
            let cap_in_owner_list = data_owner_cap_list.iter().find(|c| c.path() == &cap_path);

            if cap_in_owner_list.is_none() {
                let (e, _) = self
                    .willow_peer
                    .willow_data_manager
                    .insert_entry(
                        cap_list_ns,
                        cap_path,
                        MdnProviderCapabilityPackForOwner::from(local_cap.clone()).encode()?,
                    )
                    .await?;

                data_owner_cap_list.push(e);
            }
        }

        self.handle_owner_revocation_list(data_owner_cap_list)
            .await?;

        Ok(())
    }
    async fn handle_revocation_logic(&self) -> MeeDataSyncResult {
        let res = self.read_revocation_list().await?;

        self.revoke_capabilities(res).await?;

        Ok(())
    }
    pub fn run_background_jobs(self) -> Vec<JoinHandle<()>> {
        static CHECK_INTERVAL_MS: u64 = 2000;

        let this = Arc::new(self);

        let t1 = tokio::spawn({
            let this = this.clone();

            async move {
                loop {
                    if let Err(e) = this.handle_revocation_logic().await {
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
                    if let Err(e) = this.clean_up_revocation_list().await {
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
                            this.check_data_owner_cap_list(cap_list_ns.0).await?;
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
}
