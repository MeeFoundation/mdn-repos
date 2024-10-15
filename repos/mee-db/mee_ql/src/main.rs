use parser::ASTParserImpl;
mod ast;
// mod error;
mod parser;
mod visitable;
mod visitor;
// mod _visitor;

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
            println!("Parsed AST: {:#?}", ast);
        }
        Err(e) => {
            eprintln!("Error parsing source code: {}", e);
        }
    }
}
