use super::parser::{Parser, ParserList};
use super::*;
use std::collections::HashMap;
use tree_sitter::Node;

pub struct IteratorStmtParser;
impl Parser<IteratorStmt> for IteratorStmtParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<IteratorStmt, String> {
        let item_node = node.child_by_field_name("item").ok_or("Expected item")?;
        let item = node_text(&item_node, source_text)?;

        let source = parser_list.source.parse(
            source_text,
            node.child_by_field_name("source")
                .ok_or("Expected source")?,
            parser_list,
        )?;

        let mut assignments = HashMap::new();
        for child in node.children_by_field_name("assignments", &mut node.walk()) {
            let key = node_text(
                &child.child_by_field_name("var").ok_or("Expected key")?,
                source_text,
            )?;
            let expr = parser_list.expression.parse(
                source_text,
                child
                    .child_by_field_name("expr")
                    .ok_or("Expected expression")?,
                parser_list,
            )?;
            assignments.insert(key, expr);
        }

        let filter = if let Some(filter_node) = node.child_by_field_name("filter") {
            Some(
                parser_list
                    .bool_expression
                    .parse(source_text, filter_node, parser_list)?,
            )
        } else {
            None
        };

        let offset = if let Some(offset_node) = node.child_by_field_name("offset") {
            Some(
                parser_list
                    .pos_int
                    .parse(source_text, offset_node, parser_list)?,
            )
        } else {
            None
        };

        let limit = if let Some(limit_node) = node.child_by_field_name("limit") {
            Some(
                parser_list
                    .pos_int
                    .parse(source_text, limit_node, parser_list)?,
            )
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
}

pub struct SourceParser;
impl Parser<Source> for SourceParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Source, String> {
        match node.kind() {
            "path" => {
                let path = parser_list.path.parse(source_text, node, parser_list)?;
                Ok(Source::PathSource(path))
            }
            "array" => {
                let array = parser_list.array.parse(source_text, node, parser_list)?;
                Ok(Source::ArraySource(array))
            }
            _ => Err(format!("Unknown source kind: {}", node.kind())),
        }
    }
}
