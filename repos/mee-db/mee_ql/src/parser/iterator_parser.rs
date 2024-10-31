use super::parser::{Parser, ParserList};
use super::*;
use std::collections::{HashMap, HashSet};
use tree_sitter::Node;

pub struct IteratorStmtParser;
impl Parser<MeeNode<IteratorStmt>> for IteratorStmtParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
        source_code: &str,
    ) -> Result<MeeNode<IteratorStmt>, String> {
        let item_node = node.child_by_field_name("item").ok_or("Expected item")?;
        let mut item = node_text(&item_node, source_text)?;

        let source = parser_list.source.parse(
            source_text,
            node.child_by_field_name("source")
                .ok_or("Expected source")?,
            parser_list,
            ctx,
            source_code,
        )?;

        if source.expected_type == Some(NodeTypes::Users) {
            item = item.with_type(NodeTypes::AbsolutePath);
        } else {
            item = item.with_optional_type(source.expected_type.clone());
        }

        ctx.insert(
            item.value.to_string(),
            mee_node(&item_node, Expression::Link(Path::new(item.value.clone())))
                .with_optional_type(item.expected_type.clone()),
        );

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
                ctx,
                source_code,
            )?;
            ctx.insert(key.value.to_string(), expr.clone());
            assignments.insert(key, expr);
        }

        let filter = if let Some(filter_node) = node.child_by_field_name("filter") {
            Some(parser_list.bool_expression.parse(
                source_text,
                filter_node,
                parser_list,
                ctx,
                source_code,
            )?)
        } else {
            None
        };

        let offset = if let Some(offset_node) = node.child_by_field_name("offset") {
            Some(parser_list.pos_int.parse(
                source_text,
                offset_node,
                parser_list,
                ctx,
                source_code,
            )?)
        } else {
            None
        };

        let limit = if let Some(limit_node) = node.child_by_field_name("limit") {
            Some(parser_list.pos_int.parse(
                source_text,
                limit_node,
                parser_list,
                ctx,
                source_code,
            )?)
        } else {
            None
        };

        Ok(mee_node(
            &node,
            IteratorStmt {
                item,
                source,
                assignments,
                filter,
                offset,
                limit,
            },
        ))
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
        source_code: &str,
    ) -> Result<MeeNode<Source>, String> {
        match node.kind() {
            "path" => {
                let path =
                    parser_list
                        .path
                        .parse(source_text, node, parser_list, ctx, source_code)?;
                let source =
                    mee_node(&node, Source::PathSource(path.value)).with_type(NodeTypes::Users);
                Ok(source)
            }
            "array" => {
                let array =
                    parser_list
                        .array
                        .parse(source_text, node, parser_list, ctx, source_code)?;

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
            _ => Err(format!("Unknown source kind: {}", node.kind())),
        }
    }
}
