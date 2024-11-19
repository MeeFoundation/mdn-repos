mod bool_expression_parser;
mod comparator_parser;
mod expression_parser;
mod iterator_parser;
mod parser;
mod query_parser;
mod statement_parser;
mod support;
mod tests_can_parse;
use crate::error::*;

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
    fn parse(&mut self) -> Result<MeeNode<Query>>;
}

impl ASTParser for ASTParserImpl {
    fn parse(&mut self) -> Result<MeeNode<Query>> {
        let mut parser = Parser::new();

        let language = tree_sitter_mee_ql::LANGUAGE;
        parser.set_language(&language.into())?;

        let tree = parser
            .parse(&self.source_code, None)
            .ok_or(Error::WrongQuery(self.source_code.clone()))?;

        let root_node = tree.root_node();
        dbg!(&root_node);

        //TODO: collect all errors and return them???
        Self::find_errors(root_node, &self.source_code)?;

        let mut ctx = HashMap::new();

        match root_node.kind() {
            "start" => {
                let parser_list = ParserList::default();
                let query_node = root_node.named_child(0).ok_or(self.wrong_query())?;
                parser_list
                    .query
                    .parse(&self.source_code, query_node, &parser_list, &mut ctx)
            }
            _ => Err(self.wrong_query()),
        }
    }
}

impl ASTParserImpl {
    pub fn new(source_code: String) -> Box<dyn ASTParser> {
        Box::new(ASTParserImpl { source_code })
    }

    fn wrong_query(&self) -> Error {
        Error::WrongQuery(self.source_code.clone())
    }

    fn find_errors(node: tree_sitter::Node, source_code: &str) -> Result<()> {
        if node.is_error() {
            Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_code.to_string(),
                "Syntax error".to_string(),
            ))?;
        } else {
            match node.kind() {
                "missing_query_start" => Err(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_code.to_string(),
                    "Expected '[' or '(' as start of query",
                ))?,
                "missing_array_query_end" => Err(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_code.to_string(),
                    "Expected ']' as end of array query",
                ))?,
                "missing_element_query_end" => Err(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_code.to_string(),
                    "Expected ')' as end of element query",
                ))?,
                _ => {}
            }
        }

        for child in node.named_children(&mut node.walk()) {
            Self::find_errors(child, source_code)?;
        }
        Ok(())
    }
}
