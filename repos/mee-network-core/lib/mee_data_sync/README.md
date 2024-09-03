# MDN data sync

## Code structure (`src/`)

- [mdn](src/mdn/mod.rs) - MDN nodes based on `willow` for sync and `iroh` for networking
  - [virtual_agent](src/mdn/virtual_agent/mod.rs) - local wallet holder specific willow node implementation
  - [local_agent](src/mdn/local_agent/mod.rs) - local wallet holder specific willow node implementation
  - [provider_agent](src/mdn/provider_agent/mod.rs) - provider specific willow node implementation
  - [common](src/mdn/common/mod.rs) - common interfaces for store, capability delegation, networking, etc.
- [willow](src/willow/mod.rs) - willow wrapper structures and functions for more convenient usage
  - [peer](src/willow/peer/mod.rs) - willow peer abstraction based on `iroh-willow` library
