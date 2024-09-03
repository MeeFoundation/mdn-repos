use super::utils::create_rng;
use mee_data_sync::{
    error::MeeDataSyncResult,
    mdn::{
        common::node::MdnAgentProviderNode, local_agent::node::MdnAgentDataOwnerNodeWillowImpl,
        provider_agent::node::MdnAgentProviderNodeWillowImpl,
    },
    willow::peer::WillowPeer,
};
use std::sync::Arc;

pub async fn create_provider_node(
    entropy: &str,
) -> MeeDataSyncResult<Arc<dyn MdnAgentProviderNode + Send + Sync>> {
    let mut rng = create_rng(entropy);
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let provider_mdn_node = MdnAgentProviderNodeWillowImpl::new(willow_peer).await?;

    Ok(Arc::new(provider_mdn_node))
}

pub async fn create_data_owner_node(
    entropy: &str,
) -> MeeDataSyncResult<MdnAgentDataOwnerNodeWillowImpl> {
    let mut rng = create_rng(entropy);
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let data_owner_mdn_node = MdnAgentDataOwnerNodeWillowImpl::new(willow_peer).await?;

    Ok(data_owner_mdn_node)
}
