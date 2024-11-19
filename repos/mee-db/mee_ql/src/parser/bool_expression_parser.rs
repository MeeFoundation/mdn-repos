use super::parser::{Parser, ParserList};
use super::support::mee_node;
use super::*;
use crate::error::*;
use tree_sitter::Node;

pub struct BoolExpressionParser;
impl Parser<MeeNode<BoolExpression>> for BoolExpressionParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<BoolExpression>> {
        match node.kind() {
            "comparison" => {
                let val_node = node.child_by_field_name("val").ok_or(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_text,
                    "Expected val",
                ))?;
                dbg!(&val_node);
                let val = parser_list
                    .value
                    .parse(source_text, val_node, parser_list, ctx)?;

                let comparator_node = get_child_by_field_name(node, "comparator", source_text)?;

                let comparator =
                    parser_list
                        .comparator
                        .parse(source_text, comparator_node, parser_list, ctx)?;

                val.check_optional_type(&comparator.expected_type, source_text)?;

                Ok(
                    mee_node(&node, BoolExpression::Comparison { val, comparator })
                        .with_type(NodeTypes::Bool),
                )
            }
            "and_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr =
                        parser_list
                            .bool_expression
                            .parse(source_text, child, parser_list, ctx)?;
                    expressions.push(expr);
                }
                Ok(mee_node(&node, BoolExpression::And(expressions)).with_type(NodeTypes::Bool))
            }
            "or_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr =
                        parser_list
                            .bool_expression
                            .parse(source_text, child, parser_list, ctx)?;
                    expressions.push(expr);
                }
                Ok(mee_node(&node, BoolExpression::Or(expressions)).with_type(NodeTypes::Bool))
            }
            "not_expression" => {
                let operand_node = node.child(1).ok_or(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_text,
                    "Expected operand",
                ))?;
                let expr = parser_list.bool_expression.parse(
                    source_text,
                    operand_node,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, BoolExpression::Not(Box::new(expr))).with_type(NodeTypes::Bool))
            }
            "true" => Ok(mee_node(&node, BoolExpression::True).with_type(NodeTypes::Bool)),
            "false" => Ok(mee_node(&node, BoolExpression::False).with_type(NodeTypes::Bool)),
            "path" => {
                let path = parser_list
                    .path
                    .parse(source_text, node, parser_list, ctx)?;
                path.check_type(&NodeTypes::Bool, source_text)?;
                let expr = path.map(|p| Expression::Link(mee_node(&node, p.clone())));
                Ok(mee_node(&node, BoolExpression::Expression(expr)).with_type(NodeTypes::Bool))
            }
            "(" => {
                let next_sibling = node.next_sibling().ok_or(Error::syntax_error(
                    Position(node.byte_range().start, node.byte_range().end),
                    source_text,
                    "Expected next sibling",
                ))?;
                parser_list
                    .bool_expression
                    .parse(source_text, next_sibling, parser_list, ctx)
            }
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!(
                    "Unknown bool expression: {}",
                    node_text(&node, source_text)?.value
                ),
            )),
        }
    }
}
