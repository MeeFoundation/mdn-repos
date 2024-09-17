include .env

# The order matters: the database name should be overridden before including the common makefile.
PG_DATABASE_NAME=agent_service_db

include ../../../mee-utils/scripts/dev.service.common.mk
RUST_LOG=info

run_provider1:
	cd ../dev_secrets && make gen_dev_provider_signature1
	make dev IROH_SIGNATURE_SECRET_PATH="../target/dev_iroh_signature1"

run_provider2:
		cd ../dev_secrets && make gen_dev_provider_signature2
		make dev SERVER_PORT=8011 \
			LOCAL_TESTING_CORS_PORT=5174 \
			IROH_SIGNATURE_SECRET_PATH="../target/dev_iroh_signature2"