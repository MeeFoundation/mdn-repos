use super::parser::{Parser, ParserList};
use super::*;
use crate::error::*;
use tree_sitter::Node;

pub struct StatementParser;
impl Parser<MeeNode<Statement>> for StatementParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Statement>> {
        match node.kind() {
            "iterator_stmt" => {
                let iterator =
                    parser_list
                        .iterator_stmt
                        .parse(source_text, node, parser_list, ctx)?;
                Ok(mee_node(&node, Statement::Iterator(iterator.value)))
            }
            "assignment" => {
                let var_node = get_child_by_field_name(node, "var", source_text)?;
                // check_node_type(&var_node, "var", source_text)?;
                let key = node_text(&var_node, source_text)?;

                let expr_node = get_child_by_field_name(node, "expr", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, expr_node, parser_list, ctx)?;

                ctx.insert(key.value.to_string(), expr.clone());
                Ok(mee_node(&node, Statement::Assignment((key, expr))))
            }
            "update_stmt" => {
                let field_node = get_child_by_field_name(node, "field", source_text)?;
                let field = parser_list
                    .path
                    .parse(source_text, field_node, parser_list, ctx)?;
                field.check_type(&NodeTypes::AbsolutePath, source_text)?;

                let expr_node = get_child_by_field_name(node, "expr", source_text)?;
                let expr =
                    parser_list
                        .expression
                        .parse(source_text, expr_node, parser_list, ctx)?;
                Ok(mee_node(&node, Statement::Update((field, expr))))
            }
            "append_stmt" => {
                let field_node = get_child_by_field_name(node, "field", source_text)?;
                let field = parser_list
                    .path
                    .parse(source_text, field_node, parser_list, ctx)?;
                field.check_type(&NodeTypes::AbsolutePath, source_text)?;

                if let Ok(expr_node) = get_child_by_field_name(node, "values", source_text) {
                    let expr =
                        parser_list
                            .expression
                            .parse(source_text, expr_node, parser_list, ctx)?;
                    Ok(mee_node(&node, Statement::AppendMany((field, expr))))
                } else {
                    let expr_node = get_child_by_field_name(node, "value", source_text)?;
                    let expr =
                        parser_list
                            .expression
                            .parse(source_text, expr_node, parser_list, ctx)?;
                    let expr = MeeNode::new(
                        Expression::Array(vec![expr]),
                        expr_node.byte_range().start,
                        expr_node.byte_range().end,
                    );
                    Ok(mee_node(&node, Statement::AppendMany((field, expr))))
                }
            }
            "delete_stmt" => {
                let field_node = get_child_by_field_name(node, "field", source_text)?;
                let field = parser_list
                    .path
                    .parse(source_text, field_node, parser_list, ctx)?;
                field.check_type(&NodeTypes::AbsolutePath, source_text)?;
                Ok(mee_node(&node, Statement::Delete(field)))
            }
            "filter_stmt" => {
                let filter_node = get_child_by_field_name(node, "filter", source_text)?;
                let filter = parser_list.bool_expression.parse(
                    source_text,
                    filter_node,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, Statement::Filter(filter)))
            }
            "offset_stmt" => {
                let offset_node = get_child_by_field_name(node, "offset", source_text)?;
                let offset =
                    parser_list
                        .pos_int
                        .parse(source_text, offset_node, parser_list, ctx)?;
                Ok(mee_node(&node, Statement::Offset(offset)))
            }
            "limit_stmt" => {
                let limit_node = get_child_by_field_name(node, "limit", source_text)?;
                let limit = parser_list
                    .pos_int
                    .parse(source_text, limit_node, parser_list, ctx)?;
                Ok(mee_node(&node, Statement::Limit(limit)))
            }
            _ => Err(Error::syntax_error(
                Position(node.byte_range().start, node.byte_range().end),
                source_text,
                format!("Unknown statement kind: {}", node.kind()),
            )),
        }
    }
}
