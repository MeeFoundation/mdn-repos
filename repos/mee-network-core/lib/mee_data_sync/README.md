# MDN data sync

## Code structure (`src/`)

- [mdn_iiw38](src/mdn/mod.rs) - MDN nodes demo implementation for IIW38 built on top of `willow` for sync and `iroh` for networking
  - [virtual_agent](src/mdn/virtual_agent/mod.rs) - virtual agent specific willow node implementation
  - [local_agent](src/mdn/local_agent/mod.rs) - local wallet holder specific willow node implementation
  - [provider_agent](src/mdn/provider_agent/mod.rs) - provider specific willow node implementation
  - [common](src/mdn/common/mod.rs) - common interfaces for store, capability delegation, networking, etc.
- [willow](src/willow/mod.rs) - willow wrapper structures and functions for more convenient usage
  - [peer](src/willow/peer/mod.rs) - willow peer abstraction based on `willow-iroh` library
