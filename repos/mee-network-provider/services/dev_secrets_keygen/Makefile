
gen_dev_provider_signature1:
	cargo run -- \
		--jwk-auth-signature-secret-path="dev_provider_signature" \
		--iroh-signature-secret-path="dev_iroh_signature1" \
		--signatures-secret-path-test-folder="$$(pwd)/../target"

gen_dev_provider_signature2:
	cargo run -- \
		--jwk-auth-signature-secret-path="dev_provider_signature" \
		--iroh-signature-secret-path="dev_iroh_signature2" \
		--signatures-secret-path-test-folder="$$(pwd)/../target"