use super::*;
use std::collections::HashMap;
use tree_sitter::Node;

pub trait Parser<T> {
    fn parse(
        &self,
        source_text: &str,
        node: Node,
        parser_list: &ParserList,
        ctx: &mut Context,
    ) -> Result<T, String>;
}

#[allow(unused)]
pub struct ParserList {
    pub query: Box<dyn Parser<MeeNode<Query>>>,
    pub iterator_stmt: Box<dyn Parser<MeeNode<IteratorStmt>>>,
    pub delete_stmt: Box<dyn Parser<MeeNode<DeleteStmt>>>,
    pub value: Box<dyn Parser<MeeNode<Expression>>>,
    pub expression: Box<dyn Parser<MeeNode<Expression>>>,
    pub comparator: Box<dyn Parser<MeeNode<Comparator>>>,
    pub bool_expression: Box<dyn Parser<MeeNode<BoolExpression>>>,
    pub array: Box<dyn Parser<Vec<MeeNode<Expression>>>>,
    pub object: Box<dyn Parser<HashMap<String, MeeNode<Expression>>>>,
    pub path: Box<dyn Parser<MeeNode<Path>>>,
    pub source: Box<dyn Parser<MeeNode<Source>>>,
    pub ident: Box<dyn Parser<String>>,
    pub pos_int: Box<dyn Parser<usize>>,
    pub string: Box<dyn Parser<String>>,
    pub number: Box<dyn Parser<f64>>,
}

impl ParserList {
    pub fn default() -> Self {
        Self {
            query: Box::new(QueryParser),
            iterator_stmt: Box::new(IteratorStmtParser),
            delete_stmt: Box::new(DeleteStmtParser),
            value: Box::new(ValueParser),
            expression: Box::new(ExpressionParser),
            comparator: Box::new(ComparatorParser),
            bool_expression: Box::new(BoolExpressionParser),
            array: Box::new(ArrayParser),
            object: Box::new(ObjectParser),
            path: Box::new(PathParser),
            ident: Box::new(IdentParser),
            pos_int: Box::new(PosIntParser),
            string: Box::new(StringParser),
            source: Box::new(SourceParser),
            number: Box::new(NumberParser),
        }
    }
}
