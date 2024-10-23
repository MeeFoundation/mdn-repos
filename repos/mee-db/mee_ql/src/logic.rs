use crate::ast::*;
use mee_storage::json_utils::*;
use mee_storage::PATH_SEPARATOR;

use serde_json::json;
use serde_json::Number;
use serde_json::Value;
use std::collections::{HashMap, HashSet};
type Context = HashMap<String, Value>;

struct Settings {
    show_nulls: bool,
}

struct ContextCollector {
    context: Vec<Context>,
}

impl ContextCollector {
    fn new() -> Self {
        Self {
            context: Vec::new(),
        }
    }

    fn inter(&self, stmt: &IteratorStmt) -> Option<Value> {
        let mut context = HashMap::new();
        for (var, expr) in &stmt.assignments {
            let val = expr.map(value.clone(), context.clone());
            context.insert(var.clone(), val);
        }
        self.context.push(context);
    }
}

trait AstVisitor {
    fn pre_visit(&self, context: &mut Context) -> Option<Value>;
    fn post_visit(&self, context: &mut Context) -> Option<Value>;
}

struct LogicResult {
    filtered_paths: HashSet<String>,

    root_filter: Option<Value>,
    selected_fields: HashSet<String>,
}

trait LogicItem {
    fn filtered_paths(&self) -> HashSet<String>;
    fn enrich_context(&self, value: &Value, context: &mut Context) -> ();
    fn filter(&self, value: Value, context: &Context) -> Option<Value>; //может изменить объект при фильтрации вложенных коллекций
    fn map(&self, value: Value, context: &Context) -> Option<Value>;
}

/* Implementations */

impl LogicItem for Query {
    fn filtered_paths(&self) -> HashSet<String> {
        match self {
            Query::ArrayQuery { body } | Query::ElementQuery { body } => body.filtered_paths(),
        }
    }

    fn enrich_context(&self, value: &Value, context: &mut Context) -> () {
        match self {
            Query::ArrayQuery { body } | Query::ElementQuery { body } => {
                body.enrich_context(value, context)
            }
        }
    }

    fn filter(&self, value: Value, context: &Context) -> Option<Value> {
        match self {
            Query::ArrayQuery { body } | Query::ElementQuery { body } => {
                body.filter(value, context)
            }
        }
    }

    fn map(&self, value: Value, context: &Context) -> Option<Value> {
        match self {
            Query::ArrayQuery { body } | Query::ElementQuery { body } => body.map(value, context),
        }
    }
}

impl LogicItem for QueryBody {
    fn filtered_paths(&self) -> HashSet<String> {
        let mut fields = HashSet::new();
        if let Some(result) = &self.result {
            fields.extend(result.using_fields());
        }
        fields.extend(self.main_iterator.filtered_paths());
        for iterator in &self.embedded_iterators {
            fields.extend(iterator.using_fields());
        }
        for (path, expr) in &self.updates {
            fields.extend(path.using_fields());
            fields.extend(expr.using_fields());
        }
        fields.extend(self.deletes.filtered_paths());
        fields
    }

    fn enrich_context(&self, value: &Value, context: &mut Context) -> () {
        if let Some(result) = &self.result {
            result.enrich_context(value, context);
        }
        self.main_iterator.enrich_context(value, context);
        for iterator in &self.embedded_iterators {
            iterator.enrich_context(value, context);
        }
        for (_path, expr) in &self.updates {
            expr.enrich_context(value, context);
        }
        self.deletes.enrich_context(value, context);
    }

    fn filter(&self, value: Value, context: &Context) -> Option<Value> {
        self.main_iterator.filter(value, context)
    }

    fn map(&self, value: Value, context: &Context) -> Option<Value> {
        self.result
            .as_ref()
            .and_then(|result| result.map(value, context))
    }
}

impl LogicItem for DeleteStmt {
    fn filtered_paths(&self) -> HashSet<String> {
        match self {
            DeleteStmt::Paths(paths) => paths.iter().flat_map(|p| p.using_fields()).collect(),
            _ => HashSet::new(),
        }
    }

    fn enrich_context(&self, _: &Value, _: &mut Context) -> () {
        ()
    }

    fn filter(&self, value: Value, _: &Context) -> Option<Value> {
        Some(Value)
    }

    fn map(&self, _value: Value, _context: &Context) -> Option<Value> {
        None
    }
}

impl LogicItem for IteratorStmt {
    fn filtered_paths(&self) -> HashSet<String> {
        let mut fields = HashSet::new();
        fields.insert(self.item.clone());
        fields.extend(self.source.filtered_paths());
        for expr in self.assignments.values() {
            fields.extend(expr.using_fields());
        }
        if let Some(filter) = &self.filter {
            fields.extend(filter.using_fields());
        }
        fields
    }

    fn enrich_context(&self, value: Value, context: &mut Context) -> () {
        context.insert(self.item.clone(), value);
        for (var, expr) in &self.assignments {
            let val = expr.map(value.clone(), context.clone());
            context.insert(var.clone(), val);
        }
    }

    fn filter(&self, value: Value, context: &Context) -> Option<Value> {
        if let Some(filter_expr) = &self.filter {
            filter_expr.filter(value, context)
        } else {
            Some(value)
        }
    }

    fn map(&self, value: Value, context: &Context) -> Option<Value> {
        value
    }
}

impl LogicItem for BoolExpression {
    fn filtered_paths(&self) -> HashSet<String> {
        match self {
            BoolExpression::Comparison { val, comparator } => {
                let mut fields = val.filtered_paths();
                fields.extend(comparator.filtered_paths());
                fields
            }
            BoolExpression::And(exprs) | BoolExpression::Or(exprs) => {
                exprs.iter().flat_map(|e| e.using_fields()).collect()
            }
            BoolExpression::Not(expr) => expr.using_fields(),
            BoolExpression::BoolPath(path) => path.filtered_paths(),
            BoolExpression::True | BoolExpression::False => HashSet::new(),
        }
    }

    fn enrich_context(&self, value: Value, context: &mut Context) -> () {
        ()
    }

    fn filter(&self, value: Value, context: &Context) -> Option<Value> {
        match self {
            BoolExpression::Comparison { val, comparator } => {
                let left = val.map(value.clone(), context.clone());
                comparator.compare(left, value, context)
            }
            BoolExpression::And(exprs) => exprs
                .iter()
                .all(|e| e.filter(value.clone(), context.clone())),
            BoolExpression::Or(exprs) => exprs
                .iter()
                .any(|e| e.filter(value.clone(), context.clone())),
            BoolExpression::Not(expr) => !expr.filter(value, context),
            BoolExpression::BoolPath(path) => {
                // Retrieve the boolean value at the given path
                get_bool_at_path(&value, path)
            }
            BoolExpression::True => true,
            BoolExpression::False => false,
        }
    }

    fn map(&self, value: Value, _context: &Context) -> Option<Value> {
        Value::Bool(self.filter(value, _context)).into()
    }
}

impl LogicItem for Comparator {
    fn filtered_paths(&self) -> HashSet<String> {
        match self {
            Comparator::Exists => HashSet::new(),
            _ => {
                if let Some(expr) = self.get_expression() {
                    expr.using_fields()
                } else {
                    HashSet::new()
                }
            }
        }
    }

    fn enrich_context(&self, _value: Value, context: Context) -> Context {
        context
    }

    fn filter(&self, _value: Value, _context: Context) -> bool {
        true
    }

    fn map(&self, value: Value, context: Context) -> Value {
        Value::Bool(self.filter(value, context))
    }
}

impl Comparator {
    fn get_expression(&self) -> Option<&Expression> {
        match self {
            Comparator::Eq(expr)
            | Comparator::Ne(expr)
            | Comparator::Gt(expr)
            | Comparator::Lt(expr)
            | Comparator::Ge(expr)
            | Comparator::Le(expr)
            | Comparator::Matches(expr) => Some(expr),
            Comparator::Exists => None,
        }
    }

    fn compare(&self, left: Value, value: Value, context: Context) -> bool {
        let right = if let Some(expr) = self.get_expression() {
            expr.map(value, context)
        } else {
            Value::Null
        };
        match self {
            Comparator::Eq(_) => left == right,
            Comparator::Ne(_) => left != right,
            Comparator::Gt(_) => left > right,
            Comparator::Lt(_) => left < right,
            Comparator::Ge(_) => left >= right,
            Comparator::Le(_) => left <= right,
            Comparator::Matches(_) => {
                // Assuming pattern matching with regex
                if let (Value::String(s), Value::String(pattern)) = (left, right) {
                    regex::Regex::new(&pattern).map_or(false, |re| re.is_match(&s))
                } else {
                    false
                }
            }
            Comparator::Exists => !left.is_null(),
        }
    }
}

impl LogicItem for Source {
    fn filtered_paths(&self) -> HashSet<String> {
        match self {
            Source::PathSource(path) => path.filtered_paths(),
            Source::ArraySource(values) => values.iter().flat_map(|v| v.using_fields()).collect(),
        }
    }

    fn enrich_context(&self, _value: Value, context: Context) -> Context {
        context
    }

    fn filter(&self, _value: Value, _context: Context) -> bool {
        true
    }

    fn map(&self, value: Value, _context: Context) -> Value {
        match self {
            Source::PathSource(path) => get_value_at_path(&value, path).unwrap_or(Value::Null),
            Source::ArraySource(values) => Value::Array(
                values
                    .iter()
                    .map(|v| v.map(value.clone(), HashMap::new()))
                    .collect(),
            ),
        }
    }
}

impl LogicItem for Expression {}

impl MeeValue {
    fn using_fields(&self, settings: &Settings) -> HashSet<String> {
        match self {
            MeeValue::Path(path) => path.using_fields(),
            MeeValue::Object(map) => map
                .values()
                .flat_map(|v| v.using_fields(&settings))
                .collect(),
            MeeValue::Array(arr) => arr.iter().flat_map(|v| v.using_fields(&settings)).collect(),
            _ => HashSet::new(),
        }
    }

    fn value(&self, context: &Context) -> Result<Option<Value>, String> {
        match self {
            MeeValue::Path(path) => path.value(context).map(|v| v.cloned()),
            MeeValue::Object(map) => {
                let values = map
                    .into_iter()
                    .map(|(k, v)| {
                        v.value(context)
                            .map(|v| (k.clone(), v.unwrap_or(Value::Null)))
                    })
                    .collect::<Result<serde_json::Map<_, _>, _>>()?;
                Ok(Some(Value::Object(values)))
            }
            MeeValue::Array(arr) => {
                let values = arr
                    .into_iter()
                    .map(|v| v.value(context).map(|v| v.unwrap_or(Value::Null)))
                    .collect::<Result<Vec<_>, _>>()?;
                Ok(Some(Value::Array(values)))
            }
            MeeValue::Bool(val) => Ok(Some(Value::Bool(val.clone()))),
            MeeValue::String(val) => Ok(Some(Value::String(val.clone()))),
            MeeValue::Number(val) => {
                let res = Number::from_f64(*val).ok_or(format!("Invalid number '{val}'"))?;
                Ok(Some(Value::Number(res)))
            }
            MeeValue::Null => Ok(Some(Value::Null)),
        }
    }
}

impl Path {
    fn using_fields(&self) -> HashSet<String> {
        HashSet::from([self.field.as_ref().map_or(self.root.clone(), |f| {
            format!("{}{PATH_SEPARATOR}{f}", self.root)
        })])
    }

    fn value<'a>(&'a self, context: &'a Context) -> Result<Option<&'a Value>, String> {
        if let Some(root_object) = context.get(&self.root) {
            if let Some(field_value) = &self.field {
                Ok(root_object.x_get_property(field_value))
            } else {
                Ok(Some(root_object))
            }
        } else {
            Err(format!("Variable with name {} not found", self.root))
        }
    }
}
