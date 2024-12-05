pub enum ContextOperationsCapabilityDefinition {
    /// Identity context can be created by a user (e.g. on smart wallet) or by a provider (e.g. provider hosted MDN nodes + app)
    CreateContext,

    /// Identity context can be deleted only any MDN participant having this capability
    DeleteContext,

    /// Identity context can be delegated with read-write access to any MDN participant
    DelegateReadWriteContextToAny,

    /// Identity context can be delegated with read-write access only MDN data owner (MDN user)
    DelegateReadWriteContextToOwner,

    /// Identity context can be delegated with read access to any MDN participant
    DelegateReadContextToAny,
}

pub struct ContextOperationsCapability {
    /// Context-scoped user identifier
    from: String,
    /// MDN custodian identifier
    to: String,
    /// Context-scoped user identifier
    subject: String,
    /// JWT signature made with user private key
    signature: String,
    cap_def: ContextOperationsCapabilityDefinition,
    exp: i64,
}

pub enum ContextDataAccessPermissions {
    Read,
    Write,
    Delete,
}

pub struct ContextDataAccessDescription {
    pub paths: Vec<String>,
    pub permissions: Vec<ContextDataAccessPermissions>,
}

pub struct ContextDataAccessCapabilityDefinition {
    context_id: String,
    context_data_access: Vec<ContextDataAccessDescription>,
}

pub struct ContextDataAccessCapability {
    /// Context-scoped user identifier
    from: String,
    /// MDN custodian identifier
    to: String,
    /// Context-scoped user identifier
    subject: String,
    /// JWT signature made with user private key
    signature: String,
    cap_def: ContextDataAccessCapabilityDefinition,
    exp: i64,
}

pub enum MdnIdentityContextCapability {
    ContextOperations(ContextOperationsCapability),
    ContextDataAccess(ContextDataAccessCapability),
}

pub struct MdnCapabilitiesService {}
