use super::{
    network::MdnAgentDataNodeNetworkOps, store::MdnAgentDataNodeKvStore,
    user::MdnAgentDataNodeUserOps,
};
use crate::mdn::willow_impl::delegation::MdnDelegationManager;

pub trait MdnAgentDataNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> MdnDelegationManager;
}
