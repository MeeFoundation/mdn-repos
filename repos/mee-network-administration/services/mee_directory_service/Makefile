include .env

# The order matters: the database name should be overridden before including the common makefile.
PG_DATABASE_NAME=mee_directory_service_db

include ../../../mee-utils/scripts/dev.service.common.mk

run_vagent:
	cd ../mee_dev_secrets && make gen_dev_mee_signature
	make dev