use super::parser::{Parser, ParserList};
use super::*;
use std::collections::HashMap;
use tree_sitter::Node;

pub struct PathParser;
impl Parser<Path> for PathParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Path, String> {
        let mut segments = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "ident" {
                segments.push(parser_list.ident.parse(source_text, child, parser_list)?);
            }
        }
        Ok(Path(segments))
    }
}

pub struct PosIntParser;
impl Parser<usize> for PosIntParser {
    fn parse(&self, source_text: &str, node: Node, _: &ParserList) -> Result<usize, String> {
        let text = node_text(&node, source_text)?;
        let number = text.parse::<usize>().map_err(|e| e.to_string())?;
        Ok(number)
    }
}

pub struct ArrayParser;
impl Parser<Vec<Value>> for ArrayParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Vec<Value>, String> {
        let mut values = Vec::new();
        for child in node.named_children(&mut node.walk()) {
            values.push(parser_list.value.parse(source_text, child, parser_list)?);
        }
        Ok(values)
    }
}

pub struct ObjectParser;
impl Parser<HashMap<String, Value>> for ObjectParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<HashMap<String, Value>, String> {
        let mut pairs = HashMap::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "pair" {
                let key = parser_list.string.parse(
                    source_text,
                    child.child_by_field_name("key").ok_or("Expected key")?,
                    parser_list,
                )?;
                let value = parser_list.value.parse(
                    source_text,
                    child.child_by_field_name("value").ok_or("Expected value")?,
                    parser_list,
                )?;
                pairs.insert(key, value);
            }
        }
        Ok(pairs)
    }
}

pub struct ValueParser;
impl Parser<Value> for ValueParser {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
    ) -> Result<Value, String> {
        match node.kind() {
            "path" => {
                let path = parser_list.path.parse(source_text, node, parser_list)?;
                Ok(Value::Path(path))
            }
            "object" => {
                let object = parser_list.object.parse(source_text, node, parser_list)?;
                Ok(Value::Object(object))
            }
            "array" => {
                let array = parser_list.array.parse(source_text, node, parser_list)?;
                Ok(Value::Array(array))
            }
            "number" => {
                let number = parser_list.number.parse(source_text, node, parser_list)?;
                Ok(Value::Number(number))
            }
            "string" => {
                let string = parser_list.string.parse(source_text, node, parser_list)?;
                Ok(Value::String(string))
            }
            "true" => Ok(Value::Bool(true)),
            "false" => Ok(Value::Bool(false)),
            "null" => Ok(Value::Null),
            _ => Err(format!("Unknown value kind: {}", node.kind())),
        }
    }
}

pub struct IdentParser;
impl Parser<String> for IdentParser {
    fn parse(&self, source_text: &str, node: Node, _: &ParserList) -> Result<String, String> {
        let text = node_text(&node, source_text)?;
        Ok(text)
    }
}

pub struct StringParser;
impl Parser<String> for StringParser {
    fn parse(&self, source_text: &str, node: Node, _: &ParserList) -> Result<String, String> {
        let mut string_content = String::new();
        for child in node.named_children(&mut node.walk()) {
            if child.kind() == "string_content" {
                string_content.push_str(&node_text(&child, source_text)?);
            } else if child.kind() == "escape_sequence" {
                string_content.push_str(&unescape(&node_text(&child, source_text)?));
            }
        }
        Ok(string_content)
    }
}

pub struct NumberParser;
impl Parser<f64> for NumberParser {
    fn parse(&self, source_text: &str, node: Node, _: &ParserList) -> Result<f64, String> {
        let text = node_text(&node, source_text)?;
        let number = text.parse::<f64>().map_err(|e| e.to_string())?;
        Ok(number)
    }
}
