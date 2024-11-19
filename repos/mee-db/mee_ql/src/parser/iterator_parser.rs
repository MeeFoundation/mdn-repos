use super::parser::{Parser, ParserList};
use super::*;
use crate::error::*;
use std::collections::HashSet;
use tree_sitter::Node;

pub struct IteratorStmtParser;
impl Parser<MeeNode<IteratorStmt>> for IteratorStmtParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<IteratorStmt>> {
        let item_node = get_child_by_field_name(node, "item", source_text)?;
        let mut item = node_text(&item_node, source_text)?;

        let source_node = get_child_by_field_name(node, "source", source_text)?;

        let source = parser_list
            .source
            .parse(source_text, source_node, parser_list, ctx)?;

        if source.expected_type == Some(NodeTypes::Users) {
            item = item.with_type(NodeTypes::AbsolutePath);
        } else {
            item = item.with_optional_type(source.expected_type.clone());
        }

        ctx.insert(
            item.value.to_string(),
            mee_node(
                &item_node,
                Expression::Link(mee_node(&item_node, Path::new(item.value.clone()))),
            )
            .with_optional_type(item.expected_type.clone()),
        );

        Ok(mee_node(&node, IteratorStmt { item, source }))
    }
}

pub struct SourceParser;
impl Parser<MeeNode<Source>> for SourceParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Source>> {
        match node.kind() {
            "path" => {
                let path = parser_list
                    .path
                    .parse(source_text, node, parser_list, ctx)?;
                let source = mee_node(
                    &node,
                    Source::PathSource(mee_node(&node, path.value).with_type(NodeTypes::Users)),
                )
                .with_type(NodeTypes::Users);
                Ok(source)
            }
            "array" => {
                let array = parser_list
                    .array
                    .parse(source_text, node, parser_list, ctx)?;

                let mut expected_types = HashSet::new();
                for elem in array.iter() {
                    if let Some(t) = elem.expected_type.as_ref() {
                        expected_types.insert(t.clone());
                    }
                }

                let mut source = mee_node(&node, Source::ArraySource(array.into_iter().collect()));
                if expected_types.len() == 1 {
                    source = source.with_type(expected_types.iter().next().unwrap().clone());
                }
                Ok(source)
            }
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!("Unknown source kind: {}", node.kind()),
            )),
        }
    }
}
