use axum::{routing::get, Router};

pub fn health_check_router<S>() -> Router<S>
where
    S: Sync + Send + Clone + 'static,
{
    Router::new().route("/health", get(|| async { "OK" }))
}
