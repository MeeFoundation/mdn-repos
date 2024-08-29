use crate::error::MeeDataSyncResult;
use bytes::Bytes;
use futures::StreamExt;
use iroh_willow::{
    proto::data_model::{Component, Path},
    session::intents::IntentHandle,
};

pub fn path_from_bytes_slice(bytes_slice: &[&[u8]]) -> MeeDataSyncResult<Path> {
    Ok(Path::new_from_slice(
        &bytes_slice
            .iter()
            .filter_map(|c| Component::new(c))
            .collect::<Vec<_>>(),
    )?)
}

pub fn display_path(path: &Path) -> String {
    let p = path
        .components()
        .into_iter()
        .map(|c| String::from_utf8(c.to_vec()).unwrap_or("invalid-utf8-string".to_string()))
        .collect::<Vec<_>>()
        .join("/");

    if p.is_empty() {
        "*".to_string()
    } else {
        p
    }
}

pub fn empty_entry_payload() -> [u8; 1] {
    [0]
}

pub fn is_empty_entry_payload(payload: &Bytes) -> bool {
    payload.is_empty() || **payload == empty_entry_payload()
}

/// TODO find a better way to suffix path component
pub fn path_suffix(path: &Path, i: usize) -> MeeDataSyncResult<Path> {
    let path = path.suffix_components(i).collect::<Vec<_>>();
    let path = path.iter().map(|c| c.as_ref()).collect::<Vec<_>>();
    let path = path_from_bytes_slice(path.as_slice())?;

    Ok(path)
}

/// Useful for debugging and testing
pub async fn progress_session_intents(mut sync_event_stream: IntentHandle) -> IntentHandle {
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

    log::info!("No more session intent events.");

    sync_event_stream
}
