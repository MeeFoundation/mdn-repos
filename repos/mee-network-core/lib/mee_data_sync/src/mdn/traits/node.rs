use super::{
    network::MdnAgentDataNodeNetworkOps, store::MdnAgentDataNodeKvStore,
    user::MdnAgentDataNodeUserOps,
};
use crate::mdn::{
    data_owner::delegation::MdnAgentDataOwnerNodeDelegation,
    provider::delegation::MdnAgentProviderNodeDelegation,
};
use std::sync::Arc;

pub trait MdnAgentProviderNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnAgentProviderNodeDelegation + Send + Sync>;
}

pub trait MdnAgentDataOwnerNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnAgentDataOwnerNodeDelegation + Send + Sync>;
}
