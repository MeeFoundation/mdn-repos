use crate::error::MeeDataSyncResult;
use bytes::Bytes;
use iroh_willow::proto::{
    data_model::{Component, Path},
    grouping::Range,
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

pub fn path_range_exact(path: Path) -> MeeDataSyncResult<Option<Range<Path>>> {
    let end_path = path.append(Component::new_empty())?;

    Ok(Range::new_closed(path, end_path))
}

#[test]
fn path_exact_range_test() {
    let path = path_from_bytes_slice(&[b"path", b"to"]).unwrap();
    let wrong_paths = [
        path_from_bytes_slice(&[b"path"]).unwrap(),
        path_from_bytes_slice(&[b"path", b"t"]).unwrap(),
        path_from_bytes_slice(&[b"path", b"tu"]).unwrap(),
        path_from_bytes_slice(&[b"path", b"too"]).unwrap(),
    ];

    let range = path_range_exact(path.clone()).unwrap().unwrap();

    assert!(range.includes(&path));
    assert!(wrong_paths.iter().all(|p| !range.includes(p)));
}
