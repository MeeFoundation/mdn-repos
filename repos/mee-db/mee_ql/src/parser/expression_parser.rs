use super::parser::{Parser, ParserList};
use super::*;
use crate::error::*;
use std::collections::HashMap;
use tree_sitter::Node;

pub struct ExpressionParser;
impl Parser<MeeNode<Expression>> for ExpressionParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Expression>> {
        match node.kind() {
            "element_query" | "array_query" => {
                let query = parser_list
                    .query
                    .parse(source_text, node, parser_list, ctx)?;

                let expected_type = query
                    .value
                    .result
                    .as_ref()
                    .and_then(|r| r.expected_type.clone());

                Ok(MeeNode::new(
                    Expression::Query(Box::new(query)),
                    node.start_byte(),
                    node.end_byte(),
                )
                .with_optional_type(expected_type))
            }
            "bool_expression" => {
                let bool_expr =
                    parser_list
                        .bool_expression
                        .parse(source_text, node, parser_list, ctx)?;
                Ok(MeeNode::new(
                    Expression::BoolExpression(Box::new(bool_expr)),
                    node.start_byte(),
                    node.end_byte(),
                )
                .with_type(NodeTypes::Bool))
            }
            _ => parser_list
                .value
                .parse(source_text, node, parser_list, ctx)
                .or_else(|_| {
                    parser_list
                        .bool_expression
                        .parse(source_text, node, parser_list, ctx)
                        .map(|b| {
                            MeeNode::new(
                                Expression::BoolExpression(Box::new(b)),
                                node.start_byte(),
                                node.end_byte(),
                            )
                            .with_type(NodeTypes::Bool)
                        })
                }),
        }
    }
}

pub struct PathParser;
impl Parser<MeeNode<Path>> for PathParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Path>> {
        let mut segments = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "ident" {
                segments.push(
                    parser_list
                        .ident
                        .parse(source_text, child, parser_list, ctx)?,
                );
            }
        }

        let path = Path::new(segments.join("."));
        if path.root == ROOT_PATH {
            return Ok(MeeNode::new(path, node.start_byte(), node.end_byte())
                .with_optional_type(Some(NodeTypes::Users)));
        }
        if let Some(value_node) = ctx.get(&path.root) {
            Ok(MeeNode::new(path, node.start_byte(), node.end_byte())
                .with_optional_type(value_node.expected_type.clone()))
        } else {
            Err(Error::validation_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!("Path not found: {}", path.root),
            ))
        }
    }
}

pub struct PosIntParser;
impl Parser<usize> for PosIntParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        _: &ParserList,
        _: &mut Context,
    ) -> Result<usize> {
        let text = node_text(&node, source_text)?.value;
        let number = text.parse::<usize>().map_err(|_| {
            Error::validation_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                "Expected a positive integer",
            )
        })?;
        Ok(number)
    }
}

pub struct ArrayParser;
impl Parser<Vec<MeeNode<Expression>>> for ArrayParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<Vec<MeeNode<Expression>>> {
        let mut values = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            values.push(
                parser_list
                    .value
                    .parse(source_text, child, parser_list, ctx)?,
            );
        }
        Ok(values)
    }
}

pub struct ObjectParser;
impl Parser<HashMap<String, MeeNode<Expression>>> for ObjectParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<HashMap<String, MeeNode<Expression>>> {
        let mut pairs = HashMap::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "pair" {
                let key_node = get_child_by_field_name(child, "key", source_text)?;
                let key = parser_list
                    .string
                    .parse(source_text, key_node, parser_list, ctx)?;

                let value_node = get_child_by_field_name(child, "value", source_text)?;
                let value = parser_list
                    .value
                    .parse(source_text, value_node, parser_list, ctx)?;
                pairs.insert(key, value);
            }
        }
        Ok(pairs)
    }
}

pub struct ValueParser;
impl Parser<MeeNode<Expression>> for ValueParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Expression>> {
        dbg!(&node.kind(), node_text(&node, source_text)?);
        match node.kind() {
            "path" => {
                let path = parser_list
                    .path
                    .parse(source_text, node, parser_list, ctx)?;

                let inner_value_type = path.expected_type.clone();

                Ok(
                    MeeNode::new(Expression::Link(path), node.start_byte(), node.end_byte())
                        .with_optional_type(inner_value_type),
                )
            }
            "object" => {
                let object = parser_list
                    .object
                    .parse(source_text, node, parser_list, ctx)?;
                Ok(MeeNode::new(
                    Expression::Object(object),
                    node.start_byte(),
                    node.end_byte(),
                )
                .with_type(NodeTypes::Object))
            }
            "array" => {
                let array = parser_list
                    .array
                    .parse(source_text, node, parser_list, ctx)?;
                Ok(
                    MeeNode::new(Expression::Array(array), node.start_byte(), node.end_byte())
                        .with_type(NodeTypes::Array),
                )
            }
            "number" => {
                let number = parser_list
                    .number
                    .parse(source_text, node, parser_list, ctx)?;
                Ok(MeeNode::new(
                    Expression::Number(number),
                    node.start_byte(),
                    node.end_byte(),
                )
                .with_type(NodeTypes::Number))
            }
            "string" => {
                let string = parser_list
                    .string
                    .parse(source_text, node, parser_list, ctx)?;
                Ok(MeeNode::new(
                    Expression::String(string),
                    node.start_byte(),
                    node.end_byte(),
                )
                .with_type(NodeTypes::String))
            }
            "true" => Ok(
                MeeNode::new(Expression::Bool(true), node.start_byte(), node.end_byte())
                    .with_type(NodeTypes::Bool),
            ),
            "false" => {
                Ok(
                    MeeNode::new(Expression::Bool(false), node.start_byte(), node.end_byte())
                        .with_type(NodeTypes::Bool),
                )
            }
            "null" => Ok(MeeNode::new(
                Expression::Null,
                node.start_byte(),
                node.end_byte(),
            )),
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!("Unknown value: {}", node.kind()),
            )),
        }
    }
}

pub struct IdentParser;
impl Parser<String> for IdentParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        _: &ParserList,
        _: &mut Context,
    ) -> Result<String> {
        let text = node_text(&node, source_text)?.value;
        Ok(text)
    }
}

pub struct StringParser;
impl Parser<String> for StringParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        _: &ParserList,
        _: &mut Context,
    ) -> Result<String> {
        let mut string_content = String::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "string_content" {
                string_content.push_str(&node_text(&child, source_text)?.value);
            } else if child.kind() == "escape_sequence" {
                string_content.push_str(&unescape(&node_text(&child, source_text)?.value));
            }
        }
        Ok(string_content)
    }
}

pub struct NumberParser;
impl Parser<f64> for NumberParser {
    fn parse(&self, source_text: &str, node: Node, _: &ParserList, _: &mut Context) -> Result<f64> {
        let text = node_text(&node, source_text)?.value;
        let number = text.parse::<f64>().map_err(|_| {
            Error::validation_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                "Expected a number",
            )
        })?;
        Ok(number)
    }
}
