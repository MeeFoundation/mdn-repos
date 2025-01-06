use super::parser::{Parser, ParserList};
use super::*;
use crate::error::*;
use tree_sitter::Node;

//TODO add checks if comporator supports several types
//For MeeNode<Comparator>.expected_type is the suitable type for the left side of the comparator.
pub struct ComparatorParser;
impl Parser<MeeNode<Comparator>> for ComparatorParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Comparator>> {
        let operator_node = node.child(0).ok_or(Error::syntax_error(
            Position(node.byte_range().start, node.byte_range().end),
            source_text,
            "Expected operator",
        ))?;
        let operator = node_text(&operator_node, source_text)?.value;
        match operator.as_str() {
            "==" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Eq(expr)))
            }
            "!=" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Ne(expr)))
            }
            ">" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Gt(expr)).with_type(NodeTypes::Number))
            }
            "<" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Lt(expr)).with_type(NodeTypes::Number))
            }
            ">=" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Ge(expr)).with_type(NodeTypes::Number))
            }
            "<=" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Le(expr)).with_type(NodeTypes::Number))
            }
            "matches" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::String, source_text)?;
                Ok(mee_node(&node, Comparator::Matches(expr)).with_type(NodeTypes::String))
            }
            "after" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::After(expr)))
            }
            "before" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Before(expr)))
            }
            "between" => {
                let from_node = get_child_by_field_name(node, "from", source_text)?;
                let to_node = get_child_by_field_name(node, "to", source_text)?;
                let from =
                    parser_list
                        .expression
                        .parse(source_text, from_node, parser_list, ctx)?;
                let to = parser_list
                    .expression
                    .parse(source_text, to_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Between(from, to)))
            }
            "contains" => {
                let right_node = get_child_by_field_name(node, "right", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Contains(expr)))
            }
            "exists" => Ok(mee_node(&node, Comparator::Exists)),
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!(
                    "Unknown comparator operator: {}, text: {}",
                    operator,
                    node_text(&node, source_text)?.value
                ),
            )),
        }
    }
}
