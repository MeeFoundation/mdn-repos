use crate::error::MeeDataSyncResult;
use iroh_willow::proto::{
    data_model::{Path, PathExt},
    keys::UserId,
};

pub const CAPABILITY_LIST_PATH_PREFIX: &str = "capability";
pub const REVOCATION_REQUEST_PATH_PREFIX: &str = "revocation_request";
pub const REVOCATION_DONE_PATH_PREFIX: &str = "revocation_done";

pub fn revocation_done_record_path(user_id: UserId, cap_id: &str) -> MeeDataSyncResult<Path> {
    Ok(Path::from_bytes(&[
        REVOCATION_DONE_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
        cap_id.as_bytes(),
    ])?)
}

pub fn cap_list_record_path(user_id: UserId, cap_id: &str) -> MeeDataSyncResult<Path> {
    Ok(Path::from_bytes(&[
        CAPABILITY_LIST_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
        cap_id.as_bytes(),
    ])?)
}

pub fn revocation_request_record_path(user_id: UserId, cap_id: &str) -> MeeDataSyncResult<Path> {
    Ok(Path::from_bytes(&[
        REVOCATION_REQUEST_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
        cap_id.as_bytes(),
    ])?)
}

pub fn revocation_request_record_path_prefix(user_id: UserId) -> MeeDataSyncResult<Path> {
    Ok(Path::from_bytes(&[
        REVOCATION_REQUEST_PATH_PREFIX.as_bytes(),
        user_id.to_string().as_bytes(),
    ])?)
}
