pub mod ast;
pub mod error;
pub mod parser;
pub mod query_executor;

use std::collections::HashMap;

pub mod execution;

use execution::query_executor;
use mee_storage::json_kv_store;
