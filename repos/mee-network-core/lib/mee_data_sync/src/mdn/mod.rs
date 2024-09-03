/// Single-user data owner Willow node for actual data - MDN local agent (e.g. mobile wallet).
pub mod local_agent;

/// Multi-user service provider Willow node - MDN provider agent.
pub mod provider_agent;

/// Multi-user data owner Willow node for metadata - MDN virtual agent (e.g. `itsmee.org` web app).
pub mod virtual_agent;

/// Common interfaces
pub mod common;

/// MDN specific utils
pub mod utils;
