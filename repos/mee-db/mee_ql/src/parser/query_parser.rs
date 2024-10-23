use super::parser::{Parser, ParserList};
use super::*;
use std::collections::{HashMap, HashSet};
use tree_sitter::Node;

pub struct QueryParser;
impl QueryParser {
    fn parse_query_body(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<QueryBody, String> {
        let result = node
            .child_by_field_name("result")
            .map(|node| parser_list.value.parse(source_text, node, parser_list))
            .transpose()?;

        let mut iterators = Vec::new();
        for child in node.children_by_field_name("iterators", &mut node.walk()) {
            iterators.push(
                parser_list
                    .iterator_stmt
                    .parse(source_text, child, parser_list)?,
            );
        }

        let mut updates = HashMap::new();
        for child in node.children_by_field_name("updates", &mut node.walk()) {
            let path = parser_list.path.parse(
                source_text,
                child.child_by_field_name("field").ok_or("Expected path")?,
                parser_list,
            )?;
            let expr = parser_list.expression.parse(
                source_text,
                child.child_by_field_name("expr").ok_or("Expected expr")?,
                parser_list,
            )?;
            updates.insert(path, expr);
        }

        let deletes = parser_list
            .delete_stmt
            .parse(source_text, node, parser_list)?;

        if iterators.is_empty() {
            return Err("Expected at least one iterator".to_string());
        }

        Ok(QueryBody {
            result,
            main_iterator: iterators.remove(0),
            embedded_iterators: iterators,
            updates,
            deletes,
        })
    }
}

impl Parser<Query> for QueryParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Query, String> {
        match node.kind() {
            "array_query" => {
                let body = self.parse_query_body(source_text, node, parser_list)?;
                Ok(Query::ArrayQuery { body })
            }
            "element_query" => {
                let body = self.parse_query_body(source_text, node, parser_list)?;
                Ok(Query::ElementQuery { body })
            }
            _ => Err(format!("Unknown query kind: {}", node.kind())),
        }
    }
}

pub struct DeleteStmtParser;
impl Parser<DeleteStmt> for DeleteStmtParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<DeleteStmt, String> {
        let mut deletes = HashSet::new();
        for child in node.children_by_field_name("deletes", &mut node.walk()) {
            if let Some(path_node) = child.child_by_field_name("field") {
                let path = parser_list
                    .path
                    .parse(source_text, path_node, parser_list)?;
                deletes.insert(path);
            } else {
                return Ok(DeleteStmt::All);
            }
        }
        if deletes.is_empty() {
            Ok(DeleteStmt::None)
        } else {
            Ok(DeleteStmt::Paths(deletes))
        }
    }
}
