use crate::willow::peer::WillowPeer;

pub struct MdnAgentDataOwnerNodeWillowImpl {
    pub(crate) willow_peer: WillowPeer,
}

impl MdnAgentDataOwnerNodeWillowImpl {
    pub fn new(willow_peer: WillowPeer) -> Self {
        Self { willow_peer }
    }
}
