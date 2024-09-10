use super::Result;
use crate::json_utils::ID_PROPERTY;
use regex::Regex;
use std::fmt::Display;

#[derive(Debug, Clone, Default)]
pub enum FieldFilter {
    #[default]
    All,
    Patters {
        regexes: Vec<Regex>,
        with_id: bool,
    },
}

impl Display for FieldFilter {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            FieldFilter::All => write!(f, "All"),
            FieldFilter::Patters { regexes, with_id } => {
                write!(f, "Patterns: [")?;
                for r in regexes {
                    write!(f, "{}, ", r.as_str())?;
                }
                write!(f, "], with_id: {with_id}",)
            }
        }
    }
}

pub const ANY_PATH_SEGMENT: &str = "*";

impl FieldFilter {
    pub fn try_from_patterns(patterns: Vec<String>) -> Result<Self> {
        let mut regexes = Vec::with_capacity(patterns.len());
        let mut with_id = false;
        for pattern in patterns {
            if pattern == ID_PROPERTY {
                with_id = true;
            } else {
                let r = pattern.replace(ANY_PATH_SEGMENT, "\\w*");
                regexes.push(Regex::new(&r)?);
            }
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
