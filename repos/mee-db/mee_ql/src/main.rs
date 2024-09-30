// mod bindings;
mod ast;
use tree_sitter::{InputEdit, Language, Parser, Point};
use tree_sitter_mee_ql;

fn main() {
    let mut parser = Parser::new();

    let language = tree_sitter_mee_ql::LANGUAGE;
    parser
        .set_language(&language.into())
        .expect("Error loading MeeQl parser");

    let source_code = "[ for item in source limit 10 ]";

    // let source_code = "fn test() {}";
    let tree = parser.parse(source_code, None).unwrap();

    println!("{:?}", tree.root_node().to_sexp());

    let ast = ast::parse_query(tree.root_node());

    println!("{:?}", ast);
}
