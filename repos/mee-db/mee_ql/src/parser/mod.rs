mod bool_expression_parser;
mod comparator_parser;
mod expression_parser;
mod iterator_parser;
mod parser;
mod query_parser;
mod support;
mod value_parser;

pub(crate) use crate::ast::*;
pub(crate) use bool_expression_parser::*;
pub(crate) use comparator_parser::*;
pub(crate) use expression_parser::*;
pub(crate) use iterator_parser::*;
pub(crate) use parser::*;
pub(crate) use query_parser::*;
pub(crate) use support::*;
pub(crate) use value_parser::*;

use tree_sitter::Parser;

pub struct ASTParserImpl {
    source_code: String,
}

pub trait ASTParser {
    fn parse(&mut self) -> Result<Query, String>;
}

impl ASTParser for ASTParserImpl {
    fn parse(&mut self) -> Result<Query, String> {
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
        match root_node.kind() {
            "start" => {
                let parser_list = ParserList::default();
                let query_node = root_node.named_child(0).ok_or("Expected query node")?;
                parser_list
                    .query
                    .parse(&self.source_code, query_node, &parser_list)
            }
            _ => Err(format!(
                "Unknown node kind: {}, text: {}",
                root_node.kind(),
                node_text(&root_node, &self.source_code)?,
            )),
        }
    }
}

impl ASTParserImpl {
    pub fn new(source_code: String) -> Box<dyn ASTParser> {
        Box::new(ASTParserImpl { source_code })
    }
}

#[cfg(test)]
mod tests {
    use super::ASTParserImpl;
    use crate::ast::{BoolExpression::*, *};
    use std::collections::HashMap;

    #[test]
    fn test_greedy_and_grouping() {
        let source = "[for user in users if true and false and path]";
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource(Path(vec!["users".to_string()])),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::Value(Value::Path("user.name".into())),
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
    fn test_string_assignment() {
        let source = r#"[res for user in users res = "=name"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
        let expected = Query::ArrayQuery {
            body: QueryBody {
                result: Some(Value::Path("res".into())),
                iterators: vec![IteratorStmt {
                    item: "user".to_string(),
                    source: Source::PathSource("users".into()),
                    assignments: HashMap::from([(
                        "res".to_string(),
                        Expression::Value(Value::String("=name".to_string())),
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
    fn test_logical_expression_assignment() {
        let source = "[res for user in users res = not user.is_admin or true]";
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
    fn test_find_by_id() {
        let source = r#"[user for user in users() if user.id == "534622344"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
        let mut parser = ASTParserImpl::new(source.to_string());
        let query = parser.parse().unwrap();
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
