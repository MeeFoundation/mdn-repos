use super::parser::{Parser, ParserList};
use super::*;
use crate::error::*;
use tree_sitter::Node;

pub struct QueryParser;
impl QueryParser {
    fn parse_query_body(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Query>> {
        let query_type = match node.kind() {
            "array_query" => QueryType::All,
            "element_query" => QueryType::FirstOrNull,
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!("Unknown query kind: {}", node.kind()),
            ))?,
        };

        let main_iterator = parser_list.iterator_stmt.parse(
            source_text,
            node.child_by_field_name("main_iterator")
                .ok_or(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_text,
                    "Main iterator not found",
                ))?,
            parser_list,
            ctx,
        )?;

        let mut statements = Vec::new();
        for child in node.children_by_field_name("statements", &mut node.walk()) {
            statements.push(
                parser_list
                    .statement
                    .parse(source_text, child, parser_list, ctx)?,
            );
        }

        let result = node
            .child_by_field_name("result")
            .map(|node| parser_list.value.parse(source_text, node, parser_list, ctx))
            .transpose()?;

        Ok(mee_node(
            &node,
            Query {
                result,
                main_iterator,
                statements,
                query_type,
            },
        ))
    }
}

impl Parser<MeeNode<Query>> for QueryParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Query>> {
        self.parse_query_body(source_text, node, parser_list, ctx)
    }
}
