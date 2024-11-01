use super::parser::{Parser, ParserList};
use super::*;
use std::collections::HashMap;
use tree_sitter::Node;

pub struct QueryParser;
impl QueryParser {
    fn parse_query_body(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Query>, String> {
        let query_type = match node.kind() {
            "array_query" => QueryType::All,
            "element_query" => QueryType::FirstOrNull,
            _ => return Err(format!("Unknown query kind: {}", node.kind())),
        };

        let mut iterators = Vec::new();
        for child in node.children_by_field_name("iterators", &mut node.walk()) {
            iterators.push(parser_list.iterator_stmt.parse(
                source_text,
                child,
                parser_list,
                ctx,
            )?);
        }

        let mut updates = HashMap::new();
        for child in node.children_by_field_name("updates", &mut node.walk()) {
            let path = parser_list.path.parse(
                source_text,
                child.child_by_field_name("field").ok_or("Expected path")?,
                parser_list,
                ctx,
            )?;
            path.check_type(&NodeTypes::AbsolutePath, source_text)?;
            let expr = parser_list.expression.parse(
                source_text,
                child.child_by_field_name("expr").ok_or("Expected expr")?,
                parser_list,
                ctx,
            )?;
            updates.insert(path, expr);
        }

        let deletes = parser_list
            .delete_stmt
            .parse(source_text, node, parser_list, ctx)?;

        if iterators.is_empty() {
            return Err("Expected at least one iterator".to_string());
        }

        let result = node
            .child_by_field_name("result")
            .map(|node| parser_list.value.parse(source_text, node, parser_list, ctx))
            .transpose()?;

        Ok(mee_node(
            &node,
            Query {
                result,
                main_iterator: iterators.remove(0),
                embedded_iterators: iterators,
                updates,
                deletes,
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
    ) -> Result<MeeNode<Query>, String> {
        self.parse_query_body(source_text, node, parser_list, ctx)
    }
}

pub struct DeleteStmtParser;
impl Parser<MeeNode<DeleteStmt>> for DeleteStmtParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<DeleteStmt>, String> {
        let mut deletes = Vec::new();
        for child in node.children_by_field_name("deletes", &mut node.walk()) {
            if let Some(path_node) = child.child_by_field_name("field") {
                let path = parser_list
                    .path
                    .parse(source_text, path_node, parser_list, ctx)?;
                path.check_type(&NodeTypes::AbsolutePath, source_text)?;
                deletes.push(path);
            } else {
                return Ok(mee_node(&node, DeleteStmt::All));
            }
        }
        if deletes.is_empty() {
            Ok(mee_node(&node, DeleteStmt::None))
        } else {
            Ok(mee_node(&node, DeleteStmt::Paths(deletes)))
        }
    }
}
