# Monorepo for MDN-related subsystems

## Starting the demo

### First-time setup

* set up the database: `just setup-local-database`
* generate secrets: `just gen-dev-secrets`
* generate demo provider secrets: `just gen-demo-provider-secrets`

### Running the demo

* start the database: `just start-local-database`
* start demo: `just start-demo`
* stop demo: `just stop-demo`
