#![allow(unused_imports)]
mod _test_support;
mod condition;
mod derive_clause;
mod expression;
mod query;
mod select_clause;
mod where_clause;

pub(crate) use _test_support::*;
pub use condition::*;
pub use expression::*;
pub use query::*;
pub use select_clause::*;
pub use where_clause::*;

pub const KEY_WORD_PREFIX: char = '$';

fn is_false(b: &bool) -> bool {
    !b
}

#[cfg(test)]
pub(crate) mod test_support {
    use super::*;
    use serde_json::Value;

    pub fn expr(v: Value) -> Expr {
        serde_json::from_value(v).unwrap()
    }

    pub fn str_expr(str: &str) -> Expr {
        serde_json::from_str(str).unwrap()
    }

    pub fn cond(v: Value) -> CheckOperator {
        serde_json::from_value(v).unwrap()
    }
}
