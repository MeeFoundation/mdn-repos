use super::{
    network::MdnAgentDataNodeNetworkOps, store::MdnAgentDataNodeKvStore,
    user::MdnAgentDataNodeUserOps,
};
use crate::mdn::{
    data_owner::delegation::MdnDataOwnerDelegationManager,
    provider::delegation::manager::MdnProviderDelegationManager,
};
use std::sync::Arc;

pub trait MdnAgentProviderNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnProviderDelegationManager + Send + Sync>;
}

pub trait MdnAgentDataOwnerNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> MdnDataOwnerDelegationManager;
}
