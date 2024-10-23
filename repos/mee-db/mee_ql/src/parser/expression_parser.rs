use super::parser::{Parser, ParserList};
use super::*;
use tree_sitter::Node;

pub struct ExpressionParser;
impl Parser<Expression> for ExpressionParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Expression, String> {
        match node.kind() {
            "element_query" | "array_query" => {
                let query = parser_list.query.parse(source_text, node, parser_list)?;
                Ok(Expression::Query(Box::new(query)))
            }
            "bool_expression" => {
                let bool_expr =
                    parser_list
                        .bool_expression
                        .parse(source_text, node, parser_list)?;
                Ok(Expression::BoolExpression(Box::new(bool_expr)))
            }
            _ => parser_list
                .value
                .parse(source_text, node, parser_list)
                .map(Expression::Value)
                .or_else(|_| {
                    parser_list
                        .bool_expression
                        .parse(source_text, node, parser_list)
                        .map(|b| Expression::BoolExpression(Box::new(b)))
                }),
        }
    }
}
