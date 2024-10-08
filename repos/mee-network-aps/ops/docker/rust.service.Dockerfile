FROM rust:1.81 AS builder

ARG RUST_APP=

WORKDIR /usr/local/src/app
ADD mee-network-aps/services mee-network-aps/services
ADD mee-network-core/lib mee-network-core/lib
ADD mee-utils/lib mee-utils/lib

WORKDIR /usr/local/src/app/mee-network-aps/services
RUN cargo install --bin=${RUST_APP} --path ${RUST_APP}

FROM debian:stable-slim

ARG RUST_APP=${RUST_APP}
ENV RUST_APP=${RUST_APP}

COPY --from=builder /usr/local/cargo/bin/${RUST_APP} /usr/local/bin/${RUST_APP}
COPY mee-network-aps/ops/docker/entrypoint.sh entrypoint.sh
COPY mee-network-aps/services/${RUST_APP}/.env.example .env

CMD ["./entrypoint.sh"]
