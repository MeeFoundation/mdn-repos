use parser::ASTBuilder;
use tree_sitter::Parser;
mod ast;
mod error;
mod parser;
mod visitor;
// mod _visitor;

// Импортируем сгенерированный модуль языка, например, `tree_sitter_mee_ql`

fn main() {
    // Инициализируем парсер

    // Пример кода MeeQL для парсинга
    let source_code = r#"
       [
  user
  for user in users() if user.id == "534622344"
]
    "#;

    let mut builder = ASTBuilder::new(source_code.to_string());
    match builder.parse() {
        Ok(ast) => {
            println!("Parsed AST: {:#?}", ast);
            // Далее вы можете использовать посетителей для обработки AST
        }
        Err(e) => {
            eprintln!("Error parsing source code: {}", e);
        }
    }

    // // Парсим код и получаем синтаксическое дерево
    // let tree = parser
    //     .parse(source_code, None)
    //     .expect("Failed to parse code");
    // let root_node = tree.root_node();
    // println!("{:#?}", root_node.to_sexp());

    // let mut visitor = Visitor::new();

    // let ast = visitor.visit(root_node, source_code);
    // println!("{:#?}", ast);
}
