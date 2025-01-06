include .env

# The order matters: the database name should be overridden before including the common makefile.
PG_DATABASE_NAME=mdn_cloud_controller_db

include ../../../mee-utils/scripts/dev.service.common.mk

gen_dev_mee_signature:
	cd ../mee_dev_secrets && \
	make gen_dev_mee_signature \
		JWK_AUTH_SIGNATURE=mdn_cloud_controller_jwk_signature \
		DID_ID_SECRET_PATH=mdn_cloud_controller_did \
		IROH_SIGNATURE_SECRET_PATH=mdn_cloud_controller_iroh_signature