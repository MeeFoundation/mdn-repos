use crate::ast::*;
use tree_sitter::{Node, Parser};

pub struct ASTBuilder {
    source_code: String,
}

impl ASTBuilder {
    pub fn new(source_code: String) -> Self {
        ASTBuilder { source_code }
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

        println!("Parse tree root node kind: {}", root_node.kind());
        self.visit_node(&root_node)
    }

    fn visit_node(&mut self, node: &Node) -> Result<Query, String> {
        println!("Visiting node of kind: {}", node.kind());
        match node.kind() {
            "start" => {
                let query_node = node.named_child(0).ok_or("Expected query node")?;
                println!("Found start node, visiting query node");
                self.visit_query(&query_node)
            }
            _ => Err(format!("Unknown node kind: {}", node.kind())),
        }
    }

    fn visit_query(&mut self, node: &Node) -> Result<Query, String> {
        println!("Visiting query node of kind: {}", node.kind());
        match node.kind() {
            "array_query" => {
                println!("Processing array_query");
                let body = self.visit_query_body(&node)?;
                Ok(Query::ArrayQuery { body })
            }
            "element_query" => {
                println!("Processing element_query");
                let body = self.visit_query_body(&node)?;
                Ok(Query::ElementQuery { body })
            }
            _ => Err(format!("Unknown query kind: {}", node.kind())),
        }
    }

    fn visit_query_body(&mut self, node: &Node) -> Result<QueryBody, String> {
        println!("Visiting query body node of kind: {}", node.kind());
        let mut result = None;
        let mut iterators = Vec::new();
        let mut updates = Vec::new();
        let mut deletes = Vec::new();

        if let Some(result_node) = node.child_by_field_name("result") {
            println!("Found result node");
            result = Some(self.visit_value(&result_node)?);
        }

        for child in node.children_by_field_name("iterators", &mut node.walk()) {
            println!("Visiting iterator statement");
            let iterator = self.visit_iterator_stmt(&child)?;
            iterators.push(iterator);
        }

        for child in node.children_by_field_name("updates", &mut node.walk()) {
            println!("Visiting update statement");
            let update = self.visit_update_stmt(&child)?;
            updates.push(update);
        }

        for child in node.children_by_field_name("deletes", &mut node.walk()) {
            println!("Visiting delete statement");
            let delete = self.visit_delete_stmt(&child)?;
            deletes.push(delete);
        }

        Ok(QueryBody {
            result,
            iterators,
            updates,
            deletes,
        })
    }

    fn visit_iterator_stmt(&mut self, node: &Node) -> Result<IteratorStmt, String> {
        println!("Visiting iterator statement node k");
        let item_node = node.child_by_field_name("item").ok_or("Expected item")?;
        let item = self.node_text(&item_node);

        let source_node = node
            .child_by_field_name("source")
            .ok_or("Expected source")?;
        let source = self.visit_source(&source_node)?;

        let assignments = node
            .children_by_field_name("assignments", &mut node.walk())
            .map(|node| self.visit_assignment(&node))
            .collect::<Result<Vec<_>, String>>()?;

        let filter = if let Some(filter_node) = node.child_by_field_name("filter") {
            Some(self.visit_bool_expression(&filter_node)?)
        } else {
            None
        };

        let offset = if let Some(offset_node) = node.child_by_field_name("offset") {
            Some(self.visit_pos_int(&offset_node)?)
        } else {
            None
        };

        let limit = if let Some(limit_node) = node.child_by_field_name("limit") {
            Some(self.visit_pos_int(&limit_node)?)
        } else {
            None
        };

        Ok(IteratorStmt {
            item,
            source,
            assignments,
            filter,
            offset,
            limit,
        })
    }

    fn visit_assignment(&mut self, node: &Node) -> Result<Assignment, String> {
        let var_node = node.child_by_field_name("var").ok_or("Expected var")?;
        let var = self.node_text(&var_node);

        let expr_node = node.child_by_field_name("expr").ok_or("Expected expr")?;
        let expr = self.visit_expression(&expr_node)?;

        Ok(Assignment { var, expr })
    }

    fn visit_update_stmt(&mut self, node: &Node) -> Result<UpdateStmt, String> {
        let field_node = node.child_by_field_name("field").ok_or("Expected field")?;
        let field = self.visit_path(&field_node)?;

        let expr_node = node.child_by_field_name("expr").ok_or("Expected expr")?;
        let expr = self.visit_expression(&expr_node)?;

        Ok(UpdateStmt { field, expr })
    }

    fn visit_delete_stmt(&mut self, node: &Node) -> Result<DeleteStmt, String> {
        let path_node = node.child_by_field_name("field");
        let path = if let Some(path_node) = path_node {
            Some(self.visit_path(&path_node)?)
        } else {
            None
        };

        Ok(DeleteStmt { path })
    }

    fn visit_source(&mut self, node: &Node) -> Result<Source, String> {
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
        match node.kind() {
            "query" => {
                let query = self.visit_query(node)?;
                Ok(Expression::Query(Box::new(query)))
            }
            "bool_expression" => {
                let bool_expr = self.visit_bool_expression(node)?;
                Ok(Expression::BoolExpression(Box::new(bool_expr)))
            }
            _ => Ok(Expression::Value(self.visit_value(node)?)),
        }
    }

    fn visit_value(&mut self, node: &Node) -> Result<Value, String> {
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
                let string_content = self.node_text(node);
                Ok(Value::String(string_content))
            }
            "true" => Ok(Value::Bool(true)),
            "false" => Ok(Value::Bool(false)),
            "null" => Ok(Value::Null),
            _ => Err(format!("Unknown value kind: {}", node.kind())),
        }
    }

    fn visit_bool_expression(&mut self, node: &Node) -> Result<BoolExpression, String> {
        match node.kind() {
            "comparison" => {
                let val_node = node.child_by_field_name("val").ok_or("Expected val")?;
                let val = self.visit_value(&val_node)?;

                let comparator_node = node
                    .child_by_field_name("comparator")
                    .ok_or("Expected comparator")?;
                let comparator = self.visit_comparator(&comparator_node)?;

                Ok(BoolExpression::Comparison { val, comparator })
            }
            "and_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr = self.visit_bool_expression(&child)?;
                    expressions.push(expr);
                }
                Ok(BoolExpression::And(expressions))
            }
            "or_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr = self.visit_bool_expression(&child)?;
                    expressions.push(expr);
                }
                Ok(BoolExpression::Or(expressions))
            }
            "not_expression" => {
                let operand_node = node.child(1).ok_or("Expected operand")?;
                let expr = self.visit_bool_expression(&operand_node)?;
                Ok(BoolExpression::Not(Box::new(expr)))
            }
            "true" => Ok(BoolExpression::True),
            "false" => Ok(BoolExpression::False),
            "path" => {
                let path = self.visit_path(node)?;
                Ok(BoolExpression::BoolPath(path))
            }
            _ => Err(format!("Unknown bool expression kind: {}", node.kind())),
        }
    }

    fn visit_comparator(&mut self, node: &Node) -> Result<Comparator, String> {
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
            _ => Err(format!("Unknown comparator operator: {}", operator)),
        }
    }

    fn visit_object(&mut self, node: &Node) -> Result<Object, String> {
        let mut pairs = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "pair" {
                let pair = self.visit_pair(&child)?;
                pairs.push(pair);
            }
        }
        Ok(Object { pairs })
    }

    fn visit_pair(&mut self, node: &Node) -> Result<Pair, String> {
        let key_node = node.child_by_field_name("key").ok_or("Expected key")?;
        let key = self.node_text(&key_node);

        let value_node = node.child_by_field_name("value").ok_or("Expected value")?;
        let value = self.visit_value(&value_node)?;

        Ok(Pair { key, value })
    }

    fn visit_array(&mut self, node: &Node) -> Result<Array, String> {
        let mut elements = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "_expression" {
                let expr = self.visit_expression(&child)?;
                elements.push(expr);
            }
        }
        Ok(Array(elements))
    }

    fn visit_path(&mut self, node: &Node) -> Result<Path, String> {
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
    use super::*;

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
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::True,
                        BoolExpression::False,
                        BoolExpression::BoolPath(Path(vec!["path".to_string()])),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::Or(vec![
                        BoolExpression::True,
                        BoolExpression::False,
                        BoolExpression::BoolPath(Path(vec!["path".to_string()])),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::Not(Box::new(BoolExpression::True))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::True,
                        BoolExpression::False,
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::Or(vec![
                        BoolExpression::True,
                        BoolExpression::False,
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::True,
                        BoolExpression::Or(vec![BoolExpression::False, BoolExpression::True]),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::True,
                        BoolExpression::Or(vec![BoolExpression::False, BoolExpression::True]),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::Not(Box::new(BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "is_admin".to_string(),
                        ])))),
                        BoolExpression::And(vec![
                            BoolExpression::BoolPath(Path(vec!["check1".to_string()])),
                            BoolExpression::BoolPath(Path(vec!["check2".to_string()])),
                            BoolExpression::Or(vec![
                                BoolExpression::BoolPath(Path(vec!["check4".to_string()])),
                                BoolExpression::Not(Box::new(BoolExpression::BoolPath(Path(
                                    vec!["check5".to_string()],
                                )))),
                                BoolExpression::Not(Box::new(BoolExpression::And(vec![
                                    BoolExpression::BoolPath(Path(vec!["check6".to_string()])),
                                    BoolExpression::BoolPath(Path(vec!["check7".to_string()])),
                                ]))),
                            ]),
                        ]),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_with_comparator() {
        let source = "[for user in users if true and user.last_name exists or user.age > 18 and user.prone matches \"+1\\d{10}\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::True,
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "last_name".to_string(),
                        ])),
                        BoolExpression::Or(vec![
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "age".to_string(),
                            ])),
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "prone".to_string(),
                            ])),
                        ]),
                        BoolExpression::And(vec![
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "age".to_string(),
                            ])),
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "prone".to_string(),
                            ])),
                        ]),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_json_object() {
        let source = "[{\"key1\": \"value1\", \"key2\": 123, \"key3\": true} for user in users]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_string() {
        let source = "[\"four\" for user in users]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                result: Some(Value::Bool(true)),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_embedded_path() {
        let source =
            "({\"age\": user.age, \"names\": [user.name, user.last_name]} for user in users)";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_equal() {
        let source = "[user.id for user in users if user.name == \"Ivan\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "name".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_not_equal() {
        let source = "[user.id for user in users if user.name != \"Ivan\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "name".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_greater_than() {
        let source = "[user.id for user in users if user.age > 30]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "age".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_less_than() {
        let source = "[user.id for user in users if user.age < 30]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "age".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_greater_than_or_equal() {
        let source = "[user.id for user in users if user.age >= 30]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "age".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_less_than_or_equal() {
        let source = "[user.id for user in users if user.age <= 30]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "age".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_matches() {
        let source = "[user.id for user in users if user.name matches \"I.*\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "name".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_exists() {
        let source = "[user.id for user in users if user.email exists]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "email".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_json_object_assignment() {
        let source = "[res for user in users res = {\"name\": user.name}]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_string_assignment() {
        let source = "[res for user in users res = \"=name\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
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
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: None,
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_by_id() {
        let source = "[user for user in users() if user.id == \"534622344\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "id".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_last_name_by_email_and_name() {
        let source = "[user.last_name for user in users() if user.email == \"some@gmail.com\" and name == \"Denis\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "email".to_string(),
                        ])),
                        BoolExpression::BoolPath(Path(vec!["name".to_string()])),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_find_by_country_code_or_country() {
        let source = "[{\"name\" : user.name, \"phone\" : user.phone} for user in users() if user.phone matches \"+1[0-9]{11}\" or user.country == \"USA\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::Or(vec![
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "phone".to_string(),
                        ])),
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "country".to_string(),
                        ])),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_users_who_made_a_purchase_after_a_date() {
        let source = "[user.id for user in users() for order in user.orders if order.date >= \"2023-09-24\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![
                    IteratorStmt {
                        item: "user".to_string(),
                        source: Source::PathSource(Path(vec!["users".to_string()])),
                        assignments: vec![],
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
                        assignments: vec![],
                        filter: Some(BoolExpression::BoolPath(Path(vec![
                            "order".to_string(),
                            "date".to_string(),
                        ]))),
                        offset: None,
                        limit: None,
                    },
                ],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_10_by_age_gender_and_country() {
        let source = "[user for user in users() if (user.age >= 18 or user.age <= 25) and user.gender == \"Male\" and user.country == \"USA\" limit 10]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::Or(vec![
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "age".to_string(),
                            ])),
                            BoolExpression::BoolPath(Path(vec![
                                "user".to_string(),
                                "age".to_string(),
                            ])),
                        ]),
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "gender".to_string(),
                        ])),
                        BoolExpression::BoolPath(Path(vec![
                            "user".to_string(),
                            "country".to_string(),
                        ])),
                    ])),
                    offset: None,
                    limit: Some(10),
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_select_users_for_refund_for_a_canceled_flight() {
        let source = "[{\"name\": user.name, \"family_name\": user.last_name, \"card_number\": number} for user in users() flight = (1 for flight in user.flights if flight.number == \"AS702\" and flight.dt == \"2024.11.11T11:00:00\") number = (card.number for card in user.payment_cards limit 1) if flight exists and number exists]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::And(vec![
                        BoolExpression::BoolPath(Path(vec!["flight".to_string()])),
                        BoolExpression::BoolPath(Path(vec!["number".to_string()])),
                    ])),
                    offset: None,
                    limit: None,
                }],
                updates: vec![],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_update_flight_departure_time() {
        let source = "[user.passport for user in users() for flight in user.flights if flight.number == \"AS702\" and flight.dt == \"2024.11.11T11:00:00\" set flight.dt = \"2024.11.11T12:00:00\"]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![
                    IteratorStmt {
                        item: "user".to_string(),
                        source: Source::PathSource(Path(vec!["users".to_string()])),
                        assignments: vec![],
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
                        assignments: vec![],
                        filter: Some(BoolExpression::And(vec![
                            BoolExpression::BoolPath(Path(vec![
                                "flight".to_string(),
                                "number".to_string(),
                            ])),
                            BoolExpression::BoolPath(Path(vec![
                                "flight".to_string(),
                                "dt".to_string(),
                            ])),
                        ])),
                        offset: None,
                        limit: None,
                    },
                ],
                updates: vec![UpdateStmt {
                    field: Path(vec!["flight".to_string(), "dt".to_string()]),
                    expr: Expression::Value(Value::String("2024.11.11T12:00:00".to_string())),
                }],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn test_add_a_payment_card() {
        let source = "[for user in users() if user.id == \"4435\" set user.payment_cards = [{\"number\":\"1234 1234 1234 1234\", \"expires\": \"08/30\", \"cvv\" : \"111\"}, {\"number\":\"5555 1234 1234 1234\", \"expires\": \"08/30\", \"cvv\" : \"222\"}]]";
        let mut builder = ASTBuilder::new(source.to_string());
        let query = builder.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: None,
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: vec![],
                    filter: Some(BoolExpression::BoolPath(Path(vec![
                        "user".to_string(),
                        "id".to_string(),
                    ]))),
                    offset: None,
                    limit: None,
                }],
                updates: vec![UpdateStmt {
                    field: Path(vec!["user".to_string(), "payment_cards".to_string()]),
                    expr: Expression::Value(Value::Array(Array(vec![
                        Expression::Value(Value::Object(Object {
                            pairs: vec![
                                Pair {
                                    key: "number".to_string(),
                                    value: Value::String("1234 1234 1234 1234".to_string()),
                                },
                                Pair {
                                    key: "expires".to_string(),
                                    value: Value::String("08/30".to_string()),
                                },
                                Pair {
                                    key: "cvv".to_string(),
                                    value: Value::String("111".to_string()),
                                },
                            ],
                        })),
                        Expression::Value(Value::Object(Object {
                            pairs: vec![
                                Pair {
                                    key: "number".to_string(),
                                    value: Value::String("5555 1234 1234 1234".to_string()),
                                },
                                Pair {
                                    key: "expires".to_string(),
                                    value: Value::String("08/30".to_string()),
                                },
                                Pair {
                                    key: "cvv".to_string(),
                                    value: Value::String("222".to_string()),
                                },
                            ],
                        })),
                    ]))),
                }],
                deletes: vec![],
            },
        };
        assert_eq!(query, expected);
    }
}
