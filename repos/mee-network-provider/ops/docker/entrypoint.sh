#!/usr/bin/env bash

RUST_LOG="${RUST_LOG:-info}"

# dev purposes keygen app
SECRETS_KEYGEN=dev_secrets_keygen
# keygen options
DEV_JWK_AUTH_SIGNATURE_SECRET_PATH=dev_provider_signature
DEV_IROH_SIGNATURE_SECRET_PATH=dev_iroh_signature1
DEV_SIGNATURES_SECRET_PATH_TEST_FOLDER=/tmp

# name of main app to run
RUST_APP=agent_service
# main app options
JWK_AUTH_SIGNATURE_SECRET_PATH="${DEV_SIGNATURES_SECRET_PATH_TEST_FOLDER}/${DEV_JWK_AUTH_SIGNATURE_SECRET_PATH}"
IROH_SIGNATURE_SECRET_PATH="${DEV_SIGNATURES_SECRET_PATH_TEST_FOLDER}/${DEV_IROH_SIGNATURE_SECRET_PATH}"

set -e
echo "----------------------------------------"
env
echo "----------------------------------------"

RUST_LOG=${RUST_LOG} ${SECRETS_KEYGEN} \
  --jwk-auth-signature-secret-path=${DEV_JWK_AUTH_SIGNATURE_SECRET_PATH} \
  --iroh-signature-secret-path=${DEV_IROH_SIGNATURE_SECRET_PATH} \
  --signatures-secret-path-test-folder=${DEV_SIGNATURES_SECRET_PATH_TEST_FOLDER}

echo "----------------------------------------"
echo "Running app server: \"$RUST_APP\""
echo "----------------------------------------"

ls ${DEV_SIGNATURES_SECRET_PATH_TEST_FOLDER}

RUST_LOG=${RUST_LOG} ${RUST_APP} \
  --jwk-auth-signature-secret-path=${JWK_AUTH_SIGNATURE_SECRET_PATH} \
  --iroh-signature-secret-path=${IROH_SIGNATURE_SECRET_PATH}
