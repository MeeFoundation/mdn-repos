# MDN data sync

## Code structure (src)

- `mdn` - MDN nodes based on `willow` for sync and `iroh` for networking
  - `data_owner` - local wallet holder specific willow node implementation
  - `provider` - provider specific willow node implementation
  - `traits` - common interfaces for store, capability delegation, networking, etc.
- `willow` - willow wrapper structures and functions for more convenient usage
  - `peer` - willow peer abstraction based on `iroh-willow` library
