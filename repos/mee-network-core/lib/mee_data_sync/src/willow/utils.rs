use crate::error::MeeDataSyncResult;
use bytes::Bytes;
use iroh_willow::proto::{
    data_model::{Component, Path, PathExt},
    grouping::Range,
};

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

pub fn deleted_entry_payload() -> [u8; 1] {
    [0]
}

pub fn empty_entry_payload() -> [u8; 2] {
    [0, 0]
}

pub fn is_deleted_entry_payload(payload: &Bytes) -> bool {
    **payload == deleted_entry_payload()
}

pub fn path_suffix(path: &Path, i: usize) -> MeeDataSyncResult<Path> {
    let path = path.suffix_components(i).collect::<Vec<_>>();
    let path = path.iter().map(|c| c.as_ref()).collect::<Vec<_>>();
    let path = Path::from_bytes(path.as_slice())?;

    Ok(path)
}

pub fn path_range_exact(path: Path) -> MeeDataSyncResult<Option<Range<Path>>> {
    let end_path = path.append(Component::new_empty())?;

    Ok(Range::new_closed(path, end_path))
}

#[test]
fn path_suffix_test() {
    let path_to = Path::from_bytes(&[b"path", b"to"]).unwrap();
    let to = Path::from_bytes(&[b"to"]).unwrap();

    assert_eq!(path_suffix(&path_to, 1).unwrap(), to);
}

#[test]
fn path_exact_range_test() {
    let path = Path::from_bytes(&[b"path", b"to"]).unwrap();
    let wrong_paths = [
        Path::from_bytes(&[b"path"]).unwrap(),
        Path::from_bytes(&[b"path", b"t"]).unwrap(),
        Path::from_bytes(&[b"path", b"tu"]).unwrap(),
        Path::from_bytes(&[b"path", b"too"]).unwrap(),
    ];

    let range = path_range_exact(path.clone()).unwrap().unwrap();

    assert!(range.includes(&path));
    assert!(wrong_paths.iter().all(|p| !range.includes(p)));
}
