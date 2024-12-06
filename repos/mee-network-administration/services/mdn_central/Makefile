include .env

# The order matters: the database name should be overridden before including the common makefile.
PG_DATABASE_NAME=mdn_central_db

include ../../../mee-utils/scripts/dev.service.common.mk

gen_dev_mee_signature:
	cd ../mee_dev_secrets && \
	make gen_dev_mee_signature \
		JWK_AUTH_SIGNATURE=mdn_central_jwk_signature \
		DID_ID_SECRET_PATH=mdn_central_did \
		IROH_SIGNATURE_SECRET_PATH=mdn_central_iroh_signature