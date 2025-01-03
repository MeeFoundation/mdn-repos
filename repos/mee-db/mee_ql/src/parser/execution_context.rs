use super::*;
use crate::ast::*;
use std::collections::HashMap;

pub struct ExecutionContext {
    parent: Option<Box<ExecutionContext>>,
    user_id: Option<String>,

    ctx: HashMap<String, MeeNode<Path>>,
}

enum ExecutionContext {
    User {
        id: Option<String>,
        ctx: HashMap<String, MeeNode<Expression>>,
    },
    Property {
        name: String,
        parent: Box<Path>,
    },
    CollectionPropertyItem {
        index: Option<usize>,
        parent: Box<Path>,
    },
    Expression(Expression),
}

impl ExecutionContext {
    pub fn new() -> Self {
        Self {
            parent: None,
            ctx: HashMap::new(),
        }
    }
}
