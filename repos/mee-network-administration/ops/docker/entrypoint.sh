#!/usr/bin/env bash

RUST_LOG="${RUST_LOG:-info}"

set -e
echo "----------------------------------------"
env
echo "----------------------------------------"

echo "----------------------------------------"
echo "Running app server: \"$RUST_APP\""
echo "----------------------------------------"

RUST_LOG=${RUST_LOG} ${RUST_APP}
