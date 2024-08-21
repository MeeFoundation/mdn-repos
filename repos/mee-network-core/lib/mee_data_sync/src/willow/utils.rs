use crate::error::MeeDataSyncResult;
use bytes::Bytes;
use iroh_willow::proto::data_model::{Component, Path};

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
        .map(|c| String::from_utf8(c.to_vec()).unwrap())
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
