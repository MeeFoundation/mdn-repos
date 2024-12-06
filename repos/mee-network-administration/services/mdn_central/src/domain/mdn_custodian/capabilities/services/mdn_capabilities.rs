pub enum ContextOperationsCapabilityDefinition {
    /// Identity context can be created by a user (e.g. on smart wallet) or by a provider (e.g. MDN provider custodian storage + app)
    CreateContext,

    /// Identity context can be deleted by any MDN participant having this capability
    DeleteContext,

    /// Identity context can be revoked by any MDN participant having this capability
    RevokeContext,

    /// Identity context can be delegated with read-write access to any MDN participant
    DelegateReadWriteContextToAny,

    /// Identity context can be delegated with read-write access to MDN data owner (MDN user) only
    DelegateReadWriteContextToOwner,

    /// Identity context can be delegated with read access to any MDN participant
    DelegateReadContextToAny,
}

pub enum ContextDataAccessPermissions {
    Read,
    Write,
    Delete,
    Wildcard,
}

pub struct ContextDataAccessDescription {
    pub paths: Vec<String>,
    pub permissions: Vec<ContextDataAccessPermissions>,
}

pub struct ContextDataAccessCapabilityDefinition {
    context_id: String,
    context_data_access: Vec<ContextDataAccessDescription>,
}

pub enum MdnCapabilityDefinition {
    ContextOperations(ContextOperationsCapabilityDefinition),
    ContextDataAccess(ContextDataAccessCapabilityDefinition),
}

pub struct MdnCapability {
    /// Issuer. Context-scoped user identifier
    from: String,

    /// Audience. MDN custodian identifier
    to: String,

    /// Subject. Context-scoped user identifier
    sub: String,

    /// Capability definition
    cap: MdnCapabilityDefinition,

    /// Expiration date and time
    exp: i64,
}

pub struct MdnCapabilitiesService {}
