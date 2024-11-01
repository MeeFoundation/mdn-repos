mod bool_expression_parser;
mod comparator_parser;
mod expression_parser;
mod iterator_parser;
mod parser;
mod query_parser;
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
}
