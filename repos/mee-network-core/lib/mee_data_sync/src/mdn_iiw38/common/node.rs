use super::{
    network::MdnAgentDataNodeNetworkOps, store::MdnAgentDataNodeKvStore,
    user::MdnAgentDataNodeUserOps,
};
use crate::mdn_iiw38::{
    local_agent::delegation::MdnDataOwnerDelegationManager,
    provider_agent::delegation::manager::MdnProviderDelegationManager,
    virtual_agent::delegation::VirtualAgentDelegationManager,
};
use std::sync::Arc;

pub trait MdnAgentProviderNode: MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps {
    fn mdn_delegation_manager(&self) -> Arc<dyn MdnProviderDelegationManager + Send + Sync>;
    fn mdn_data_store(&self) -> Arc<dyn MdnAgentDataNodeKvStore + Send + Sync>;
}

pub trait MdnAgentDataOwnerNode:
    MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps + MdnAgentDataNodeKvStore
{
    fn mdn_delegation_manager(&self) -> MdnDataOwnerDelegationManager;
}

pub trait MdnVirtualAgentNode: MdnAgentDataNodeNetworkOps + MdnAgentDataNodeUserOps {
    fn mdn_delegation_manager(&self) -> VirtualAgentDelegationManager;
    fn search_schemas_store(&self) -> Arc<dyn MdnAgentDataNodeKvStore + Send + Sync>;
}
