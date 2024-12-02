use crate::ast::MeeNode;
use crate::ast::Position;
use crate::error::*;
use tree_sitter::Node;

pub fn unescape(s: &str) -> String {
    match s {
        r#"\\"# => r#"\"#.to_string(),
        r#"\""# => r#"""#.to_string(),
        r#"\/""# => r#"/"#.to_string(),
        r#"\b"# => "\u{0008}".to_string(),
        r#"\f"# => "\u{000C}".to_string(),
        r#"\n"# => "\n".to_string(),
        r#"\r"# => "\r".to_string(),
        r#"\t"# => "\t".to_string(),
        str if str.starts_with(r#"\u"#) => {
            let hex_digits = str.get(2..6).unwrap();
            let unicode_value = u32::from_str_radix(hex_digits, 16).unwrap();
            char::from_u32(unicode_value).unwrap().to_string()
        }
        _ => String::new(),
    }
}

pub fn node_text(node: &Node, source_text: &str) -> Result<MeeNode<String>> {
    //TODO why trim helps?
    Ok(mee_node(
        node,
        source_text[node.byte_range()].trim().to_string(),
    ))
}

pub fn mee_node<T>(node: &Node, inner: T) -> MeeNode<T> {
    MeeNode::new(inner, node.start_byte(), node.end_byte())
}

pub fn get_child_by_field_name<'a>(
    node: Node<'a>,
    field_name: &'a str,
    source_text: &'a str,
) -> Result<Node<'a>> {
    node.child_by_field_name(field_name)
        .ok_or(Error::syntax_error(
            Position(node.byte_range().start, node.byte_range().end),
            source_text,
            format!("Expected child with type: {:?}", field_name),
        ))
}
