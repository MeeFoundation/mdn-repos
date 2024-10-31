use parser::ASTParserImpl;
mod ast;
// mod error;
mod parser;

use std::collections::HashMap;

// mod execution;

use mee_storage::json_kv_store;

fn main() {
    let source_code = r#"
       [
  user
  for user in users() if user.id == "534622344"
]
    "#;

    let red_text = "This text is red";
    println!("fdf\x1b[31m{}\x1b[0mfdfd", red_text);
    let store = json_kv_store::new_btree_map_based();

    let mut parser = ASTParserImpl::new(source_code.to_string());
    match parser.parse() {
        Ok(ast) => {
            // let validator = ValidatorImpl::new();
            // let mut ctx = HashMap::new();
            // let query = validator.validate_query(ast.value, &mut ctx).unwrap();

            println!("AST: {:?}", ast);
        }
        Err(e) => {
            eprintln!("Error parsing source code: {}", e);
        }
    }
}
