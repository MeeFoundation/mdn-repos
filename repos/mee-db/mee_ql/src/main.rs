use parser::ASTParserImpl;
mod ast;
// mod error;
mod parser;

use std::collections::HashMap;

mod execution;

use execution::query_executor;
use mee_storage::json_kv_store;

#[tokio::main]
async fn main() -> Result<(), String> {
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
            let executor = query_executor(store);
            let mut ctx = HashMap::new();
            let res = executor.execute(&source_code, &ast, &mut ctx).await;
            // let validator = ValidatorImpl::new();

            // let query = validator.validate_query(ast.value, &mut ctx).unwrap();

            println!("AST: {:?}", ast);

            println!("Result: {:?}", res);
            Ok(())
        }
        Err(e) => {
            eprintln!("Error parsing source code: {}", e);
            Err(e.to_string())
        }
    }
}
