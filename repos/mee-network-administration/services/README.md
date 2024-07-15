# Cloud services and helper libraries

## Binaries

- [mdn_license_manager](mdn_license_manager/README.md) - Mee Data Network license application management for providers, PDAs and APSs.
- [mee_directory_service](mee_directory_service/README.md) - Provider/PDA discovery.
- [mee_user_manager](mee_user_manager/README.md) - Mee Network user management.
- [mee_provider_manager](mee_provider_manager/README.md) - Mee Network provider management.
- [oidc_prodiver](oidc_prodiver/README.md) - OIDC login for Mee Network providers client applications.

## Libraries

- [secrets_manager](secrets_manager/README.md) - It provides access to secure secrets management systems implemented by us or provided by third-party ones.
- [db_utils](db_utils/README.md) - Reusable database abstractions.
- [http_utils](http_utils/README.md) - Reusable HTTP-related utilities.
- [service_utils](service/README.md) - Utilities for internal cross-service communication.

## Local development

### Database

- `docker` has installed
- db init commands:

```bash
  make -f dev.common.mk run_db_daemon # run it only once
  cd path_to_concrete_service
  make create_db
  # make clean_db # if required
  # make stop_db_daemon # if required
```

### Service itself

To start a service run:

```bash
cd path_to_service
make dev
```

To start all required services at once run:

```bash
# tmux should be already installed
./run_for_dev.sh
# now, tmux has a new session with all services running
```
