use mee_data_sync::{
    error::MeeDataSyncResult,
    mdn::{
        common::node::{MdnAgentProviderNode, MdnVirtualAgentNode},
        local_agent::node::MdnAgentDataOwnerNodeWillowImpl,
        provider_agent::node::MdnAgentProviderNodeWillowImpl,
        virtual_agent::node::VirtualAgentWillowNodeImpl,
    },
    willow::peer::WillowPeer,
};
use std::sync::Arc;

pub async fn create_provider_node() -> MeeDataSyncResult<Arc<dyn MdnAgentProviderNode + Send + Sync>>
{
    let mut rng = rand::thread_rng();
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let provider_mdn_node = MdnAgentProviderNodeWillowImpl::new(willow_peer).await?;

    Ok(Arc::new(provider_mdn_node))
}

pub async fn create_virtual_agent_node(
) -> MeeDataSyncResult<Arc<dyn MdnVirtualAgentNode + Send + Sync>> {
    let mut rng = rand::thread_rng();
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let virtual_agent_mdn_node = VirtualAgentWillowNodeImpl::new(willow_peer).await?;

    Ok(Arc::new(virtual_agent_mdn_node))
}

pub async fn create_data_owner_node() -> MeeDataSyncResult<MdnAgentDataOwnerNodeWillowImpl> {
    let mut rng = rand::thread_rng();
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let data_owner_mdn_node = MdnAgentDataOwnerNodeWillowImpl::new(willow_peer).await?;

    Ok(data_owner_mdn_node)
}
