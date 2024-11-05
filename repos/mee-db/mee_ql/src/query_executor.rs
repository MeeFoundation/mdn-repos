use super::*;
use crate::execution::ExecutorList;
use crate::json_kv_store;
use crate::parser::ASTParserImpl;
use crate::query_executor;
use mee_storage::json_kv_store::{new_btree_map_based, Store};
// use crate::Result;
use futures::stream::StreamExt;
use serde_json::Value;
use std::sync::Arc;

use mee_storage::binary_kv_store::PATH_SEPARATOR;
use mee_storage::json_utils::*;
use mee_storage::query_el::FieldFilter;
use serde_json::json;

pub type DB = Arc<dyn QueryExecutor + Send + Sync>;

fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
}

#[async_trait::async_trait]
pub trait QueryExecutor {
    async fn execute(&self, source_code: String) -> Result<Value, String>;

    async fn insert_many(&self, values: Vec<Value>) -> Result<Vec<String>, String>;
}

pub struct QueryExecutorImpl {
    store: Store,
    executor_list: Arc<ExecutorList>,
}

impl QueryExecutorImpl {
    pub fn new_btree_map_based() -> Self {
        let store = json_kv_store::new_btree_map_based();
        Self {
            store: store.clone(),
            executor_list: query_executor(store),
        }
    }
}

fn generate_id() -> String {
    uuid::Uuid::now_v7().to_string()
}

#[async_trait::async_trait]
impl QueryExecutor for QueryExecutorImpl {
    async fn execute(&self, source_code: String) -> Result<Value, String> {
        let ast = {
            let mut parser = ASTParserImpl::new(source_code.clone());
            parser.parse()?
        };

        let ctx = HashMap::new();

        let executor_list = self.executor_list.clone();

        let res = executor_list
            .qe
            .execute(
                Arc::new(source_code),
                Arc::new(ast.clone()),
                ctx,
                executor_list.clone(),
            )
            .await?;

        Ok(res)
    }

    async fn insert_many(&self, values: Vec<Value>) -> Result<Vec<String>, String> {
        let mut ids = Vec::with_capacity(values.len());

        for v in values.into_iter() {
            let id = generate_id();
            self.store
                .set(object_key(&id).clone(), v)
                .await
                .map_err(|e| e.to_string())?;
            ids.push(id);
        }

        Ok(ids)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

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

    async fn setup() -> DB {
        let qe = QueryExecutorImpl::new_btree_map_based();
        qe.insert_many(vec![alice(), bob(), carol(), dan()])
            .await
            .unwrap();
        Arc::new(qe)
    }

    #[tokio::test]
    async fn test_get_names() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            user.name
            for user in users
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Alice", "Bob", "Carol", "Dan"]));
    }

    #[tokio::test]
    async fn test_get_names_with_filter() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            user.name
            for user in users if user.age > 30
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Carol", "Dan"]));
    }

    #[tokio::test]
    async fn test_get_names_with_filter_and_offset_limit() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            user.name
            for user in users if user.age > 25 offset 1 limit 1
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Carol"]));
    }

    #[tokio::test]
    async fn test_get_age_with_assignments() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            age_field
            for user in users
            name = user.name
            age_field = user.age
            if name == "Carol"
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!([35]));
    }

    #[tokio::test]
    async fn test_get_visa_cards() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            card.number
            for user in users
            for card in user.payment_cards
            if card.isssuer == "Visa"
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(
            res,
            json!([
                "1234 5678 9011 3456",
                "1234 5678 9015 3456",
                "1234 5678 9017 3456"
            ])
        );
    }

    #[tokio::test]
    async fn test_get_users_who_is_older_then_current() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"
        [
            {"name": name, "older": older }
            for user in users
            older = [ user1.name for user1 in users if user1.age > user.age ]
            name = user.name
        ]
        "#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(
            res,
            json!(
              [
                {"name": "Alice", "older": ["Carol", "Dan"]},
                {"name": "Bob", "older": ["Alice", "Carol", "Dan"]},
                {"name": "Carol", "older": ["Dan"]},
                {"name": "Dan", "older": []}
              ]
            )
        );
    }

    #[tokio::test]
    async fn test_find_last_name_by_email_and_name() {
        let qe = setup().await;
        let res = qe
            .execute(r#"[user.last_name for user in users() if user.email == "sbob@gmail.com" and user.name == "Bob"]"#.to_string())
            .await
            .unwrap();
        assert_eq!(res, json!(["Smith"]));
    }

    #[tokio::test]
    async fn test_user_by_card_number() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"[
                {"name" : user.name, "card" : card}
                for user in users()
                for card in user.payment_cards
                if card.number == "9999 5678 9014 3456"
                ]"#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(
            res,
            json!([
                {
                    "name": "Bob",
                    "card": {
                        "cvv": "321",
                        "expire": "2028-12-01",
                        "holder": "Bob Smith",
                        "isssuer": "Mastercard",
                        "number": "9999 5678 9014 3456"
                    }
                }
            ])
        );
    }

    //TODO add date type
    #[tokio::test]
    async fn test_update_name_and_card_issuer() {
        let qe = setup().await;
        qe.execute(
            r#"[
            user
            for user in users if user.name == "Bob"
            for card in user.payment_cards if card.number == "9999 5678 9014 3456"
            set user.name = "Updated Bob"
            set card.isssuer = "Updated Mastercard"
            ]"#
            .to_string(),
        )
        .await
        .unwrap();
        let res = qe
            .execute(
                r#"(
            {"name": name, "cards_issuers": card_issuers}
            for user in users
            name = user.name
            card_issuers = [card.isssuer for card in user.payment_cards]
            if name == "Updated Bob"
            )"#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(
            res,
            json!({"cards_issuers": ["Mastercard", "Updated Mastercard"], "name": "Updated Bob"})
        );
    }

    #[tokio::test]
    async fn test_delete_card() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"[
            user for user in users if user.name == "Bob"
            for card in user.payment_cards if card.number == "9999 5678 9014 3456"
            delete card
            ]"#
                .to_string(),
            )
            .await
            .unwrap();
        let res = qe
            .execute(
                r#"[
            card.number
            for user in users
            if user.name == "Bob"
            for card in user.payment_cards
            ]"#
                .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["1234 5678 9013 3456"]));
    }

    #[tokio::test]
    async fn test_delete_user() {
        let qe = setup().await;
        qe.execute(r#"[user for user in users if user.name == "Bob" delete user]"#.to_string())
            .await
            .unwrap();
        let res = qe
            .execute(r#"[user.name for user in users]"#.to_string())
            .await
            .unwrap();
        assert_eq!(res, json!(["Alice", "Carol", "Dan"]));
    }
}
