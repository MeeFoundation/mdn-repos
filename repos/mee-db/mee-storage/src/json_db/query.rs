#![allow(dead_code)]
#![allow(unused)]

use serde_json::Value;

pub(crate) enum OrderingType {
    Ask,
    Desc,
}

pub(crate) struct KeyOrdering {
    fields: Vec<(String, OrderingType)>,
}

struct Query {
    value_filter: Option<Box<dyn Fn(&Value) -> bool + Sync + Send>>,
    limit: Option<usize>,
    offset: usize,
}

pub(crate) struct SelectQuery {
    key_filter: Option<Box<dyn Fn(&str) -> bool + Sync + Send>>,
    ordering: KeyOrdering,
    query: Query,
}

pub(crate) struct UpdateQuery {
    update: Option<Box<dyn Fn(&mut Value) + Sync + Send>>,
    query: Query,
}

pub(crate) struct DeleteQuery {
    key_filter: Option<Box<dyn Fn(&str) -> bool + Sync + Send>>,
    query: Query,
}

impl Query {
    pub fn new() -> Self {
        Self {
            value_filter: None,
            limit: None,
            offset: 0,
        }
    }

    pub fn filter<F>(mut self, f: F) -> Self
    where
        F: Fn(&Value) -> bool + 'static + Sync + Send,
    {
        self.value_filter = Some(Box::new(f));
        self
    }

    pub fn limit(mut self, limit: usize) -> Self {
        self.limit = Some(limit);
        self
    }

    pub fn offset(mut self, offset: usize) -> Self {
        self.offset = offset;
        self
    }

    pub fn select(self) -> SelectQuery {
        SelectQuery {
            key_filter: None,
            ordering: KeyOrdering { fields: vec![] },
            query: self,
        }
    }
}

impl SelectQuery {
    pub fn fields<F>(mut self, fields: Vec<String>) -> Self {
        self.key_filter = Some(Box::new(move |key| fields.contains(&key.to_string())));
        self
    }

    pub fn order_by<F>(mut self, field: String, ord: OrderingType) -> Self {
        self.ordering.fields.push((field, ord));
        self
    }
}

impl UpdateQuery {
    pub fn update<F>(mut self, f: F) -> Self
    where
        F: Fn(&mut Value) + 'static + Sync + Send,
    {
        self.update = Some(Box::new(f));
        self
    }
}

impl DeleteQuery {
    pub fn fields<F>(mut self, f: F) -> Self
    where
        F: Fn(&str) -> bool + 'static + Sync + Send,
    {
        self.key_filter = Some(Box::new(f));
        self
    }
}

pub(crate) trait QueryDetails {
    fn field_filter(key: &str) -> bool;
    fn object_filter(value: &Value) -> bool;
}

pub(crate) enum QueryTypes {
    Select(SelectQuery),
    Update(UpdateQuery),
    Delete(DeleteQuery),
}

impl QueryTypes {}
