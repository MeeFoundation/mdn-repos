use crate::{error::MeeDataSyncResult, willow::utils::path_from_bytes_slice};
use iroh_willow::proto::{data_model::Path, keys::UserId};

pub const REVOCATION_LIST_PATH_PREFIX: &str = "revocation_request";
pub const REVOCATION_DONE_PATH_PREFIX: &str = "revocation_done";

pub fn revocation_done_record_path(user_id: UserId, cap_id: &str) -> MeeDataSyncResult<Path> {
    path_from_bytes_slice(&[
        REVOCATION_DONE_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
        cap_id.as_bytes(),
    ])
}

pub fn revocation_list_record_path(user_id: UserId, cap_id: &str) -> MeeDataSyncResult<Path> {
    path_from_bytes_slice(&[
        REVOCATION_LIST_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
        cap_id.as_bytes(),
    ])
}

pub fn revocation_list_record_path_prefix(user_id: UserId) -> MeeDataSyncResult<Path> {
    path_from_bytes_slice(&[
        REVOCATION_LIST_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
    ])
}
