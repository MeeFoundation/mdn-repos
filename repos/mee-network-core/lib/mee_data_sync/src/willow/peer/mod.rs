use super::node::WillowNode;
use crate::error::MeeDataSyncResult;
use data_manager::WillowDataManager;
use delegation_manager::WillowDelegationManager;
use namespace_manager::WillowNamespaceManager;
use network_manager::WillowNetworkManager;
use session_manager::WillowSessionManager;
use user_manager::WillowUserManager;

pub mod data_manager;
pub mod delegation_manager;
pub mod namespace_manager;
pub mod network_manager;
pub mod session_manager;
pub mod user_manager;

#[derive(Clone)]
pub struct WillowPeer {
    pub willow_data_manager: WillowDataManager,
    pub willow_delegation_manager: WillowDelegationManager,
    pub willow_namespace_manager: WillowNamespaceManager,
    pub willow_network_manager: WillowNetworkManager,
    pub willow_user_manager: WillowUserManager,
    pub willow_session_manager: WillowSessionManager,
}

impl WillowPeer {
    pub async fn new(iroh_node_secret_key: iroh_net::key::SecretKey) -> MeeDataSyncResult<Self> {
        let willow_node = WillowNode::run(iroh_node_secret_key, Default::default()).await?;
        let willow_user_manager = WillowUserManager::new(willow_node.clone());
        let willow_network_manager = WillowNetworkManager::new(willow_node.clone());

        Ok(Self {
            willow_session_manager: WillowSessionManager::new(willow_node.clone()),
            willow_data_manager: WillowDataManager::new(
                willow_node.clone(),
                willow_user_manager.clone(),
            ),
            willow_namespace_manager: WillowNamespaceManager::new(
                willow_node.clone(),
                willow_user_manager.clone(),
            ),
            willow_delegation_manager: WillowDelegationManager::new(
                willow_node.clone(),
                willow_network_manager.clone(),
            ),
            willow_user_manager: WillowUserManager::new(willow_node),
            willow_network_manager,
        })
    }
}
