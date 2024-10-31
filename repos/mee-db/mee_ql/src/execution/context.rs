use std::collections::HashMap;

use crate::ast::*;
use std::cell::RefCell;
use std::rc::Rc;

pub type ContextRef = Rc<RefCell<Context>>;

pub struct Context {
    variables: HashMap<String, Expression>,
    parent: Option<ContextRef>,
}

impl Context {
    pub fn new(parent: Option<ContextRef>) -> ContextRef {
        Rc::new(RefCell::new(Context {
            variables: HashMap::new(),
            parent,
        }))
    }

    pub fn get(&self, name: &str) -> Option<Expression> {
        match self.variables.get(name) {
            Some(value) => Some(value.clone()),
            _ => {
                if let Some(ref parent) = self.parent {
                    parent.borrow().get(name)
                } else {
                    None
                }
            }
        }
    }

    pub fn set(&mut self, name: String, value: Expression) {
        self.variables.insert(name, value);
    }
}
