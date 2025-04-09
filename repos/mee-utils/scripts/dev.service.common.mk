PG_DATABASE_HOST=localhost
PG_DATABASE_PORT=5432
PG_DATABASE_USER=postgres
PG_DATABASE_PSWD=postgres

export DATABASE_URL=postgres://${PG_DATABASE_USER}:${PG_DATABASE_PSWD}@${PG_DATABASE_HOST}:${PG_DATABASE_PORT}/${PG_DATABASE_NAME}

DB_CONT_NAME=local-dev-mee-pgsql
DOCKER_DB=docker exec -ti ${DB_CONT_NAME} psql
USE_LOCAL_DEV_DB:=$(USE_LOCAL_DEV_DB)
PGSQL_BIN=${DOCKER_DB}

ifeq (${USE_LOCAL_DEV_DB},1)
	PGSQL_BIN=psql
endif

RUST_LOG=info

stop_db_daemon:
	docker stop ${DB_CONT_NAME}

run_db_daemon:
	docker run --rm -d \
		-p ${PG_DATABASE_PORT}:${PG_DATABASE_PORT} \
		--name ${DB_CONT_NAME} \
		-e POSTGRES_USER=${PG_DATABASE_USER} \
		-e POSTGRES_PASSWORD=${PG_DATABASE_PSWD} \
		-e PGDATA=/var/lib/postgresql/data/pgdata \
		-v $(shell pwd)/../../tmp:/var/lib/postgresql/data \
		postgres:16.8

create_db:
	${PGSQL_BIN} \
		-U ${PG_DATABASE_USER} \
		-c "CREATE DATABASE ${PG_DATABASE_NAME} WITH OWNER=${PG_DATABASE_USER};"

	${PGSQL_BIN} \
		-U ${PG_DATABASE_USER} \
		-c "GRANT ALL PRIVILEGES ON DATABASE ${PG_DATABASE_NAME} TO ${PG_DATABASE_USER};"

clean_db:
	${PGSQL_BIN} \
		-U ${PG_DATABASE_USER} \
		-c "drop database if exists ${PG_DATABASE_NAME};"

dev:
	RUST_LOG=${RUST_LOG} DATABASE_URL=${DATABASE_URL} cargo run

db_migrate:
	RUST_LOG=${RUST_LOG} cargo run --bin=migrator

db_generate_models:
	sea-orm-cli generate entity \
		-u ${DATABASE_URL} \
		-o src/db_models \
		--with-serde serialize

dev_db_recreate: clean_db create_db db_migrate db_generate_models