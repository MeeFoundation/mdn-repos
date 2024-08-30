use super::traits::delegation::REVOCATION_REQUEST_PATH_PREFIX;
use crate::{
    error::MeeDataSyncResult,
    willow::{
        peer::data_manager::WillowDataManager,
        utils::{display_path, is_empty_entry_payload, path_suffix},
    },
};
use futures::{StreamExt, TryStreamExt};
use iroh_willow::proto::{
    data_model::{Entry, Path, PathExt},
    keys::UserId,
};
use std::str::FromStr;

// TODO check revocation list record origin validity
pub fn find_revocation_cap_pairs(
    revocation_list: Vec<Entry>,
) -> MeeDataSyncResult<Vec<(UserId, Entry, Entry)>> {
    let mut res = vec![];

    let pref = Path::from_bytes(&[REVOCATION_REQUEST_PATH_PREFIX.as_bytes()])?;

    let (request_list, readiness_list): (Vec<_>, Vec<_>) = revocation_list
        .into_iter()
        .partition(|e| e.path().is_prefixed_by(&pref));

    for req in request_list {
        let common_path = path_suffix(req.path(), 1)?;

        let req_res = readiness_list.iter().find_map(|e| {
            let res = || {
                let path = path_suffix(e.path(), 1)?;
                let user_id = path.get_component(0);

                if let Some(user_id) = user_id {
                    let user = UserId::from_str(&String::from_utf8(user_id.to_vec())?)?;

                    if path == common_path {
                        return MeeDataSyncResult::Ok(Some((user, req.clone(), e.clone())));
                    }
                }

                MeeDataSyncResult::Ok(None)
            };

            match res() {
                Ok(v) => v,
                Err(e) => {
                    log::error!("Error looking for revocation list readiness entries: {e}");
                    None
                }
            }
        });

        if let Some(req_res) = req_res {
            res.push(req_res);
        }
    }

    Ok(res)
}

impl WillowDataManager {
    pub async fn map_payload<EntryElement, EntryFn, Payload, MapFn>(
        &self,
        entries: impl IntoIterator<Item = EntryElement>,
        entry_fn: EntryFn,
        map_fn: MapFn,
    ) -> MeeDataSyncResult<Vec<Payload>>
    where
        MapFn: Fn(EntryElement, &bytes::Bytes) -> MeeDataSyncResult<Payload>,
        EntryFn: Fn(&EntryElement) -> Entry,
    {
        let res = futures::stream::iter(entries)
            .map(MeeDataSyncResult::Ok)
            .try_filter_map(|e| async {
                if let Some(p) = self.read_entry_payload(entry_fn(&e)).await? {
                    if !is_empty_entry_payload(&p) {
                        return MeeDataSyncResult::Ok(Some(map_fn(e, &p)?));
                    }
                }

                MeeDataSyncResult::Ok(None)
            })
            .try_collect()
            .await?;

        Ok(res)
    }
    pub async fn is_entry_list_payload_empty(
        &self,
        revocation_list: &Vec<Entry>,
    ) -> MeeDataSyncResult<bool> {
        let mut payloads = vec![];

        for e in revocation_list.iter() {
            let p = self.read_entry_payload(e.clone()).await?;
            if let Some(p) = p {
                payloads.push((display_path(e.path()), p));
            }
        }

        let pred = payloads.iter().all(|(_, p)| is_empty_entry_payload(p));

        Ok(pred)
    }
}

#[macro_export]
macro_rules! json_codec {
    ($struct_name: ident) => {
        impl $struct_name {
            pub fn encode(&self) -> MeeDataSyncResult<Vec<u8>> {
                Ok(serde_json::to_vec(self)?)
            }
            pub fn decode(bytes: &[u8]) -> MeeDataSyncResult<Self> {
                Ok(serde_json::from_slice(bytes)?)
            }
        }
    };
}
