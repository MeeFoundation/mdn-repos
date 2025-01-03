use serde_json::value;

use super::Context;
use crate::ast::*;
use crate::error::*;
use std::any::Any;

impl<T> MeeNode<T> {
    pub fn new(value: T, start: usize, end: usize) -> Self {
        Self {
            value,
            position: Position(start, end),
            expected_type: None,
        }
    }

    pub fn with_type(self, expected_type: NodeTypes) -> Self {
        Self {
            expected_type: Some(expected_type),
            ..self
        }
    }

    pub fn with_optional_type(self, expected_type: Option<NodeTypes>) -> Self {
        Self {
            expected_type,
            ..self
        }
    }

    pub fn map<F, U>(&self, f: F) -> MeeNode<U>
    where
        F: FnOnce(&T) -> U,
    {
        MeeNode::new(f(&self.value), self.position.0, self.position.1)
    }

    pub fn check_type(&self, expected_type: &NodeTypes, source_code: &str) -> Result<&Self> {
        if let Some(inner_type) = self.expected_type.as_ref() {
            match (inner_type, expected_type) {
                (NodeTypes::AbsolutePath, NodeTypes::AbsolutePath) => Ok(self),
                (NodeTypes::AbsolutePath, _) => Ok(self),
                (t, u) if t == u => Ok(self),
                _ => {
                    let reason = format!(
                        "Expected type: {:?}, found: {:?}",
                        expected_type, inner_type
                    );
                    Err(Error::validation_error(
                        self.position.clone(),
                        source_code,
                        reason,
                    ))
                }
            }
        } else {
            Ok(self)
        }
    }

    pub fn check_optional_type(
        &self,
        expected_type: &Option<NodeTypes>,
        source_code: &str,
    ) -> Result<&Self> {
        if let Some(inner_type) = expected_type.as_ref() {
            self.check_type(inner_type, source_code)
        } else {
            Ok(self)
        }
    }
}

pub trait GetUsingPaths {
    fn using_paths(&self, ctx: &Context) -> Vec<Path>;
}

impl<T> GetUsingPaths for MeeNode<T>
where
    T: GetUsingPaths + Any,
{
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        self.value.using_paths(ctx)
    }
}

impl GetUsingPaths for Path {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        println!("path: {:?}, ctx: {:?}", self, ctx.keys());
        vec![self.clone()]
    }
}

impl GetUsingPaths for Expression {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        match self {
            Expression::Query(q) => q.using_paths(ctx),
            Expression::BoolExpression(b) => b.using_paths(ctx),
            Expression::Link(l) => l.using_paths(ctx),
            Expression::Object(o) => o.values().flat_map(|e| e.using_paths(ctx)).collect(),
            Expression::Array(a) => a.iter().flat_map(|e| e.using_paths(ctx)).collect(),
            _ => vec![],
        }
    }
}

impl GetUsingPaths for Query {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        let mut res = Vec::new();
        if let Some(ref r) = self.result {
            res.extend(r.using_paths(ctx));
        }
        res.extend(self.main_iterator.using_paths(ctx));
        res.extend(self.statements.iter().flat_map(|s| s.using_paths(ctx)));
        res
    }
}

impl Query {
    pub fn is_read_only(&self) -> bool {
        self.statements.iter().any(|s| {
            matches!(
                s.value,
                Statement::Update(_)
                    | Statement::Delete(_)
                    | Statement::AppendOne(_)
                    | Statement::AppendMany(_)
            )
        })
    }
}

impl GetUsingPaths for Statement {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        match self {
            Statement::Iterator(i) => i.using_paths(ctx),
            Statement::Assignment((_, e)) => e.using_paths(ctx),
            Statement::Update((_, e)) => e.using_paths(ctx),
            Statement::AppendOne((_, e)) => e.using_paths(ctx),
            Statement::AppendMany((_, e)) => e.using_paths(ctx),
            Statement::Filter(b) => b.using_paths(ctx),
            _ => vec![],
        }
    }
}

impl GetUsingPaths for IteratorStmt {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        match &self.source.value {
            Source::Users => vec![],
            Source::EmbeddedCollection { prop, parent } => parent
                .using_paths(ctx)
                .into_iter()
                .map(|p| p.combine(&Path::new("*")).combine(prop))
                .collect(),
            Source::Property { prop, parent } => parent
                .using_paths(ctx)
                .into_iter()
                .map(|p| p.combine(prop))
                .collect(),
            Source::Link { prop, parent } => parent
                .using_paths(ctx)
                .into_iter()
                .map(|p| p.combine(prop))
                .collect(),
            Source::ArraySource(e) => e.iter().flat_map(|e| e.using_paths(ctx)).collect(),
        }
    }
}

impl GetUsingPaths for BoolExpression {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        match self {
            BoolExpression::Expression(e) => e.using_paths(ctx),
            BoolExpression::Comparison { val, comparator } => {
                let mut res = val.using_paths(ctx);
                res.extend(comparator.using_paths(ctx));
                res
            }
            _ => vec![],
        }
    }
}

impl GetUsingPaths for Comparator {
    fn using_paths(&self, ctx: &Context) -> Vec<Path> {
        match self {
            Comparator::Eq(e)
            | Comparator::Ne(e)
            | Comparator::Gt(e)
            | Comparator::Lt(e)
            | Comparator::Ge(e)
            | Comparator::Le(e)
            | Comparator::Matches(e)
            | Comparator::After(e)
            | Comparator::Before(e)
            | Comparator::Contains(e) => e.using_paths(ctx),
            Comparator::Between(e1, e2) => {
                let mut res = e1.using_paths(ctx);
                res.extend(e2.using_paths(ctx));
                res
            }
            _ => vec![],
        }
    }
}
