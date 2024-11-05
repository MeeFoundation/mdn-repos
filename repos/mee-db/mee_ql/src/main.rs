use parser::ASTParserImpl;
pub mod ast;
// mod error;
pub mod parser;
pub mod query_executor;

use std::collections::HashMap;

pub mod execution;

use execution::query_executor;
use mee_storage::json_kv_store;
use std::sync::Arc;

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
            let executor_list = query_executor(store);
            let ctx = HashMap::new();

            let res = executor_list
                .qe
                .execute(
                    Arc::new(source_code.to_string()),
                    Arc::new(ast.clone()),
                    ctx,
                    executor_list.clone(),
                )
                .await;

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

#[cfg(test)]
mod test {
    use super::*;
    use assert_json_diff::assert_json_eq;
    use futures::stream::StreamExt;

    use mee_storage::binary_kv_store::PATH_SEPARATOR;
    use mee_storage::json_kv_store::{new_btree_map_based, JsonStore};
    use mee_storage::json_utils::*;
    use mee_storage::query_el::FieldFilter;
    use serde_json::json;
    use serde_json::Value;

    fn generate_id() -> String {
        uuid::Uuid::now_v7().to_string()
    }

    fn object_key(id: &str) -> String {
        format!("{ID_PREFIX}{id}")
    }

    fn property_key(object_key: &str, property: &str) -> String {
        format!("{object_key}{PATH_SEPARATOR}{property}")
    }

    async fn exec(source_code: &str) -> Result<Value, String> {
        //insert test data
        let db = new_btree_map_based();
        insert_and_get(db.clone(), alice()).await;
        insert_and_get(db.clone(), bob()).await;
        insert_and_get(db.clone(), carol()).await;
        insert_and_get(db.clone(), dan()).await;

        let mut parser = ASTParserImpl::new(source_code.to_string());
        let ast = parser.parse()?;

        let executor_list = query_executor(db.clone());
        let ctx = HashMap::new();

        let res = executor_list
            .qe
            .execute(
                Arc::new(source_code.to_string()),
                Arc::new(ast.clone()),
                ctx,
                executor_list.clone(),
            )
            .await?;

        Ok(res)
    }

    async fn insert_and_get(db: Arc<dyn JsonStore + Send + Sync>, value: Value) -> (String, Value) {
        let id = generate_id();
        db.set(object_key(&id), value.clone()).await.unwrap();
        // let user = db.range(id.clone(), FieldFilter::All).await.unwrap();
        // dbg!(&id, &user);
        let mut new_value = value.clone();
        new_value.x_set_id(&id);
        (id, new_value)
    }

    /* #region test_data */
    fn alice() -> Value {
        json!({
            "name": "Alice",
            "last_name": "Walker",
            "age": 30,
            "email": "awalker@gmail.com",
            "payment_cards": [
                {
                    "holder": "Alice Walker",
                    "number": "1234 5678 9011 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Alice Walker",
                    "number": "9999 5678 9012 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                }
            ]
        })
    }

    fn bob() -> Value {
        json!({
            "name": "Bob",
            "last_name": "Smith",
            "age": 25,
            "email": "sbob@gmail.com",
            "payment_cards": [
            {
                "holder": "Bob Smith",
                "number": "1234 5678 9013 3456",
                "expire": "2023-12-01",
                "cvv": "123",
                "isssuer": "Mastercard",
            },
            {
                "holder": "Bob Smith",
                "number": "9999 5678 9014 3456",
                "expire": "2028-12-01",
                "cvv": "321",
                "isssuer": "Mastercard",
            }
            ]
        })
    }

    fn carol() -> Value {
        json!({
                "name": "Carol",
                "last_name": "Johnson",
                "age": 35,
                "email": "jcarol@gmail.com",
                "payment_cards": [
                {
                    "holder": "Carol Johnson",
                    "number": "1234 5678 9015 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Carol Johnson",
                    "number": "9999 5678 9016 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                }
                ]
        })
    }

    fn dan() -> Value {
        json!({
                "name": "Dan",
                "last_name": "Brown",
                "age": 40,
                "email": "bdan@yahoo.com",
                "payment_cards": [
                {
                    "holder": "Dan Brown",
                    "number": "1234 5678 9017 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Dan Brown",
                    "number": "9999 5678 9018 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                }
                ]
        })
    }

    /* #endregion */

    #[tokio::test]
    async fn test_simple_query() {
        let res = exec(
            r#"
        [
            user.name
            for user in users
        ]
        "#,
        )
        .await
        .unwrap();

        assert_json_eq!(res, json!(["Alice", "Bob", "Carol", "Dan"]));
    }
}
