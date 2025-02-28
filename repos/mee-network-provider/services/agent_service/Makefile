include .env

# The order matters: the database name should be overridden before including the common makefile.
PG_DATABASE_NAME=agent_service_db

include ../../../mee-utils/scripts/dev.service.common.mk
RUST_LOG=info

TEST_CORS=--local-testing-cors-port=5173 \
					--local-testing-cors-port=5174 \
					--local-testing-cors-port=5175 \
					--local-testing-cors-port=5176 \
					--local-testing-cors-port=5177 \
					--local-testing-cors-port=5178

profile_provider1:
	RUST_LOG=${RUST_LOG} \
	DATABASE_URL=${DATABASE_URL} \
	SERVER_PORT=8010 \
	IROH_SIGNATURE_SECRET_PATH="../target/dev_iroh_signature1" \
		cargo instruments --bin agent_service -t alloc -- ${TEST_CORS}


run_provider1:
	cd ../dev_secrets_keygen && make gen_dev_provider_signature1
	
	RUST_LOG=${RUST_LOG} \
	DATABASE_URL=${DATABASE_URL} \
	SERVER_PORT=8010 \
	IROH_SIGNATURE_SECRET_PATH="../target/dev_iroh_signature1" \
		cargo run -- ${TEST_CORS}

run_provider2:
		cd ../dev_secrets_keygen && make gen_dev_provider_signature2

		RUST_LOG=${RUST_LOG} \
		DATABASE_URL=${DATABASE_URL} \
		SERVER_PORT=8011 \
		IROH_SIGNATURE_SECRET_PATH="../target/dev_iroh_signature2" \
			cargo run -- ${TEST_CORS}
