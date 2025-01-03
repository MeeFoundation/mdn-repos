use super::*;
use crate::error::*;
use crate::execution::ExecutorList;
use crate::json_kv_store;
use crate::parser::ASTParserImpl;
use crate::query_executor;
use mee_storage::json_kv_store::binary_store::BinaryStore;
use mee_storage::json_kv_store::Store;

use serde_json::Value;
use std::sync::Arc;

#[allow(unused)]
use serde_json::json;

use futures::future::try_join_all;

pub type DB = Arc<dyn QueryExecutor + Send + Sync>;

#[async_trait::async_trait]
pub trait QueryExecutor {
    async fn execute(&self, source_code: String) -> Result<Value>;

    async fn insert_many(&self, values: Vec<Value>) -> Result<Vec<String>>;
}

pub struct QueryExecutorImpl {
    store: Store,
    executor_list: Arc<ExecutorList>,
}

impl QueryExecutorImpl {
    pub fn new_btree_map_based(binary_store: BinaryStore) -> DB {
        let store = json_kv_store::new(binary_store);
        Arc::new(Self {
            store: store.clone(),
            executor_list: query_executor(store),
        })
    }
}

#[async_trait::async_trait]
impl QueryExecutor for QueryExecutorImpl {
    async fn execute(&self, source_code: String) -> Result<Value> {
        let ast = {
            let mut parser = ASTParserImpl::new(source_code.clone());
            parser.parse()?
        };

        let mut ctx = HashMap::new();

        let executor_list = self.executor_list.clone();

        let res = executor_list
            .qe
            .execute(
                Arc::new(source_code),
                Arc::new(ast.clone()),
                &mut ctx,
                executor_list.clone(),
            )
            .await?;

        Ok(res)
    }

    async fn insert_many(&self, values: Vec<Value>) -> Result<Vec<String>> {
        let futures = values.into_iter().map(|v| self.store.insert(v));
        let ids = try_join_all(futures).await?;
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
            "birth_date": "1993-05-15",
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
            "birth_date": "1998-05-15",
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
                "birth_date": "1995-05-15",
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
                "birth_date": "1996-05-15",
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
        let binary_store = mock_binary_kv_store::new_btree_map_based();
        let qe = QueryExecutorImpl::new_btree_map_based(binary_store);
        qe.insert_many(vec![alice(), bob(), carol(), dan()])
            .await
            .unwrap();
        qe
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
        qe.execute(
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

    #[tokio::test]
    async fn test_after() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"[user.name for user in users if user.birth_date after "1998-05-14"]"#
                    .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Bob"]));
    }

    #[tokio::test]
    async fn test_before() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"[user.name for user in users if user.birth_date before "1993-05-16"]"#
                    .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Alice"]));
    }

    #[tokio::test]
    async fn test_between() {
        let qe = setup().await;
        let res = qe
            .execute(
                r#"[user.name for user in users if user.birth_date between "1993-05-15" and "1996-05-15"]"#
                    .to_string(),
            )
            .await
            .unwrap();
        assert_eq!(res, json!(["Alice", "Carol"]));
    }

    #[tokio::test]
    async fn test_contains() {
        let qe = setup().await;
        let res = qe
            .execute(r#"[user.name for user in users if [card.number for card in user.payment_cards] contains "9999 5678 9014 3456"]"#.to_string())
            .await
            .unwrap();
        assert_eq!(res, json!(["Bob"]));
    }

    #[tokio::test]
    async fn test_append_one() {
        let qe = setup().await;
        qe.execute(
            r#"[user.id for user in users if user.name == "Bob" append user.payment_cards 
        {
                    "holder": "Bob Smith",
                    "number": "1234 1234 1234 1234",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard"
                }]"#
            .to_string(),
        )
        .await
        .unwrap();
        let res = qe
            .execute(r#"[card.number for user in users if user.name == "Bob" for card in user.payment_cards]"#.to_string())
            .await
            .unwrap();
        assert_eq!(
            res,
            json!([
                "1234 5678 9013 3456",
                "9999 5678 9014 3456",
                "1234 1234 1234 1234"
            ])
        );
    }

    #[tokio::test]
    async fn test_append_many() {
        let qe = setup().await;
        qe.execute(
            r#"[for user in users if user.name == "Bob" append user.payment_cards values [
        {
                    "holder": "Bob Smith",
                    "number": "1234 1234 1234 1234",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard"
                },
                {
                    "holder": "Bob Smith",
                    "number": "1234 1234 1234 1235",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard"
                }]
                ]"#
            .to_string(),
        )
        .await
        .unwrap();
        let res = qe
            .execute(r#"[card.number for user in users if user.name == "Bob" for card in user.payment_cards]"#.to_string())
            .await
            .unwrap();
        assert_eq!(
            res,
            json!([
                "1234 5678 9013 3456",
                "9999 5678 9014 3456",
                "1234 1234 1234 1234",
                "1234 1234 1234 1235"
            ])
        );
    }
}
