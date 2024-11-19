mod bool_expression_parser;
mod comparator_parser;
mod expression_parser;
mod iterator_parser;
mod parser;
mod query_parser;
mod statement_parser;
mod support;
mod tests_can_parse;

pub(crate) use crate::ast::*;
pub(crate) use bool_expression_parser::*;
pub(crate) use comparator_parser::*;
pub(crate) use expression_parser::*;
pub(crate) use iterator_parser::*;
pub(crate) use parser::*;
pub(crate) use query_parser::*;
pub(crate) use support::*;

use std::collections::HashMap;
use tree_sitter::Parser;

pub type Context = HashMap<String, MeeNode<Expression>>;

pub const ROOT_PATH: &str = "users";

pub struct ASTParserImpl {
    source_code: String,
}

pub trait ASTParser {
    fn parse(&mut self) -> Result<MeeNode<Query>, String>;
}

impl ASTParser for ASTParserImpl {
    fn parse(&mut self) -> Result<MeeNode<Query>, String> {
        let mut parser = Parser::new();

        let language = tree_sitter_mee_ql::LANGUAGE;
        parser
            .set_language(&language.into())
            .map_err(|e| e.to_string())?;

        let tree = parser
            .parse(&self.source_code, None)
            .ok_or("Failed to parse")?;
        let root_node = tree.root_node();
        dbg!(&root_node);

        let mut errors = Vec::new();
        Self::find_errors(root_node, &self.source_code, &mut errors);
        if !errors.is_empty() {
            return Err(errors.join("\n"));
        }

        let mut ctx = HashMap::new();

        match root_node.kind() {
            "start" => {
                let parser_list = ParserList::default();
                let query_node = root_node.named_child(0).ok_or("Expected query node")?;
                parser_list
                    .query
                    .parse(&self.source_code, query_node, &parser_list, &mut ctx)
            }
            _ => Err(format!(
                "Unknown node kind: {}, text: {}",
                root_node.kind(),
                node_text(&root_node, &self.source_code)?.value,
            )),
        }
    }
}

impl ASTParserImpl {
    pub fn new(source_code: String) -> Box<dyn ASTParser> {
        Box::new(ASTParserImpl { source_code })
    }

    fn find_errors(node: tree_sitter::Node, source_code: &str, errors: &mut Vec<String>) {
        if node.is_error() {
            let start = node.start_position();
            let end = node.end_position();
            let error_text = &source_code[node.start_byte()..node.end_byte()];
            errors.push(format!(
                "Syntax error from {:?} to {:?}: '{}'",
                start, end, error_text
            ));
        } else {
            match node.kind() {
                "missing_query_start" => {
                    let start = node.start_position();
                    let end = node.end_position();
                    errors.push(format!("Expected '[' or '(' at {:?} to {:?}", start, end));
                }
                "missing_array_query_end" => {
                    let start = node.start_position();
                    let end = node.end_position();
                    errors.push(format!("Expected ']' at {:?} to {:?}", start, end));
                }
                "missing_element_query_end" => {
                    let start = node.start_position();
                    let end = node.end_position();
                    errors.push(format!("Expected ')' at {:?} to {:?}", start, end));
                }
                _ => {}
            }
        }

        for child in node.named_children(&mut node.walk()) {
            Self::find_errors(child, source_code, errors);
        }
    }
}
