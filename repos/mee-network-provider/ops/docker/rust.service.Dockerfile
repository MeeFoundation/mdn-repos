FROM rust:1.81 AS builder

ARG RUST_APP=
ARG SECRETS_KEYGEN=

WORKDIR /usr/local/src/app
ADD mee-network-provider/services mee-network-provider/services
ADD mee-network-core/lib mee-network-core/lib
ADD mee-utils/lib mee-utils/lib

WORKDIR /usr/local/src/app/mee-network-provider/services
RUN cargo install --bin=${SECRETS_KEYGEN} --path ${SECRETS_KEYGEN} && \
    cargo install --bin=${RUST_APP} --path ${RUST_APP}

FROM debian:stable-slim

ARG RUST_APP=${RUST_APP}
ARG SECRETS_KEYGEN=${SECRETS_KEYGEN}
ENV RUST_APP=${RUST_APP}
ENV SECRETS_KEYGEN=${SECRETS_KEYGEN}

COPY --from=builder /usr/local/cargo/bin/${RUST_APP} /usr/local/bin/${RUST_APP}
COPY --from=builder /usr/local/cargo/bin/${SECRETS_KEYGEN} /usr/local/bin/${SECRETS_KEYGEN}
COPY mee-network-provider/ops/docker/entrypoint.sh entrypoint.sh
COPY mee-network-provider/services/${RUST_APP}/.env.example .env

CMD ["./entrypoint.sh"]
