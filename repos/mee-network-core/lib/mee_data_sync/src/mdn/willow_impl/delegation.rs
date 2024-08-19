use super::node::MdnAgentDataNodeWillowImpl;
use crate::{
    error::{MeeDataSyncErr, MeeDataSyncResult},
    mdn::{
        node::{
            MdnAgentDataNodeDelegation, MdnDataDelegationCapabilityPack,
            MdnDataDelegationCapabilityRole, MdnDataRevocationListRecord,
        },
        store::MdnAgentDataNodeKvStore,
    },
    willow::{
        peer::delegation_manager::{cap_granted_components, ImportCapabilitiesFromRemotePeer},
        utils::path_from_bytes_slice,
    },
};
use async_trait::async_trait;
use futures::StreamExt;
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, RestrictArea},
    proto::{
        data_model::{Path, WriteCapability},
        grouping::{Area, AreaSubspace, Range, Range3d},
        keys::UserId,
        meadowcap::AccessMode,
    },
    session::intents::IntentHandle,
};

pub fn revocation_list_record_path(user_id: UserId) -> MeeDataSyncResult<Path> {
    path_from_bytes_slice(&[b"revocation_list", user_id.as_bytes()])
}

#[async_trait]
impl MdnAgentDataNodeDelegation for MdnAgentDataNodeWillowImpl {
    async fn import_capabilities_from_remote_peer(
        &self,
        caps: ImportCapabilitiesFromRemotePeer,
    ) -> MeeDataSyncResult<IntentHandle> {
        for cap in caps.caps.iter() {
            if let MdnDataDelegationCapabilityRole::RevocationListReceiver = cap.cap_role {
                let (ns, _) = cap_granted_components(&cap.cap_pack);

                self.ns_store_manager
                    .set_other_peer_revocation_list_ns(ns, cap.cap_pack.receiver())
                    .await?;
            }
        }

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps)
            .await
    }
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListRecord>> {
        let mut entries = vec![];

        let caps = self
            .ns_store_manager
            .get_others_cap_revoke_list_nss()
            .await?;

        let user_id = self
            .willow_peer
            .willow_user_manager
            .get_active_user_profile()
            .await?;

        for cap in caps {
            let ent = self
                .willow_peer
                .willow_data_manager
                .get_entries(
                    cap.ns_id,
                    Range3d::new(
                        Range::new_open(user_id),
                        Range::new_open(Path::new_empty()),
                        Default::default(),
                    ),
                )
                .await?;

            entries.extend(ent);
        }

        log::warn!("revoke list: {entries:#?}");

        let res = futures::stream::iter(entries.into_iter())
            .then(move |entry| {
                let willow_peer = self.willow_peer.clone();

                async move {
                    let payload = willow_peer
                        .willow_data_manager
                        .read_entry_payload(entry.clone())
                        .await?;

                    let record = if let Some(payload) = payload {
                        if payload.is_empty() {
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
        let revoke_list_ns = self.ns_store_manager.get_cap_revoke_list_ns().await?.0;
        let path = revocation_list_record_path(revoke_from)?;

        let payload = MdnDataRevocationListRecord {
            data_owner: self
                .willow_peer
                .willow_user_manager
                .get_active_user_profile()
                .await?,
            data_owner_ns: self.ns_store_manager.get_agent_node_data_ns().await?.0,
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
        let data_ns = self.ns_store_manager.get_agent_node_data_ns().await?.0;
        // TODO subscribe to this namespace and check signals from peers with revoked capabilities
        let revoke_list_ns = self.ns_store_manager.get_cap_revoke_list_ns().await?.0;

        let shared_data_path =
            self.data_entry_path_from_key_components(self.key_components(&shared_data_path)?)?;

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
                cap_pack,
                cap_role: MdnDataDelegationCapabilityRole::MdnDataSharing,
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
            cap_pack: CapabilityPack::Write(revoke_list_write_cap.into()),
            cap_role: MdnDataDelegationCapabilityRole::RevocationListReceiver,
        };

        data_caps.extend(revoke_list_read_caps);
        data_caps.push(revoke_list_write_cap);

        Ok(data_caps)
    }
}
