use crate::binary_kv_store::PATH_SEPARATOR;
use crate::json_kv_store::error::*;
use crate::json_utils::ID_PREFIX;

pub fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
}

pub fn property_key(id: &str, property_name: &str) -> String {
    format!("{}{PATH_SEPARATOR}{property_name}", object_key(id))
}

pub fn remove_object_id_prefix(key: String) -> String {
    if let Some(index) = key.find(PATH_SEPARATOR) {
        key[index + 1..].to_string()
    } else {
        key
    }
}

pub fn get_id(key: &str) -> Result<String> {
    if key.starts_with(ID_PREFIX) {
        let end = key.find(PATH_SEPARATOR).unwrap_or(key.len());
        Ok(key[ID_PREFIX.len()..end].to_string())
    } else {
        Err(Error::Store(format!("Invalid key format: {key}")))
    }
}

pub fn generate_id() -> String {
    uuid::Uuid::now_v7().to_string()
}
