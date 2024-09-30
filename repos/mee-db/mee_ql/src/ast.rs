#[derive(Debug)]
pub enum Query {
    ArrayQuery(ArrayQuery),
    ElementQuery(ElementQuery),
}

#[derive(Debug)]
pub struct ArrayQuery {
    pub query_body: QueryBody,
}

#[derive(Debug)]
pub struct ElementQuery {
    pub query_body: QueryBody,
}

#[derive(Debug)]
pub struct QueryBody {
    pub iterator: IteratorNode,
    pub assignments: Vec<Assignment>,
    pub conditions: Vec<Condition>,
    pub limit: Option<Limit>,
    pub offset: Option<Offset>,
    pub update_assignment: Option<UpdateAssignment>,
}

#[derive(Debug)]
pub struct IteratorNode {
    pub item: String,
    pub source: Source,
}

#[derive(Debug)]
pub struct Assignment {
    pub var: String,
    pub expr: Expression,
}

#[derive(Debug)]
pub struct UpdateAssignment {
    pub field: Path,
    pub expr: Expression,
}

#[derive(Debug)]
pub enum Expression {
    Value(Value),
    Query(Box<Query>),
}

#[derive(Debug)]
pub enum Source {
    Path(Path),
    FunctionCall(Path),
    Array(Array),
}

#[derive(Debug)]
pub struct Condition {
    pub comparison: Comparison,
}

#[derive(Debug)]
pub struct Comparison {
    pub left: Value,
    pub right: Option<Comparator>,
    pub logical_op: Option<LogicalOp>,
}

#[derive(Debug)]
pub struct Comparator {
    pub op: ComparatorOp,
    pub expr: Option<Expression>,
}

#[derive(Debug)]
pub enum ComparatorOp {
    Equal,
    NotEqual,
    GreaterThan,
    LessThan,
    GreaterOrEqual,
    LessOrEqual,
    Matches,
    Exists,
}

#[derive(Debug)]
pub enum LogicalOp {
    And,
    Or,
}

#[derive(Debug)]
pub struct Limit {
    pub value: u64,
}

#[derive(Debug)]
pub struct Offset {
    pub value: u64,
}

#[derive(Debug)]
pub enum Value {
    Path(Path),
    Object(Object),
    Array(Array),
    Number(f64),
    String(String),
    True,
    False,
    Null,
}

#[derive(Debug)]
pub struct Object {
    pub pairs: Vec<Pair>,
}

#[derive(Debug)]
pub struct Pair {
    pub key: String,
    pub value: Value,
}

#[derive(Debug)]
pub struct Array {
    pub values: Vec<Value>,
}

#[derive(Debug)]
pub struct Path {
    pub segments: Vec<String>,
}

#[derive(Debug)]
pub struct StringLiteral {
    pub content: String,
}

#[derive(Debug)]
pub struct NumberLiteral {
    pub value: f64,
}

#[derive(Debug)]
pub struct Identifier {
    pub name: String,
}

pub fn parse_query(node: tree_sitter::Node) -> Query {
    let node = node.child(0).unwrap();
    let buf = [0; 1024];
    match node.kind() {
        "array_query" => Query::ArrayQuery(parse_array_query(node, &buf)),
        "element_query" => Query::ElementQuery(parse_element_query(node, &buf)),
        _ => panic!("Unexpected query node kind: {}", node.kind()),
    }
}

pub fn parse_array_query(node: tree_sitter::Node, buf: &[u8]) -> ArrayQuery {
    let body_node = node; //.child_by_field_name("query_body").unwrap();
    let query_body = parse_query_body(body_node, buf);
    ArrayQuery { query_body }
}

pub fn parse_element_query(node: tree_sitter::Node, buf: &[u8]) -> ElementQuery {
    let body_node = node.child_by_field_name("query_body").unwrap();
    let query_body = parse_query_body(body_node, buf);
    ElementQuery { query_body }
}

pub fn parse_query_body(node: tree_sitter::Node, buf: &[u8]) -> QueryBody {
    let iterator = parse_iterator(node.child_by_field_name("iterator").unwrap(), buf);
    let assignments = vec![]; // Implement parsing assignments
    let conditions = vec![]; // Implement parsing conditions
    let limit = None; // Implement parsing limit
    let offset = None; // Implement parsing offset
    let update_assignment = None; // Implement parsing update_assignment

    QueryBody {
        iterator,
        assignments,
        conditions,
        limit,
        offset,
        update_assignment,
    }
}

pub fn parse_iterator(node: tree_sitter::Node, buf: &[u8]) -> IteratorNode {
    let item = node
        .child_by_field_name("item")
        .unwrap()
        .utf8_text(buf)
        .unwrap()
        .to_string();
    let source = parse_source(node.child_by_field_name("source").unwrap(), buf);
    IteratorNode { item, source }
}

pub fn parse_source(node: tree_sitter::Node, buf: &[u8]) -> Source {
    match node.kind() {
        "path" => Source::Path(parse_path(node, buf)),
        "function_call" => {
            let path = parse_path(node.child_by_field_name("path").unwrap(), buf);
            Source::FunctionCall(path)
        }
        "array" => Source::Array(parse_array(node, buf)),
        _ => panic!("Unexpected source node kind: {}", node.kind()),
    }
}

pub fn parse_path(node: tree_sitter::Node, buf: &[u8]) -> Path {
    let mut segments = Vec::new();
    for i in 0..node.child_count() {
        let child = node.child(i).unwrap();
        if child.kind() == "ident" {
            segments.push(child.utf8_text(buf).unwrap().to_string());
        }
    }
    Path { segments }
}

pub fn parse_array(node: tree_sitter::Node, buf: &[u8]) -> Array {
    let mut values = Vec::new();
    for i in 0..node.child_count() {
        let child = node.child(i).unwrap();
        if child.kind() == "value" {
            values.push(parse_value(child, buf));
        }
    }
    Array { values }
}

pub fn parse_object(node: tree_sitter::Node, buf: &[u8]) -> Object {
    let mut pairs = Vec::new();
    for i in 0..node.child_count() {
        let child = node.child(i).unwrap();
        if child.kind() == "pair" {
            let key = child
                .child_by_field_name("key")
                .unwrap()
                .utf8_text(buf)
                .unwrap()
                .to_string();
            let value = parse_value(child.child_by_field_name("value").unwrap(), buf);
            pairs.push(Pair { key, value });
        }
    }
    Object { pairs }
}

pub fn parse_value(node: tree_sitter::Node, buf: &[u8]) -> Value {
    match node.kind() {
        "path" => Value::Path(parse_path(node, buf)),
        "object" => Value::Object(parse_object(node, buf)),
        "array" => Value::Array(parse_array(node, buf)),
        "number" => Value::Number(node.utf8_text(buf).unwrap().parse::<f64>().unwrap()),
        "string" => Value::String(parse_string(node, buf)),
        "true" => Value::True,
        "false" => Value::False,
        "null" => Value::Null,
        _ => panic!("Unexpected value node kind: {}", node.kind()),
    }
}

pub fn parse_string(node: tree_sitter::Node, buf: &[u8]) -> String {
    // The string node contains the quotes, so we need to strip them
    let text = node.utf8_text(buf).unwrap();
    text[1..text.len() - 1].to_string() // Remove quotes
}

pub fn parse_comparator(node: tree_sitter::Node, buf: &[u8]) -> Comparator {
    let op = match node
        .child_by_field_name("op")
        .unwrap()
        .utf8_text(buf)
        .unwrap()
    {
        "==" => ComparatorOp::Equal,
        "!=" => ComparatorOp::NotEqual,
        ">" => ComparatorOp::GreaterThan,
        "<" => ComparatorOp::LessThan,
        ">=" => ComparatorOp::GreaterOrEqual,
        "<=" => ComparatorOp::LessOrEqual,
        "matches" => ComparatorOp::Matches,
        "exists" => ComparatorOp::Exists,
        _ => panic!("Unexpected comparator operator"),
    };

    let expr = match node.child_by_field_name("expr") {
        Some(expr_node) => Some(parse_expression(expr_node, buf)),
        None => None,
    };

    Comparator { op, expr }
}

pub fn parse_expression(node: tree_sitter::Node, buf: &[u8]) -> Expression {
    match node.kind() {
        "value" => Expression::Value(parse_value(node, buf)),
        "query" => Expression::Query(Box::new(parse_query(node))),
        _ => panic!("Unexpected expression node kind: {}", node.kind()),
    }
}

pub fn parse_logical_op(node: tree_sitter::Node, buf: &[u8]) -> LogicalOp {
    match node.utf8_text(buf).unwrap() {
        "and" => LogicalOp::And,
        "or" => LogicalOp::Or,
        _ => panic!(
            "Unexpected logical operator: {}",
            node.utf8_text(buf).unwrap()
        ),
    }
}

pub fn parse_condition(node: tree_sitter::Node, buf: &[u8]) -> Condition {
    let comparison_node = node.child_by_field_name("comparison").unwrap();
    let comparison = parse_comparison(comparison_node, buf);
    Condition { comparison }
}

pub fn parse_comparison(node: tree_sitter::Node, buf: &[u8]) -> Comparison {
    let left_value = parse_value(node.child_by_field_name("left").unwrap(), buf);

    let right = match node.child_by_field_name("right") {
        Some(right_node) => Some(parse_comparator(right_node, buf)),
        None => None,
    };

    let logical_op = match node.child_by_field_name("logical_op") {
        Some(logical_node) => Some(parse_logical_op(logical_node, buf)),
        None => None,
    };

    Comparison {
        left: left_value,
        right,
        logical_op,
    }
}

pub fn parse_number(node: tree_sitter::Node, buf: &[u8]) -> f64 {
    node.utf8_text(buf).unwrap().parse::<f64>().unwrap()
}

pub fn parse_limit(node: tree_sitter::Node, buf: &[u8]) -> Limit {
    let value = node
        .child_by_field_name("pos_int")
        .unwrap()
        .utf8_text(buf)
        .unwrap()
        .parse::<u64>()
        .unwrap();
    Limit { value }
}

pub fn parse_offset(node: tree_sitter::Node, buf: &[u8]) -> Offset {
    let value = node
        .child_by_field_name("pos_int")
        .unwrap()
        .utf8_text(buf)
        .unwrap()
        .parse::<u64>()
        .unwrap();
    Offset { value }
}
