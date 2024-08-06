use super::user_manager::WillowUserManager;
use crate::{error::MeeDataSyncResult, willow::node::WillowNode};
use iroh_willow::proto::keys::{NamespaceId, NamespaceKind};

#[derive(Clone)]
pub struct WillowNamespaceManager {
    willow_node: WillowNode,
    willow_user_manager: WillowUserManager,
}

// TODO add namespace mapping from human-readable names to Willow IDs
impl WillowNamespaceManager {
    pub fn new(willow_node: WillowNode, willow_user_manager: WillowUserManager) -> Self {
        Self {
            willow_node,
            willow_user_manager,
        }
    }

    async fn filter_namespaces_by_type(
        &self,
        ns_kind: NamespaceKind,
    ) -> MeeDataSyncResult<Vec<NamespaceId>> {
        let nss = self
            .willow_node
            .engine
            .list_namespaces()
            .await?
            .into_iter()
            .filter_map(|ns| {
                let ns_pk = ns.into_public_key();

                if let Ok(ns_pk) = ns_pk {
                    if ns_pk.kind() == ns_kind {
                        return Some(ns);
                    }
                } else {
                    log::error!("Error decoding namespace public key.");
                }

                None
            })
            .collect();

        Ok(nss)
    }

    pub async fn get_communal_namespaces(&self) -> MeeDataSyncResult<Vec<NamespaceId>> {
        self.filter_namespaces_by_type(NamespaceKind::Communal)
            .await
    }
    pub async fn get_owned_namespaces(&self) -> MeeDataSyncResult<Vec<NamespaceId>> {
        self.filter_namespaces_by_type(NamespaceKind::Owned).await
    }

    pub async fn create_namespace(&self, ns_kind: NamespaceKind) -> MeeDataSyncResult<NamespaceId> {
        let namespace_id = self
            .willow_node
            .engine
            .create_namespace(
                ns_kind,
                self.willow_user_manager.get_active_user_profile().await?,
            )
            .await?;

        Ok(namespace_id)
    }

    pub async fn get_namespace_or_create(
        &self,
        ns_kind: NamespaceKind,
    ) -> MeeDataSyncResult<NamespaceId> {
        let mut nss = self.filter_namespaces_by_type(ns_kind).await?;

        match nss.pop() {
            Some(v) => Ok(v),
            None => self.create_namespace(ns_kind).await,
        }
    }
}
