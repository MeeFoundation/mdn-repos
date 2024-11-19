use super::parser::{Parser, ParserList};
use super::*;
use tree_sitter::Node;

pub struct StatementParser;
impl Parser<MeeNode<Statement>> for StatementParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<MeeNode<Statement>, String> {
        dbg!(&node);
        match node.kind() {
            "iterator_stmt" => {
                let iterator =
                    parser_list
                        .iterator_stmt
                        .parse(source_text, node, parser_list, ctx)?;
                Ok(mee_node(&node, Statement::Iterator(iterator.value)))
            }
            "assignment" => {
                let key = node_text(
                    &node.child_by_field_name("var").ok_or("Expected key")?,
                    source_text,
                )?;
                let expr = parser_list.expression.parse(
                    source_text,
                    node.child_by_field_name("expr")
                        .ok_or("Expected expression")?,
                    parser_list,
                    ctx,
                )?;
                ctx.insert(key.value.to_string(), expr.clone());
                Ok(mee_node(&node, Statement::Assignment((key, expr))))
            }
            "update_stmt" => {
                let field = parser_list.path.parse(
                    source_text,
                    node.child_by_field_name("field").ok_or("Expected field")?,
                    parser_list,
                    ctx,
                )?;
                field.check_type(&NodeTypes::AbsolutePath, source_text)?;
                let expr = parser_list.expression.parse(
                    source_text,
                    node.child_by_field_name("expr")
                        .ok_or("Expected expression")?,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, Statement::Update((field, expr))))
            }
            "delete_stmt" => {
                let field = parser_list.path.parse(
                    source_text,
                    node.child_by_field_name("field").ok_or("Expected field")?,
                    parser_list,
                    ctx,
                )?;
                field.check_type(&NodeTypes::AbsolutePath, source_text)?;
                Ok(mee_node(&node, Statement::Delete(field)))
            }
            "filter_stmt" => {
                let filter = parser_list.bool_expression.parse(
                    source_text,
                    node.child_by_field_name("filter")
                        .ok_or("Expected filter")?,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, Statement::Filter(filter)))
            }
            "offset_stmt" => {
                let offset = parser_list.pos_int.parse(
                    source_text,
                    node.child_by_field_name("offset")
                        .ok_or("Expected offset")?,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, Statement::Offset(offset)))
            }
            "limit_stmt" => {
                let limit = parser_list.pos_int.parse(
                    source_text,
                    node.child_by_field_name("limit").ok_or("Expected limit")?,
                    parser_list,
                    ctx,
                )?;
                Ok(mee_node(&node, Statement::Limit(limit)))
            }
            _ => Err(format!("Unknown statement kind: {}", node.kind())),
        }
    }
}
