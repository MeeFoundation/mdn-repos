use crate::ast::*;
// Implement the Visitor pattern to execute the AST
use super::*;
use regex::Regex;
use std::collections::HashMap;

pub trait Visitor {
    fn visit_query(&mut self, query: &Query) -> Result<MeeValue, EvalError>;
    fn visit_query_body(&mut self, body: &QueryBody) -> Result<MeeValue, EvalError>;
    fn visit_delete_stmt(&mut self, delete_stmt: &DeleteStmt) -> Result<(), EvalError>;
    fn visit_iterator_stmt(
        &mut self,
        iterator_stmt: &IteratorStmt,
    ) -> Result<Vec<MeeValue>, EvalError>;
    fn visit_bool_expression(&mut self, bool_expr: &BoolExpression) -> Result<bool, EvalError>;
    fn visit_comparator(
        &mut self,
        comparator: &Comparator,
        value: &MeeValue,
    ) -> Result<bool, EvalError>;
    fn visit_source(&mut self, source: &Source) -> Result<Vec<MeeValue>, EvalError>;
    fn visit_expression(&mut self, expr: &Expression) -> Result<MeeValue, EvalError>;
    fn visit_mee_value(&mut self, value: &MeeValue) -> Result<MeeValue, EvalError>;
}

#[derive(Debug)]
pub enum EvalError {
    InvalidType(String),
    InvalidPath(MeeValue, Path),
    PathNotFound(Path),
    Other(String),
}

#[derive(Default)]
pub struct Evaluator {
    pub data: MeeValue,
    pub variables: HashMap<String, MeeValue>,
}

impl Evaluator {
    pub fn new(data: MeeValue) -> Self {
        Evaluator {
            data,
            variables: HashMap::new(),
        }
    }

    fn resolve_path(&self, value: &MeeValue, path: &Path) -> Result<MeeValue, EvalError> {
        let mut current_value = value.clone();
        for key in &path.0 {
            match current_value {
                MeeValue::Object(ref map) => {
                    if let Some(v) = map.get(key) {
                        current_value = v.clone();
                    } else {
                        return Err(EvalError::PathNotFound(path.clone()));
                    }
                }
                _ => {
                    return Err(EvalError::InvalidPath(current_value, path.clone()));
                }
            }
        }
        Ok(current_value)
    }

    fn update_path(&mut self, path: &Path, value: MeeValue) -> Result<(), EvalError> {
        let mut current_value = &mut self.data;
        let len = path.0.len();
        for key in &path.0[..len - 1] {
            match current_value {
                MeeValue::Object(ref mut map) => {
                    current_value = map.entry(key.clone()).or_insert(MeeValue::Null);
                }
                _ => {
                    return Err(EvalError::InvalidPath(current_value.clone(), path.clone()));
                }
            }
        }
        if let MeeValue::Object(ref mut map) = current_value {
            map.insert(path.0[len - 1].clone(), value);
            Ok(())
        } else {
            Err(EvalError::InvalidPath(current_value.clone(), path.clone()))
        }
    }

    fn delete_path(&mut self, path: &Path) -> Result<(), EvalError> {
        let mut current_value = &mut self.data;
        let len = path.0.len();
        for key in &path.0[..len - 1] {
            match current_value {
                MeeValue::Object(ref mut map) => {
                    if map.contains_key(key) {
                        current_value = map.get_mut(key).unwrap();
                    } else {
                        return Err(EvalError::PathNotFound(path.clone()));
                    }
                }
                _ => {
                    return Err(EvalError::InvalidPath(current_value.clone(), path.clone()));
                }
            }
        }
        if let MeeValue::Object(ref mut map) = current_value {
            map.remove(&path.0[len - 1]);
            Ok(())
        } else {
            Err(EvalError::InvalidPath(current_value.clone(), path.clone()))
        }
    }
}

impl Visitor for Evaluator {
    fn visit_query(&mut self, query: &Query) -> Result<MeeValue, EvalError> {
        match query {
            Query::ArrayQuery { body } => self.visit_query_body(body),
            Query::ElementQuery { body } => {
                let result = self.visit_query_body(body)?;
                match result {
                    MeeValue::Array(mut arr) => {
                        if let Some(first) = arr.pop() {
                            Ok(first)
                        } else {
                            Ok(MeeValue::Null)
                        }
                    }
                    _ => Ok(result),
                }
            }
        }
    }

    fn visit_query_body(&mut self, body: &QueryBody) -> Result<MeeValue, EvalError> {
        // Evaluate main iterator
        let items = self.visit_iterator_stmt(&body.main_iterator)?;

        // Apply updates and deletes
        for item in items.iter() {
            // Set iterator variable
            self.variables
                .insert(body.main_iterator.item.clone(), item.clone());

            // Apply embedded iterators
            for embedded_iterator in &body.embedded_iterators {
                self.visit_iterator_stmt(embedded_iterator)?;
            }

            // Apply updates
            for (path, expr) in &body.updates {
                let value = self.visit_expression(expr)?;
                self.update_path(path, value)?;
            }

            // Apply deletes
            self.visit_delete_stmt(&body.deletes)?;
        }

        // Collect result
        if let Some(result_expr) = &body.result {
            self.visit_mee_value(result_expr)
        } else {
            Ok(MeeValue::Array(items))
        }
    }

    fn visit_delete_stmt(&mut self, delete_stmt: &DeleteStmt) -> Result<(), EvalError> {
        match delete_stmt {
            DeleteStmt::Paths(paths) => {
                for path in paths {
                    self.delete_path(path)?;
                }
                Ok(())
            }
            DeleteStmt::All => {
                if let MeeValue::Object(ref mut map) = self.data {
                    map.clear();
                    Ok(())
                } else {
                    Err(EvalError::InvalidType("Expected Object".to_string()))
                }
            }
            DeleteStmt::None => Ok(()),
        }
    }

    fn visit_iterator_stmt(
        &mut self,
        iterator_stmt: &IteratorStmt,
    ) -> Result<Vec<MeeValue>, EvalError> {
        let source_items = self.visit_source(&iterator_stmt.source)?;

        // Apply filter
        let mut filtered_items = Vec::new();
        for item in source_items {
            // Set iterator variable
            self.variables
                .insert(iterator_stmt.item.clone(), item.clone());

            // Evaluate assignments
            for (var, expr) in &iterator_stmt.assignments {
                let value = self.visit_expression(expr)?;
                self.variables.insert(var.clone(), value);
            }

            let pass = if let Some(filter_expr) = &iterator_stmt.filter {
                self.visit_bool_expression(filter_expr)?
            } else {
                true
            };

            if pass {
                filtered_items.push(item.clone());
            }
        }

        // Apply offset and limit
        let offset = iterator_stmt.offset.unwrap_or(0);
        let limit = iterator_stmt.limit.unwrap_or(filtered_items.len());
        let selected_items = filtered_items
            .into_iter()
            .skip(offset)
            .take(limit)
            .collect();

        Ok(selected_items)
    }

    fn visit_bool_expression(&mut self, bool_expr: &BoolExpression) -> Result<bool, EvalError> {
        match bool_expr {
            BoolExpression::Comparison { val, comparator } => {
                let val_value = self.visit_mee_value(val)?;
                self.visit_comparator(comparator, &val_value)
            }
            BoolExpression::And(exprs) => {
                for expr in exprs {
                    if !self.visit_bool_expression(expr)? {
                        return Ok(false);
                    }
                }
                Ok(true)
            }
            BoolExpression::Or(exprs) => {
                for expr in exprs {
                    if self.visit_bool_expression(expr)? {
                        return Ok(true);
                    }
                }
                Ok(false)
            }
            BoolExpression::Not(expr) => {
                let result = self.visit_bool_expression(expr)?;
                Ok(!result)
            }
            BoolExpression::BoolPath(path) => {
                let value = self.resolve_path(&self.data, path)?;
                match value {
                    MeeValue::Bool(b) => Ok(b),
                    _ => Err(EvalError::InvalidType("Expected Bool".to_string())),
                }
            }
            BoolExpression::True => Ok(true),
            BoolExpression::False => Ok(false),
        }
    }

    fn visit_comparator(
        &mut self,
        comparator: &Comparator,
        value: &MeeValue,
    ) -> Result<bool, EvalError> {
        match comparator {
            Comparator::Eq(expr) => {
                let expr_value = self.visit_expression(expr)?;
                Ok(value == &expr_value)
            }
            Comparator::Ne(expr) => {
                let expr_value = self.visit_expression(expr)?;
                Ok(value != &expr_value)
            }
            Comparator::Gt(expr) => {
                let expr_value = self.visit_expression(expr)?;
                match (value, &expr_value) {
                    (MeeValue::Number(a), MeeValue::Number(b)) => Ok(a > b),
                    _ => Err(EvalError::InvalidType("Expected Number".to_string())),
                }
            }
            Comparator::Lt(expr) => {
                let expr_value = self.visit_expression(expr)?;
                match (value, &expr_value) {
                    (MeeValue::Number(a), MeeValue::Number(b)) => Ok(a < b),
                    _ => Err(EvalError::InvalidType("Expected Number".to_string())),
                }
            }
            Comparator::Ge(expr) => {
                let expr_value = self.visit_expression(expr)?;
                match (value, &expr_value) {
                    (MeeValue::Number(a), MeeValue::Number(b)) => Ok(a >= b),
                    _ => Err(EvalError::InvalidType("Expected Number".to_string())),
                }
            }
            Comparator::Le(expr) => {
                let expr_value = self.visit_expression(expr)?;
                match (value, &expr_value) {
                    (MeeValue::Number(a), MeeValue::Number(b)) => Ok(a <= b),
                    _ => Err(EvalError::InvalidType("Expected Number".to_string())),
                }
            }
            Comparator::Matches(expr) => {
                let expr_value = self.visit_expression(expr)?;
                match (&value, &expr_value) {
                    (MeeValue::String(s), MeeValue::String(pattern)) => {
                        let pattern =
                            Regex::new(pattern).map_err(|e| EvalError::Other(e.to_string()))?;
                        Ok(pattern.is_match(s))
                    }
                    _ => Err(EvalError::InvalidType("Expected String".to_string())),
                }
            }
            Comparator::Exists => Ok(value != &MeeValue::Null),
        }
    }

    fn visit_source(&mut self, source: &Source) -> Result<Vec<MeeValue>, EvalError> {
        match source {
            Source::PathSource(path) => {
                let value = self.resolve_path(&self.data, path)?;
                match value {
                    MeeValue::Array(items) => Ok(items),
                    _ => Ok(vec![value]),
                }
            }
            Source::ArraySource(array) => Ok(array.clone()),
        }
    }

    fn visit_expression(&mut self, expr: &Expression) -> Result<MeeValue, EvalError> {
        match expr {
            Expression::Value(val) => self.visit_mee_value(val),
            Expression::Query(query) => self.visit_query(query),
            Expression::BoolExpression(bool_expr) => {
                let result = self.visit_bool_expression(bool_expr)?;
                Ok(MeeValue::Bool(result))
            }
        }
    }

    fn visit_mee_value(&mut self, value: &MeeValue) -> Result<MeeValue, EvalError> {
        match value {
            MeeValue::Path(path) => self.resolve_path(&self.data, path),
            MeeValue::Object(map) => {
                let mut result = HashMap::new();
                for (k, v) in map {
                    let val = self.visit_mee_value(v)?;
                    result.insert(k.clone(), val);
                }
                Ok(MeeValue::Object(result))
            }
            MeeValue::Array(items) => {
                let mut result = Vec::new();
                for item in items {
                    let val = self.visit_mee_value(item)?;
                    result.push(val);
                }
                Ok(MeeValue::Array(result))
            }
            MeeValue::String(s) => Ok(MeeValue::String(s.clone())),
            MeeValue::Number(n) => Ok(MeeValue::Number(*n)),
            MeeValue::Bool(b) => Ok(MeeValue::Bool(*b)),
            MeeValue::Null => Ok(MeeValue::Null),
        }
    }
}
