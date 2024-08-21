use futures::StreamExt;
use iroh_willow::session::intents::IntentHandle;
use mee_data_sync::willow::utils::display_path;
use rand_chacha::{rand_core::SeedableRng, ChaCha12Rng};

pub fn create_rng(seed: &str) -> ChaCha12Rng {
    let seed = iroh_base::hash::Hash::new(seed);
    ChaCha12Rng::from_seed(*(seed.as_bytes()))
}

pub async fn progress_session_intents(mut sync_event_stream: IntentHandle) {
    while let Some(ev) = sync_event_stream.next().await {
        match ev {
            iroh_willow::session::intents::EventKind::CapabilityIntersection {
                area,
                namespace,
            } => {
                log::info!(
                    "CapabilityIntersection: {namespace} {}",
                    display_path(area.path())
                );
            }
            iroh_willow::session::intents::EventKind::InterestIntersection { area, namespace } => {
                log::info!(
                    "InterestIntersection: {namespace} {}",
                    display_path(area.area.path())
                );
            }
            iroh_willow::session::intents::EventKind::Reconciled { area, namespace } => {
                log::info!("Reconciled: {namespace} {}", display_path(area.area.path()));
            }
            iroh_willow::session::intents::EventKind::ReconciledAll => {
                log::info!("Reconciled all");
            }
            iroh_willow::session::intents::EventKind::Abort { error } => {
                log::error!("Abort session intent: {error:#}");
            }
        };
    }

    log::info!("No more session intent events. Trying again...");
}
