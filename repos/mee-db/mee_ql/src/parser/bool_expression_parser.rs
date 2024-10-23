use super::parser::{Parser, ParserList};
use super::{BoolExpression::*, *};
use tree_sitter::Node;

pub struct BoolExpressionParser;
impl Parser<BoolExpression> for BoolExpressionParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<BoolExpression, String> {
        match node.kind() {
            "comparison" => {
                let val_node = node.child_by_field_name("val").ok_or("Expected val")?;
                let val = parser_list
                    .value
                    .parse(source_text, val_node, parser_list)?;

                let comparator_node = node
                    .child_by_field_name("comparator")
                    .ok_or("Expected comparator")?;
                let comparator =
                    parser_list
                        .comparator
                        .parse(source_text, comparator_node, parser_list)?;

                Ok(Comparison { val, comparator })
            }
            "and_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr =
                        parser_list
                            .bool_expression
                            .parse(source_text, child, parser_list)?;
                    expressions.push(expr);
                }
                Ok(And(expressions))
            }
            "or_expression" => {
                let mut expressions = Vec::new();
                for child in node.named_children(&mut node.walk()) {
                    let expr =
                        parser_list
                            .bool_expression
                            .parse(source_text, child, parser_list)?;
                    expressions.push(expr);
                }
                Ok(Or(expressions))
            }
            "not_expression" => {
                let operand_node = node.child(1).ok_or("Expected operand")?;
                let expr =
                    parser_list
                        .bool_expression
                        .parse(source_text, operand_node, parser_list)?;
                Ok(Not(Box::new(expr)))
            }
            "true" => Ok(True),
            "false" => Ok(False),
            "path" => {
                let path = parser_list.path.parse(source_text, node, parser_list)?;
                Ok(BoolPath(path))
            }
            "(" => {
                let next_sibling = node.next_sibling().ok_or("Expected next sibling")?;
                parser_list
                    .bool_expression
                    .parse(source_text, next_sibling, parser_list)
            }
            _ => Err(format!(
                "Unknown bool expression kind: {}. next: {}, text: {}",
                node.kind(),
                node_text(&node.next_sibling().unwrap(), source_text)?,
                node_text(&node, source_text)?
            )),
        }
    }
}
