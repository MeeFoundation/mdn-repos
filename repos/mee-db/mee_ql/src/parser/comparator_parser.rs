use super::parser::{Parser, ParserList};
use super::*;
use tree_sitter::Node;

pub struct ComparatorParser;
impl Parser<Comparator> for ComparatorParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Comparator, String> {
        let operator_node = node.child(0).ok_or("Expected operator")?;
        let operator = node_text(&operator_node, source_text)?;
        match operator.as_str() {
            "==" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Eq(expr))
            }
            "!=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Ne(expr))
            }
            ">" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Gt(expr))
            }
            "<" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Lt(expr))
            }
            ">=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Ge(expr))
            }
            "<=" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Le(expr))
            }
            "matches" => {
                let right_node = node.child_by_field_name("right").ok_or("Expected right")?;
                let expr = parser_list
                    .expression
                    .parse(source_text, right_node, parser_list)?;
                Ok(Comparator::Matches(expr))
            }
            "exists" => Ok(Comparator::Exists),
            _ => Err(format!(
                "Unknown comparator operator: {}, text: {}",
                operator,
                node_text(&node, source_text)?
            )),
        }
    }
}
