# Monorepo for MDN-related subsystems

## Local development (backend services)

### Database

- `docker` has installed
- db init commands:

```bash
  cd mee-utils/scripts
  make -f dev.service.common run_db_daemon # run it only once
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
