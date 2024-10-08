# TEST PURPOSES ONLY MAKEFILE

build-provider-agent:
	docker --debug build \
		--progress=plain \
		--build-arg RUST_APP=agent_service \
		--build-arg SECRETS_KEYGEN=dev_secrets_keygen \
		-f rust.service.Dockerfile \
		-t provider_agent_service \
		../../..
