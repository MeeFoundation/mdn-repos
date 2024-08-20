#![allow(unused)]
use crate::{binary_kv_store::PATH_SEPARATOR, error::Result};
use regex::Regex;

pub enum FieldFilter {
    All,
    Patters { regexes: Vec<Regex>, with_id: bool },
}

pub const ANY_PATH_SEGMENT: &str = "*";
pub const ANY_PATH_SEGMENT_REPLACEMENT: &str = "[^{PATH_SEPARATOR}]*";

impl FieldFilter {
    pub fn try_from_patterns(patterns: Vec<String>, with_id: bool) -> Result<Self> {
        let mut regexes = Vec::with_capacity(patterns.len());
        for pattern in patterns {
            let r = pattern.replace(ANY_PATH_SEGMENT, ANY_PATH_SEGMENT_REPLACEMENT);
            regexes.push(Regex::new(&r)?);
        }
        Ok(FieldFilter::Patters { regexes, with_id })
    }

    pub fn matches(&self, key: &str) -> bool {
        match self {
            FieldFilter::All => true,
            FieldFilter::Patters { regexes, .. } => {
                for pattern in regexes {
                    if pattern.is_match(key) {
                        return true;
                    }
                }
                false
            }
        }
    }

    pub fn add_id(&self) -> bool {
        match self {
            FieldFilter::All => true,
            FieldFilter::Patters { with_id, .. } => *with_id,
        }
    }
}
