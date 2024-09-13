use super::MdnProviderDelegationManagerImpl;
use crate::{
    error::MeeDataSyncResult,
    json_codec,
    mdn::common::{
        delegation::revocation_request_record_path,
        store::{data_entry_path_from_key_components, key_components, ReadDataRecord},
    },
    willow::{
        peer::delegation_manager::cap_granted_components,
        utils::{display_path, path_range_exact},
    },
};
use anyhow::Context;
use async_trait::async_trait;
use futures::TryStreamExt;
use iroh_net::ticket::NodeTicket;
use iroh_willow::{
    interest::{CapSelector, CapabilityPack, DelegateTo, Interests, RestrictArea},
    proto::{
        data_model::{NamespaceId, Path},
        grouping::{Area, AreaSubspace, Range, Range3d},
        keys::UserId,
        meadowcap::AccessMode,
    },
    session::{intents::IntentHandle, SessionInit, SessionMode},
};
use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnProviderCapabilityPack {
    pub capability_id: String,
    pub cap_receiver: UserId,
    pub shared_data_path: String,
    pub data_source_namespace: MdnProviderCapabilityPackObject,
    pub revocation_list_receiver_namespace: MdnProviderCapabilityPackObject,
    pub revocation_list_sender_namespace: MdnProviderCapabilityPackObject,
}

impl From<MdnProviderCapabilityPack> for MdnProviderCapabilityPackForOwner {
    fn from(
        MdnProviderCapabilityPack {
            capability_id,
            cap_receiver,
            shared_data_path,
            data_source_namespace,
            ..
        }: MdnProviderCapabilityPack,
    ) -> Self {
        Self {
            capability_id,
            cap_receiver,
            shared_data_path,
            data_source_namespace,
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnProviderCapabilityPackForOwner {
    pub capability_id: String,
    pub cap_receiver: UserId,
    pub shared_data_path: String,
    pub data_source_namespace: MdnProviderCapabilityPackObject,
}

json_codec!(MdnProviderCapabilityPack);
json_codec!(MdnProviderCapabilityPackForOwner);

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnProviderCapabilityPackObject {
    pub cap_pack: Vec<CapabilityPack>,
    pub cap_issuer: UserId,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnDataRevocationListResponse {
    pub record: MdnDataRevocationListRecord,
    pub signal_revocation_ns: NamespaceId,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MdnDataRevocationListRecord {
    pub shared_data_path: String,
    pub data_owner: UserId,
    pub data_owner_ns: NamespaceId,
    pub revocation_id: String,
    pub revocation_receiver: UserId,
}

json_codec!(MdnDataRevocationListRecord);

// TODO make abstract over willow specific details
#[async_trait]
pub trait MdnProviderDelegationManager {
    /// Imports permission to write the provider list of their capabilities into data owner namespace
    async fn import_cap_list_from_data_owner(
        &self,
        import_capabilities_from_data_owner: ImportCapabilitiesFromDataOwner,
    ) -> MeeDataSyncResult<()>;

    async fn import_search_schemas_ns_from_virtual_agent(
        &self,
        import_capabilities_from_virtual_agent: ImportCapabilitiesFromVirtualAgent,
    ) -> MeeDataSyncResult<IntentHandle>;

    async fn import_capabilities_from_provider(
        &self,
        caps: ImportCapabilitiesFromProvider,
    ) -> MeeDataSyncResult<IntentHandle>;

    /// Delegates read access from one provider to another one
    async fn delegate_read_access_to_provider(
        &self,
        data_subset_path: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnProviderCapabilityPack>;

    /// Revokes data access from one provider by another one
    async fn revoke_shared_access_from_provider(
        &self,
        cap_id: &str,
        shared_data_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult;

    /// Owner means MDN user (e.g. local/virtual wallet holder)
    async fn delegate_privileged_access_to_owner(
        &self,
        provider_node_ticket: String,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<DelegatePrivilegedAccessToOwner>;

    async fn delegated_caps(&self) -> MeeDataSyncResult<Vec<MdnProviderCapabilityPack>>;
    async fn read_revocation_list(&self) -> MeeDataSyncResult<Vec<MdnDataRevocationListResponse>>;
    async fn is_revocation_list_empty(&self) -> MeeDataSyncResult<bool>;
    async fn virtual_agent_search_schemas(&self) -> MeeDataSyncResult<Vec<ReadDataRecord>>;
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ImportCapabilitiesFromProvider {
    pub provider_node_ticket: String,
    #[schema(value_type = Object)]
    pub caps: MdnProviderCapabilityPack,
}

pub struct ImportCapabilitiesFromDataOwner {
    pub data_owner_node_ticket: String,
    pub caps: Vec<CapabilityPack>,
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ImportCapabilitiesFromVirtualAgent {
    pub virtual_agent_node_ticket: String,
    #[schema(value_type = Vec<Object>)]
    pub caps: Vec<CapabilityPack>,
}

pub struct DelegatePrivilegedAccessToOwner {
    pub provider_node_ticket: String,
    pub caps: Vec<CapabilityPack>,
}

#[async_trait]
impl MdnProviderDelegationManager for MdnProviderDelegationManagerImpl {
    async fn virtual_agent_search_schemas(&self) -> MeeDataSyncResult<Vec<ReadDataRecord>> {
        let Some(search_schemas_ns) = self.mdn_ns_store_manager.get_search_schemas_ns().await?
        else {
            return Ok(vec![]);
        };

        let list: Vec<_> = self
            .willow_peer
            .willow_data_manager
            .get_entries_stream(search_schemas_ns.0, Range3d::new_full())
            .await?
            .try_collect()
            .await?;

        let list = self
            .willow_peer
            .willow_data_manager
            .map_payload(
                list,
                |e| e.clone(),
                |e, payload| {
                    Ok(ReadDataRecord {
                        key: display_path(e.path()),
                        value: payload.to_vec(),
                    })
                },
            )
            .await?;

        Ok(list)
    }
    async fn delegated_caps(&self) -> MeeDataSyncResult<Vec<MdnProviderCapabilityPack>> {
        Ok(self.mdn_provider_capability_manager.store.list_caps()?)
    }
    async fn delegate_privileged_access_to_owner(
        &self,
        provider_node_ticket: String,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<DelegatePrivilegedAccessToOwner> {
        let data_ns = self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0;

        let caps = self
            .willow_peer
            .willow_delegation_manager
            .delegate_capabilities(
                CapSelector::any(data_ns),
                AccessMode::Write,
                DelegateTo::new(delegate_to, RestrictArea::None),
            )
            .await?;

        Ok(DelegatePrivilegedAccessToOwner {
            provider_node_ticket,
            caps,
        })
    }
    async fn import_cap_list_from_data_owner(
        &self,
        ImportCapabilitiesFromDataOwner {
            data_owner_node_ticket,
            mut caps,
        }: ImportCapabilitiesFromDataOwner,
    ) -> MeeDataSyncResult<()> {
        let ticket: NodeTicket = data_owner_node_ticket.parse()?;

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps.clone(), &ticket)
            .await?;

        if let Some(caps) = caps.pop() {
            let (data_owner_cap_list_ns, _) = cap_granted_components(&caps);

            self.mdn_ns_store_manager
                .set_data_owner_cap_list(data_owner_cap_list_ns)
                .await?;
        }

        Ok(())
    }
    async fn import_search_schemas_ns_from_virtual_agent(
        &self,
        ImportCapabilitiesFromVirtualAgent {
            virtual_agent_node_ticket,
            mut caps,
        }: ImportCapabilitiesFromVirtualAgent,
    ) -> MeeDataSyncResult<IntentHandle> {
        let ticket: NodeTicket = virtual_agent_node_ticket.parse()?;

        self.willow_peer
            .willow_delegation_manager
            .import_capabilities_from_remote_peer(caps.clone(), &ticket)
            .await?;

        let mut interests = Interests::builder();

        if let Some(caps) = caps.pop() {
            let (search_schemas_ns, _) = cap_granted_components(&caps);

            self.mdn_ns_store_manager
                .set_search_schemas_ns(search_schemas_ns)
                .await?;

            interests = interests.add_full_cap(search_schemas_ns);
        }

        let init = SessionInit::new(interests, SessionMode::Continuous);

        let sync_intent = self
            .willow_peer
            .willow_session_manager
            .sync_with_peer(ticket.node_addr().node_id, init)
            .await?;

        Ok(sync_intent)
    }
    async fn is_revocation_list_empty(&self) -> MeeDataSyncResult<bool> {
        Ok(self
            .willow_peer
            .willow_data_manager
            .is_entry_list_payload_empty(&self.revocation_list_entries().await?)
            .await?)
    }

    async fn import_capabilities_from_provider(
        &self,
        ImportCapabilitiesFromProvider {
            provider_node_ticket,
            caps,
        }: ImportCapabilitiesFromProvider,
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

        let ticket: NodeTicket = provider_node_ticket.parse()?;

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
                .get_entries(cap.revocation_ns, Range3d::new_full())
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

        let res = self
            .willow_peer
            .willow_data_manager
            .map_payload(
                entries,
                |e| e.0.clone(),
                |(_, signal_revocation_ns), payload| {
                    Ok(MdnDataRevocationListResponse {
                        record: MdnDataRevocationListRecord::decode(&payload)?,
                        signal_revocation_ns,
                    })
                },
            )
            .await?;

        Ok(res)
    }
    async fn revoke_shared_access_from_provider(
        &self,
        cap_id: &str,
        shared_data_path: &str,
        revoke_from: UserId,
    ) -> MeeDataSyncResult {
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;
        let path = revocation_request_record_path(revoke_from, &cap_id)?;

        let current_entry = self
            .willow_peer
            .willow_data_manager
            .get_entries(
                revoke_list_ns,
                Range3d::new(
                    Default::default(),
                    path_range_exact(path.clone())?.context("Wrong path range")?,
                    Default::default(),
                ),
            )
            .await?;

        if !self
            .willow_peer
            .willow_data_manager
            .is_entry_list_payload_empty(&current_entry)
            .await?
        {
            return Ok(());
        }

        let payload = MdnDataRevocationListRecord {
            revocation_receiver: revoke_from,
            revocation_id: cap_id.to_string(),
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
    /// TODO check if shared_data_path_str actually exists
    async fn delegate_read_access_to_provider(
        &self,
        shared_data_path_str: &str,
        delegate_to: UserId,
    ) -> MeeDataSyncResult<MdnProviderCapabilityPack> {
        let data_ns = self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0;
        let revoke_list_ns = self.mdn_ns_store_manager.get_cap_revoke_list_ns().await?.0;

        let shared_data_path =
            data_entry_path_from_key_components(key_components(&shared_data_path_str)?)?;

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
                CapSelector::any(data_ns),
                AccessMode::Read,
                DelegateTo::new(delegate_to, data_subset_restriction),
            )
            .await?;

        let data_source_namespace = MdnProviderCapabilityPackObject {
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
                CapSelector::any(revoke_list_ns),
                AccessMode::Read,
                DelegateTo::new(delegate_to, revoke_list_restriction),
            )
            .await?;

        let revocation_list_receiver_namespace = MdnProviderCapabilityPackObject {
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
                CapSelector::any(revoke_list_ns),
                AccessMode::Write,
                DelegateTo::new(delegate_to, revoke_list_response_restriction),
            )
            .await?;

        let revocation_list_sender_namespace = MdnProviderCapabilityPackObject {
            cap_issuer,
            cap_pack: revoke_list_write_caps,
        };

        let res = MdnProviderCapabilityPack {
            shared_data_path: shared_data_path_str.to_string(),
            capability_id: uuid::Uuid::new_v4().to_string(),
            cap_receiver: delegate_to,
            data_source_namespace: data_source_namespace.clone(),
            revocation_list_receiver_namespace,
            revocation_list_sender_namespace,
        };

        self.mdn_provider_capability_manager
            .store
            .insert_cap(res.clone())?;

        Ok(res)
    }
}
