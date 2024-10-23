use parser::ASTParserImpl;
mod ast;
// mod error;
mod parser;
mod visitable;
mod visitor;
// mod _visitor;
mod evalator;
mod logic;

fn main() {
    let source_code = r#"
       [
  user
  for user in users() if user.id == "534622344"
]
    "#;

    let mut parser = ASTParserImpl::new(source_code.to_string());
    match parser.parse() {
        Ok(ast) => {
            let mut evaluator = Evaluator::new(ast);

            // Execute query
            match evaluator.visit_query(&ast) {
                Ok(result) => println!("Result: {:?}", result),
                Err(e) => eprintln!("Error: {:?}", e),
            }
        }
        Err(e) => {
            eprintln!("Error parsing source code: {}", e);
        }
    }
}
