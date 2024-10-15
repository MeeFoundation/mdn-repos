use crate::ast::{BoolExpression::*, *};
use std::collections::HashMap;
use std::collections::HashSet;
use tree_sitter::{Node, Parser};

pub struct ASTBuilder {
    source_code: String,
}

fn unescape(s: &str) -> String {
    match s {
        r#"\\"# => r#"\"#.to_string(),
        r#"\""# => r#"""#.to_string(),
        r#"\/""# => r#"/"#.to_string(),
        r#"\b"# => r#"\b"#.to_string(),
        r#"\f"# => r#"\f"#.to_string(),
        r#"\n"# => r#"\n"#.to_string(),
        r#"\r"# => r#"\r"#.to_string(),
        r#"\t"# => r#"\t"#.to_string(),
        str if str.starts_with(r#"\u"#) => {
            let hex_digits = str.get(2..6).unwrap();
            let unicode_value = u32::from_str_radix(&hex_digits, 16).unwrap();
            char::from_u32(unicode_value).unwrap().to_string()
        }
        _ => String::new(),
    }
}

impl ASTBuilder {
    pub fn new(source_code: String) -> Self {
        ASTBuilder { source_code }
    }

    fn dbg_node(&self, node: &Node, method: &str) {
        println!(
            "{}: Visiting node of kind: '{}', text: '{}', node: {:?}",
            method,
            node.kind(),
            self.node_text(node),
            node
        );
    }

    pub fn parse(&mut self) -> Result<Query, String> {
        println!("Starting parse with source code: {}", self.source_code);
        let mut parser = Parser::new();

        let language = tree_sitter_mee_ql::LANGUAGE;
        parser
            .set_language(&language.into())
            .map_err(|e| e.to_string())?;

        let tree = parser
            .parse(&self.source_code, None)
            .ok_or("Failed to parse")?;
        let root_node = tree.root_node();

        self.visit_node(&root_node)
    }

    fn visit_node(&mut self, node: &Node) -> Result<Query, String> {
        self.dbg_node(node, "visit_node");
        match node.kind() {
            "start" => {
                let query_node = node.named_child(0).ok_or("Expected query node")?;
                self.visit_query(&query_node)
            }
            _ => Err(format!("Unknown node kind: {}", node.kind())),
        }
    }

    fn visit_query(&mut self, node: &Node) -> Result<Query, String> {
        self.dbg_node(node, "visit_query");
        match node.kind() {
            "array_query" => {
                let body = self.visit_query_body(&node)?;
                Ok(Query::ArrayQuery { body })
            }
            "element_query" => {
                let body = self.visit_query_body(&node)?;
                Ok(Query::ElementQuery { body })
            }
            _ => Err(format!("Unknown query kind: {}", node.kind())),
        }
    }

    fn visit_query_body(&mut self, node: &Node) -> Result<QueryBody, String> {
        self.dbg_node(node, "visit_query_body");
        let result = node
            .child_by_field_name("result")
            .map(|node| self.visit_value(&node))
            .transpose()?;

        let iterators = self.visit_iterators(node)?;
        let updates = self.visit_update_stmt(node)?;
        let deletes = self.visit_delete_stmt(node)?;

        Ok(QueryBody {
            result,
            iterators,
            updates,
            deletes,
        })
    }

    fn visit_iterators(&mut self, node: &Node) -> Result<Vec<IteratorStmt>, String> {
        self.dbg_node(node, "visit_iterators");
        let mut iterators = Vec::new();
        for child in node.children_by_field_name("iterators", &mut node.walk()) {
            self.dbg_node(&child, "visit_iterators child");
            let item_node = child.child_by_field_name("item").ok_or("Expected item")?;
            let item = self.node_text(&item_node);

            let source_node = child
                .child_by_field_name("source")
                .ok_or("Expected source")?;
            let source = self.visit_source(&source_node)?;

            let assignments = self.visit_assignment(&child)?;

            let filter = if let Some(filter_node) = child.child_by_field_name("filter") {
                Some(self.visit_bool_expression(&filter_node)?)
            } else {
                None
            };

            let offset = if let Some(offset_node) = child.child_by_field_name("offset") {
                Some(self.visit_pos_int(&offset_node)?)
            } else {
                None
            };

            let limit = if let Some(limit_node) = child.child_by_field_name("limit") {
                Some(self.visit_pos_int(&limit_node)?)
            } else {
                None
            };

            iterators.push(IteratorStmt {
                item,
                source,
                assignments,
                filter,
                offset,
                limit,
            });
        }
        Ok(iterators)
    }

    fn visit_assignment(&mut self, node: &Node) -> Result<HashMap<String, Expression>, String> {
        self.dbg_node(node, "visit_assignment");
        let mut assignments = HashMap::new();
        for child in node.children_by_field_name("assignments", &mut node.walk()) {
            self.dbg_node(&child, "visit_assignment child");
            let key = self.node_text(&child.named_child(0).ok_or("Expected key")?);
            let expr =
                self.visit_expression(&child.named_child(1).ok_or("Expected expression")?)?;
            assignments.insert(key, expr);
        }
        Ok(assignments)
    }

    fn visit_update_stmt(&mut self, node: &Node) -> Result<HashMap<Path, Expression>, String> {
        self.dbg_node(node, "visit_update_stmt");
        let mut updates = HashMap::new();
        for child in node.children_by_field_name("updates", &mut node.walk()) {
            self.dbg_node(&child, "visit_update_stmt child");
            let path = self.visit_path(&child.named_child(0).ok_or("Expected key")?)?;
            let expr =
                self.visit_expression(&child.named_child(1).ok_or("Expected expression")?)?;
            updates.insert(path, expr);
        }
        Ok(updates.into())
    }

    fn visit_delete_stmt(&mut self, node: &Node) -> Result<DeleteStmt, String> {
        self.dbg_node(node, "visit_delete_stmt");
        let mut deletes = HashSet::new();
        for child in node.children_by_field_name("deletes", &mut node.walk()) {
            self.dbg_node(&child, "visit_delete_stmt child");
            if let Some(path_node) = child.named_child(0) {
                let path = self.visit_path(&path_node)?;
                deletes.insert(path);
            } else {
                return Ok(DeleteStmt::All);
            }
        }
        if deletes.is_empty() {
            Ok(DeleteStmt::None)
        } else {
            Ok(DeleteStmt::Paths(deletes))
        }
    }

    fn visit_source(&mut self, node: &Node) -> Result<Source, String> {
        self.dbg_node(node, "visit_source");
        match node.kind() {
            "path" => {
                let path = self.visit_path(node)?;
                Ok(Source::PathSource(path))
            }
            "array" => {
                let array = self.visit_array(node)?;
                Ok(Source::ArraySource(array))
            }
            _ => Err(format!("Unknown source kind: {}", node.kind())),
        }
    }

    fn visit_expression(&mut self, node: &Node) -> Result<Expression, String> {
        self.dbg_node(node, "visit_expression");
        match node.kind() {
            "element_query" | "array_query" => {
                let query = self.visit_query(node)?;
                Ok(Expression::Query(Box::new(query)))
            }
            "bool_expression" => {
                let bool_expr = self.visit_bool_expression(node)?;
                Ok(Expression::BoolExpression(Box::new(bool_expr)))
            }
            _ => self
                .visit_value(node)
                .map(|v| Expression::Value(v))
                .or_else(|_| {
                    self.visit_bool_expression(node)
                        .map(|b| Expression::BoolExpression(Box::new(b)))
                }),
        }
    }

    fn visit_value(&mut self, node: &Node) -> Result<Value, String> {
        self.dbg_node(node, "visit_value");
        match node.kind() {
            "path" => {
                let path = self.visit_path(node)?;
                Ok(Value::Path(path))
            }
            "object" => {
                let object = self.visit_object(node)?;
                Ok(Value::Object(object))
            }
            "array" => {
                let array = self.visit_array(node)?;
                Ok(Value::Array(array))
            }
            "number" => {
                let number_text = self.node_text(node);
                let number = number_text.parse::<f64>().map_err(|e| e.to_string())?;
                Ok(Value::Number(number))
            }
            "string" => {
                let string = self.visit_string(node)?;
                Ok(Value::String(string))
            }
            "true" => Ok(Value::Bool(true)),
            "false" => Ok(Value::Bool(false)),
            "null" => Ok(Value::Null),
            _ => Err(format!("Unknown value kind: {}", node.kind())),
        }
    }

    fn visit_string(&mut self, node: &Node) -> Result<String, String> {
        self.dbg_node(node, "visit_string");
        let mut string_content = String::new();
        for child in node.named_children(&mut node.walk()) {
            self.dbg_node(&child, "visit_string child");
            if child.kind() == "string_content" {
                string_content.push_str(&self.node_text(&child));
            } else if child.kind() == "escape_sequence" {
                string_content.push_str(&unescape(&self.node_text(&child)));
            }
        }
        Ok(string_content)
    }

    fn visit_bool_expression(&mut self, node: &Node) -> Result<BoolExpression, String> {
        self.dbg_node(node, "visit_bool_expression");
        match node.kind() {
            "comparison" => {
                let val_node = node.child_by_field_name("val").ok_or("Expected val")?;
                let val = self.visit_value(&val_node)?;

                let comparator_node = node
                    .child_by_field_name("comparator")
                    .ok_or("Expected comparator")?;
                let comparator = self.visit_comparator(&comparator_node)?;

                Ok(Comparison { val, comparator })
            }
            "and_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr = self.visit_bool_expression(&child)?;
                    expressions.push(expr);
                }
                Ok(And(expressions))
            }
            "or_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr = self.visit_bool_expression(&child)?;
                    expressions.push(expr);
                }
                Ok(Or(expressions))
            }
            "not_expression" => {
                let operand_node = node.child(1).ok_or("Expected operand")?;
                let expr = self.visit_bool_expression(&operand_node)?;
                Ok(Not(Box::new(expr)))
            }
            "true" => Ok(True),
            "false" => Ok(False),
            "path" => {
                let path = self.visit_path(node)?;
                Ok(BoolPath(path))
            }
            "(" => {
                let next_sibling = node.next_sibling().ok_or("Expected next sibling")?;
                self.visit_bool_expression(&next_sibling)
            }
            _ => Err(format!(
                "Unknown bool expression kind: {}. next: {}, text: {}",
                node.kind(),
                self.node_text(&node.next_sibling().unwrap()),
                self.node_text(&node)
            )),
        }
    }

    fn visit_comparator(&mut self, node: &Node) -> Result<Comparator, String> {
        self.dbg_node(node, "visit_comparator");
        let operator_node = node.child(0).ok_or("Expected operator")?;
        let operator = self.node_text(&operator_node);
        match operator.as_str() {
            "==" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Eq(expr))
            }
            "!=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Ne(expr))
            }
            ">" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Gt(expr))
            }
            "<" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Lt(expr))
            }
            ">=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Ge(expr))
            }
            "<=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Le(expr))
            }
            "matches" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = self.visit_expression(&right_node)?;
                Ok(Comparator::Matches(expr))
            }
            "exists" => Ok(Comparator::Exists),
            _ => Err(format!(
                "Unknown comparator operator: {}, text: {}",
                operator,
                self.node_text(&node)
            )),
        }
    }

    fn visit_object(&mut self, node: &Node) -> Result<ValueMap, String> {
        self.dbg_node(node, "visit_object");
        let mut pairs = HashMap::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "pair" {
                self.dbg_node(&child, "visit_object pair");
                let key = self.visit_string(&child.named_child(0).ok_or("Expected key")?)?;

                let value = self.visit_value(&child.named_child(1).ok_or("Expected value")?)?;

                pairs.insert(key, value);
            }
        }
        Ok(pairs.into())
    }

    fn visit_array(&mut self, node: &Node) -> Result<Vec<Value>, String> {
        self.dbg_node(node, "visit_array");
        let mut elements = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            self.dbg_node(&child, "visit_array child");
            let value = self.visit_value(&child)?;
            elements.push(value);
        }
        Ok(elements)
    }

    fn visit_path(&mut self, node: &Node) -> Result<Path, String> {
        self.dbg_node(node, "visit_path");
        let mut segments = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "ident" {
                segments.push(self.node_text(&child));
            }
        }
        Ok(Path(segments))
    }

    fn node_text(&self, node: &Node) -> String {
        self.source_code[node.byte_range()].to_string()
    }

    fn visit_pos_int(&mut self, node: &Node) -> Result<usize, String> {
        let text = self.node_text(node);
        let number = text.parse::<usize>().map_err(|e| e.to_string())?;
        Ok(number)
    }
}

mod tests {
    use super::ASTBuilder;
    use crate::ast::{BoolExpression::*, *};
    use std::collections::HashMap;

    #[test]
    fn test_greedy_and_grouping() {
        let source = "[for user in users if true and false and path]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(True.and(false).and::<Path>(("path").into())),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_greedy_or_grouping() {
        let source = "[for user in users if true or false or path]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.or(false).or::<Path>(("path").into())),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_not_operation() {
        let source = "[for user in users if not true]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.not()),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_and_operation() {
        let source = "[for user in users if true and false]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.and(false)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_or_operation() {
        let source = "[for user in users if true or false]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.or(false)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_grouped_expression() {
        let source = "[for user in users if true and (false or true)]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.and(False.or(true))),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_operation_priorities() {
        let source = "[for user in users if true and not true or false and true]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(True.and(True.not()).or(False.and(true))),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_complicated_expression() {
        let source = "[for user in users if not user.is_admin or check1 and check2 and (check4 or not check5 or not (check6 and check7))]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        BoolPath("user.is_admin".into())
                            .not()
                            .or(BoolPath("check1".into())
                                .and(BoolPath("check2".into()))
                                .and(
                                    BoolPath("check4".into())
                                        .or(BoolPath("check5".into()).not())
                                        .or(BoolPath("check6".into())
                                            .and(BoolPath("check7".into()))
                                            .not()),
                                )),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    //TODO: fix escaping
    #[test]
    fn test_with_comparator() {
        let source = r#"[for user in users 
        if true and user.last_name exists or user.age > 18 and user.phone matches "+1\\d{10}"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        True.and(Value::Path("user.last_name".into()).exists())
                            .or(Value::Path("user.age".into())
                                .gt(18)
                                .and(Value::Path("user.phone".into()).matches(r#"+1\d{10}"#))),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_json_object() {
        let source = r#"[{"key1": "value1", "key2": 123, "key3": true} for user in users]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let mut map = HashMap::new();
        map.insert("key1".to_string(), Value::String("value1".to_string()));
        map.insert("key2".to_string(), Value::Number(123.0));
        map.insert("key3".to_string(), Value::Bool(true));
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(map.into()),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_json_array() {
        let source = "[[1, 2, 3, \"four\", false] for user in users]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Array(vec![
                    1.into(),
                    2.into(),
                    3.into(),
                    "four".into(),
                    false.into(),
                ])),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_string() {
        let source = r#"["four" for user in users]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some("four".into()),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_number() {
        let source = "[1 for user in users]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(1.into()),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_boolean_expression() {
        let source = "[true for user in users]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(true.into()),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_embedded_path() {
        let source =
            r#"({"age": user.age, "names": [user.name, user.last_name]} for user in users)"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let mut map = HashMap::new();
        map.insert("age".to_string(), Value::Path("user.age".into()));
        map.insert(
            "names".to_string(),
            Value::Array(vec![
                Value::Path("user.name".into()),
                Value::Path("user.last_name".into()),
            ]),
        );
        let expected = Query::ElementQuery {
            body: QueryBody {
                result: Some(map.into()),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_equal() {
        let source = r#"[user.id for user in users if user.name == "Ivan"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.name".into()).eq(Value::String("Ivan".to_string())),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_not_equal() {
        let source = r#"[user.id for user in users if user.name != "Ivan"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.name".into()).ne(Value::String("Ivan".to_string())),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_greater_than() {
        let source = r#"[user.id for user in users if user.age > 30]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.age".into()).gt(30)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_less_than() {
        let source = r#"[user.id for user in users if user.age < 30]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.age".into()).lt(30)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_greater_than_or_equal() {
        let source = r#"[user.id for user in users if user.age >= 30]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.age".into()).ge(30)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_less_than_or_equal() {
        let source = r#"[user.id for user in users if user.age <= 30]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.age".into()).le(30)),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_matches() {
        let source = r#"[user.id for user in users if user.name matches "I.*"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.name".into()).matches(Value::String("I.*".to_string())),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_exists() {
        let source = r#"[user.id for user in users if user.email exists]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),

                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.email".into()).exists()),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_json_object_assignment() {
        let source = r#"[res for user in users res = {"name": user.name}]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::Value(
                            HashMap::from([("name".to_string(), Value::Path("user.name".into()))])
                                .into(),
                        ),
                    )]),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_path_assignment() {
        let source = "[res for user in users res = user.name]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::Value(Value::Path("user.name".into())),
                    )])
                    .into(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_string_assignment() {
        let source = r#"[res for user in users res = "=name"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::Value(Value::String("=name".to_string())),
                    )])
                    .into(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_logical_expression_assignment() {
        let source = "[res for user in users res = not user.is_admin or true]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::BoolExpression(Box::new(
                            BoolExpression::BoolPath("user.is_admin".into())
                                .not()
                                .or(BoolExpression::True),
                        )),
                    )])
                    .into(),
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_by_id() {
        let source = r#"[user for user in users() if user.id == "534622344"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.id".into()).eq(Value::String("534622344".to_string())),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_last_name_by_email_and_name() {
        let source = r#"[user.last_name for user in users() if user.email == "some@gmail.com" and name == "Denis"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.last_name".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.email".into())
                            .eq(Value::String("some@gmail.com".to_string()))
                            .and(Value::Path("name".into()).eq(Value::String("Denis".to_string()))),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_by_country_code_or_country() {
        let source = r#"[{"name" : user.name, "phone" : user.phone} for user in users() if user.phone matches "+1[0-9]{11}" or user.country == "USA"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(
                    HashMap::from([
                        ("name".to_string(), Value::Path("user.name".into())),
                        ("phone".to_string(), Value::Path("user.phone".into())),
                    ])
                    .into(),
                ),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.phone".into())
                            .matches(Value::String("+1[0-9]{11}".to_string()))
                            .or(Value::Path("user.country".into())
                                .eq(Value::String("USA".to_string()))),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_users_who_made_a_purchase_after_a_date() {
        let source = r#"[user.id for user in users() for order in user.orders if order.date >= "2023-09-24"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.id".into())),
                iterators: vec![
                    IteratorStmt {
                        item: "user".to_string(),
                        source: Source::PathSource("users".into()),
                        assignments: HashMap::new(),
                        filter: None,
                        offset: None,
                        limit: None,
                    },
                    IteratorStmt {
                        item: "order".to_string(),
                        source: Source::PathSource(Path(vec![
                            "user".to_string(),
                            "orders".to_string(),
                        ])),
                        assignments: HashMap::new(),
                        filter: Some(
                            Value::Path("order.date".into())
                                .ge(Value::String("2023-09-24".to_string())),
                        ),
                        offset: None,
                        limit: None,
                    },
                ],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_10_by_age_gender_and_country() {
        let source = r#"[user for user in users() if (user.age >= 18 or user.age <= 25) and user.gender == "Male" and user.country == "USA" limit 10]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(
                        Value::Path("user.age".into())
                            .ge(18)
                            .or(Value::Path("user.age".into()).le(25))
                            .and(
                                Value::Path("user.gender".into())
                                    .eq(Value::String("Male".to_string())),
                            )
                            .and(
                                Value::Path("user.country".into())
                                    .eq(Value::String("USA".to_string())),
                            ),
                    ),
                    offset: None,
                    limit: Some(10),
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_users_for_refund_for_a_canceled_flight() {
        let source = r#"[
        {
            "name": user.name, 
            "family_name": user.last_name, 
            "card_number": number
        } 
        for user in users()
        flight = (1 for flight in user.flights if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00") 
        number = (card.number for card in user.payment_cards limit 1) 
        if flight exists and number exists]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(
                    HashMap::from([
                        ("name".to_string(), Value::Path("user.name".into())),
                        (
                            "family_name".to_string(),
                            Value::Path("user.last_name".into()),
                        ),
                        ("card_number".to_string(), Value::Path("number".into())),
                    ])
                    .into(),
                ),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::from([
                        (
                            "flight".to_string(),
                            Expression::Query(Box::new(Query::ElementQuery {
                                body: QueryBody {
                                    result: Some(1.into()),
                                    iterators: vec![IteratorStmt {
                                        item: "flight".to_string(),
                                        source: Source::PathSource("user.flights".into()),
                                        assignments: HashMap::new(),
                                        filter: Some(
                                            Value::Path("flight.number".into()).eq("AS702").and(
                                                Value::Path("flight.dt".into())
                                                    .eq("2024.11.11T11:00:00"),
                                            ),
                                        ),
                                        offset: None,
                                        limit: None,
                                    }],
                                    updates: HashMap::new(),
                                    deletes: DeleteStmt::None,
                                },
                            })),
                        ),
                        (
                            "number".to_string(),
                            Expression::Query(Box::new(Query::ElementQuery {
                                body: QueryBody {
                                    result: Some(Value::Path("card.number".into())),
                                    iterators: vec![IteratorStmt {
                                        item: "card".to_string(),
                                        source: Source::PathSource("user.payment_cards".into()),
                                        assignments: HashMap::new(),
                                        filter: None,
                                        offset: None,
                                        limit: Some(1),
                                    }],
                                    updates: HashMap::new(),
                                    deletes: DeleteStmt::None,
                                },
                            })),
                        ),
                    ]),
                    filter: Some(
                        Value::Path("flight".into())
                            .exists()
                            .and(Value::Path("number".into()).exists()),
                    ),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::new(),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_update_flight_departure_time() {
        let source = r#"[user.passport for user in users() for flight in user.flights if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00" set flight.dt = "2024.11.11T12:00:00"]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("user.passport".into())),
                iterators: vec![
                    IteratorStmt {
                        item: "user".to_string(),
                        source: Source::PathSource(Path(vec!["users".to_string()])),
                        assignments: HashMap::new(),
                        filter: None,
                        offset: None,
                        limit: None,
                    },
                    IteratorStmt {
                        item: "flight".to_string(),
                        source: Source::PathSource(Path(vec![
                            "user".to_string(),
                            "flights".to_string(),
                        ])),
                        assignments: HashMap::new(),
                        filter: Some(
                            Value::Path("flight.number".into())
                                .eq("AS702")
                                .and(Value::Path("flight.dt".into()).eq("2024.11.11T11:00:00")),
                        ),
                        offset: None,
                        limit: None,
                    },
                ],
                updates: HashMap::from([(
                    Path(vec!["flight".to_string(), "dt".to_string()]),
                    Expression::Value(Value::String("2024.11.11T12:00:00".to_string())),
                )]),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_add_a_payment_card() {
        let source = r#"[for user in users() if user.id == "4435" set user.payment_cards = [{"number":"1234 1234 1234 1234", "expires": "08/30", "cvv" : "111"}, {"number":"5555 1234 1234 1234", "expires": "08/30", "cvv" : "222"}]]"#;
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let card1 = HashMap::from([
            ("number", "1234 1234 1234 1234"),
            ("expires", "08/30"),
            ("cvv", "111"),
        ]);
        let card1: Value = card1.into();
        let card2 = HashMap::from([
            ("number", "5555 1234 1234 1234"),
            ("expires", "08/30"),
            ("cvv", "222"),
        ]);
        let card2: Value = card2.into();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::new(),
                    filter: Some(Value::Path("user.id".into()).eq("4435")),
                    offset: None,
                    limit: None,
                }],
                updates: HashMap::from([(
                    Path::from_dot_separated("user.payment_cards"),
                    Expression::Value(vec![card1, card2].into()),
                )]),
                deletes: DeleteStmt::None,
            },
        };
        assert_eq!(query, expected);
    }
}
