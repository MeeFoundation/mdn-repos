
JWK_AUTH_SIGNATURE=dev_mee_signature
IROH_SIGNATURE_SECRET_PATH=dev_iroh_signature
DID_ID_SECRET_PATH=dev_mee_did
SIGNATURES_SECRET_PATH_TEST_FOLDER="$$(pwd)/../target"

gen_dev_mee_signature:
	cargo run --bin=keygen -- \
		--jwk-auth-signature-secret-path=${JWK_AUTH_SIGNATURE} \
		--iroh-signature-secret-path=${IROH_SIGNATURE_SECRET_PATH} \
		--did-id-secret-path=${DID_ID_SECRET_PATH} \
		--signatures-secret-path-test-folder=${SIGNATURES_SECRET_PATH_TEST_FOLDER}
