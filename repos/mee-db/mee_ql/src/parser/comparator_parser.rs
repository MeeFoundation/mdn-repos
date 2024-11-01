use super::parser::{Parser, ParserList};
use super::*;
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
    ) -> Result<MeeNode<Comparator>, String> {
        let operator_node = node.child(0).ok_or("Expected operator")?;
        let operator = node_text(&operator_node, source_text)?.value;
        match operator.as_str() {
            "==" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Eq(expr)))
            }
            "!=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                Ok(mee_node(&node, Comparator::Ne(expr)))
            }
            ">" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Gt(expr)).with_type(NodeTypes::Number))
            }
            "<" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Lt(expr)).with_type(NodeTypes::Number))
            }
            ">=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Ge(expr)).with_type(NodeTypes::Number))
            }
            "<=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::Number, source_text)?;
                Ok(mee_node(&node, Comparator::Le(expr)).with_type(NodeTypes::Number))
            }
            "matches" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, right_node, parser_list, ctx)?;
                expr.check_type(&NodeTypes::String, source_text)?;
                Ok(mee_node(&node, Comparator::Matches(expr)).with_type(NodeTypes::String))
            }
            "exists" => Ok(mee_node(&node, Comparator::Exists)),
            _ => Err(format!(
                "Unknown comparator operator: {}, text: {}",
                operator,
                node_text(&node, source_text)?.value
            )),
        }
    }
}
