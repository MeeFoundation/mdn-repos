use super::utils::create_rng;
use mee_data_sync::{
    error::MeeDataSyncResult,
    mdn::{provider::node::MdnAgentProviderNodeWillowImpl, traits::node::MdnAgentProviderNode},
    willow::peer::WillowPeer,
};
use std::sync::Arc;

pub async fn create_node(
    entropy: &str,
) -> MeeDataSyncResult<Arc<dyn MdnAgentProviderNode + Send + Sync>> {
    let mut rng = create_rng(entropy);
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let oyt_mdn_node = MdnAgentProviderNodeWillowImpl::new(willow_peer).await?;

    Ok(Arc::new(oyt_mdn_node))
}
