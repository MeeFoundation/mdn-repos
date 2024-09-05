use crate::willow::utils::display_path;
use futures::StreamExt;
use iroh_willow::{proto::data_model::Entry, session::intents::IntentHandle};

/// Useful for debugging and testing
pub async fn progress_session_intents(
    mut sync_event_stream: IntentHandle,
    additional_info: &str,
) -> IntentHandle {
    while let Some(ev) = sync_event_stream.next().await {
        match ev {
            iroh_willow::session::intents::EventKind::CapabilityIntersection {
                area,
                namespace,
            } => {
                log::info!(
                    "{additional_info}CapabilityIntersection: {namespace} {}",
                    display_path(area.path())
                );
            }
            iroh_willow::session::intents::EventKind::InterestIntersection { area, namespace } => {
                log::info!(
                    "{additional_info}InterestIntersection: {namespace} {}",
                    display_path(area.area.path())
                );
            }
            iroh_willow::session::intents::EventKind::Reconciled { area, namespace } => {
                log::info!(
                    "{additional_info}Reconciled: {namespace} {}",
                    display_path(area.area.path())
                );
            }
            iroh_willow::session::intents::EventKind::ReconciledAll => {
                log::info!("{additional_info}Reconciled all");
            }
            iroh_willow::session::intents::EventKind::Abort { error } => {
                log::error!("{additional_info}Abort session intent: {error:#}");
            }
        };
    }

    log::info!("No more session intent events.");

    sync_event_stream
}

pub fn display_entry(entry: &Entry) -> (String, String, String) {
    (
        display_path(entry.path()),
        format!("{:?}", entry.namespace_id()),
        format!("{:?}", entry.subspace_id()),
    )
}

pub fn display_entry_list<'a>(entries: impl Iterator<Item = &'a Entry>) -> String {
    format!("{:#?}", entries.map(display_entry).collect::<Vec<_>>())
}
