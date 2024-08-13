use crate::error::MeeDataSyncResult;
use iroh_willow::proto::data_model::{Component, Path};

pub fn path_from_bytes_slice(bytes_slice: &[&[u8]]) -> MeeDataSyncResult<Path> {
    Ok(Path::new_from_slice(
        &bytes_slice
            .iter()
            .filter_map(|c| Component::new(c))
            .collect::<Vec<_>>(),
    )?)
}
