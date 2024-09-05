use super::JsonDB;
use crate::binary_kv_store::PATH_SEPARATOR;
use crate::error::Result;
use crate::json_kv_store::{FieldFilter, JsonStore, JsonStream};
use crate::json_utils::JsonExt;
use crate::json_utils::ID_PREFIX;
use crate::json_utils::ID_PROPERTY;
use crate::query_el::SelectQuery;
use async_stream::stream;
use chrono::offset;
use futures::stream::{self, Skip, StreamExt};
use serde_json::{Map, Value};
use std::sync::Arc;
use tracing::field;
pub struct JsonDBImpl {
    db: Arc<dyn JsonStore + Send + Sync>,
}

#[allow(dead_code)]
impl JsonDBImpl {
    pub fn new(db: Arc<dyn JsonStore + Send + Sync>) -> Self {
        Self { db }
    }
}

fn object_key(id: &str) -> String {
    format!("{ID_PREFIX}{id}")
}

fn property_key(object_key: &str, property: &str) -> String {
    format!("{object_key}{PATH_SEPARATOR}{property}")
}

fn generate_id() -> String {
    uuid::Uuid::now_v7().to_string()
}

#[async_trait::async_trait]
impl JsonDB for JsonDBImpl {
    async fn insert(&self, value: Value) -> Result<String> {
        let id = generate_id();
        self.db.set(object_key(&id).clone(), value).await?;
        Ok(id)
    }

    async fn find_by_id(
        &self,
        id: String,
        selecting_properties: Vec<String>,
    ) -> Result<Option<Value>> {
        let key = object_key(&id);
        let mut existing_properties = Map::new();
        for prop in selecting_properties {
            if prop == ID_PROPERTY {
                existing_properties.insert(ID_PROPERTY.to_string(), Value::String(id.clone()));
                continue;
            }
            let key = property_key(&key, &prop);
            if let Some(value) = self.db.get(key, FieldFilter::All).await? {
                existing_properties.insert(prop, value);
            }
        }

        if existing_properties.is_empty() {
            Ok(None)
        } else {
            Ok(Some(Value::Object(existing_properties)))
        }
    }

    async fn find_by_id_full(&self, id: String) -> Result<Option<Value>> {
        match self.db.get(object_key(&id), FieldFilter::All).await? {
            Some(mut value) if value.is_object() => {
                value.x_set_id(&id);
                Ok(Some(value))
            }
            _ => Ok(None),
        }
    }

    async fn delete(&self, id: String) -> Result<()> {
        self.db.delete(object_key(&id)).await
    }

    async fn stream(&self, key: &str, mut query: SelectQuery) -> Result<JsonStream> {
        let field_filter = query.pack_and_get_field_filter()?;
        let stream = self.db.range(key.to_string(), field_filter).await?;
        let limit = query.limit.unwrap_or(usize::MAX);
        let offset = query.offset.unwrap_or(0);
        let flatten = query.flatten;

        let mut stream = stream
            .filter_map(move |v| {
                let query = query.clone();
                async move { query.process(v) }
            })
            .flat_map(move |v: Value| {
                let arr = match v {
                    Value::Array(arr) if flatten => arr,
                    _ => vec![v],
                };
                stream::iter(arr)
            })
            .skip(offset)
            .take(limit);

        Ok(stream.boxed())
    }

    // async fn execute_update(&self, query: super::query::UpdateQuery) -> Result<u128> {
    //     todo!()
    // }

    // async fn execute_delete(&self, query: super::query::DeleteQuery) -> Result<u128> {
    //     todo!()
    // }
}

#[cfg(test)]
mod test {
    use crate::{
        json_kv_store,
        query_el::{CheckOperator::*, Expr::*, Operation::*, WhereClause::*},
    };
    use assert_json_diff::assert_json_eq;
    use futures::FutureExt;

    use super::*;
    use serde_json::json;
    fn setup() -> JsonDBImpl {
        let json_store = json_kv_store::new_btree_map_based();
        JsonDBImpl::new(json_store)
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
    pub fn de_select_query(s: &str) -> SelectQuery {
        serde_json::from_str(s).unwrap()
    }

    /* #endregion */

    async fn insert_and_get(db: &JsonDBImpl, value: Value) -> (String, Value) {
        let id = db.insert(value.clone()).await.unwrap();
        let mut new_value = value.clone();
        new_value.x_set_id(&id);
        (id, new_value)
    }

    #[tokio::test]
    async fn insert_and_read_object_by_id() {
        let db = setup();
        let (alice_id, alice) = insert_and_get(&db, alice()).await;
        let (bob_id, bob) = insert_and_get(&db, bob()).await;

        let alice_value = db.find_by_id_full(alice_id.clone()).await.unwrap();

        let bob_value = db.find_by_id_full(bob_id.clone()).await.unwrap();
        assert_json_eq!(alice_value, Some(alice));
        assert_json_eq!(bob_value, Some(bob));
    }

    #[tokio::test]
    async fn read_selected_properties_by_object_id() {
        let db = setup();
        let (alice_id, _) = insert_and_get(&db, alice()).await;

        let alice_value = db
            .find_by_id(
                alice_id.clone(),
                vec!["name".to_string(), "email".to_string()],
            )
            .await
            .unwrap();

        assert_json_eq!(
            alice_value,
            Some(json!({
                "name": "Alice",
                 "email": "awalker@gmail.com",
            })),
        );
    }

    #[tokio::test]
    async fn delete_object_by_id() {
        let db = setup();
        let (alice_id, _) = insert_and_get(&db, alice()).await;
        let (bob_id, bob) = insert_and_get(&db, bob()).await;
        db.delete(alice_id.clone()).await.unwrap();
        let alice_value = db.find_by_id_full(alice_id.clone()).await.unwrap();
        let bob_value = db.find_by_id_full(bob_id.clone()).await.unwrap();

        assert_eq!(alice_value, None);
        assert_json_eq!(bob_value, Some(bob));
    }

    #[tokio::test]
    async fn select_all() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(r#"{}"#);

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(res, json!([alice, bob, carol, dan]));
    }

    #[tokio::test]
    async fn get_all_payment_cards_of_user() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                    "@name": "Alice",
                    "$select": [
                        { "my_name": "@name" },
                        { "my_upper_name": { "@name": "$upper" } },
                        "@payment_cards"
                    ]
                  }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([
              {
                "my_name": "Alice",
                "my_upper_name": "ALICE",
                "payment_cards": [
                  {
                    "cvv": "123",
                    "expire": "2023-12-01",
                    "holder": "Alice Walker",
                    "isssuer": "Visa",
                    "number": "1234 5678 9011 3456"
                  },
                  {
                    "cvv": "321",
                    "expire": "2028-12-01",
                    "holder": "Alice Walker",
                    "isssuer": "Mastercard",
                    "number": "9999 5678 9012 3456"
                  }
                ]
              }
            ])
        );
    }

    #[tokio::test]
    async fn get_alice_payment_card_by_number() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "$derive" : {
                    "my_card" : {
                        "@payment_cards" : {
                            "$find": {
                                    "@number": "9999 5678 9012 3456"
                                }
                            }
                    }
                },
                "@name": "Alice",
                "@my_card": "$exists",
                "$select": [
                    "@name",
                    "@my_card"
                ]
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([{
                "name": "Alice",
                "my_card": {
                "cvv": "321",
                "expire": "2028-12-01",
                "holder": "Alice Walker",
                "isssuer": "Mastercard",
                "number": "9999 5678 9012 3456"
                }
            }])
        );
    }

    #[tokio::test]
    async fn get_user_with_lastname_in_email() {
        let db = setup();
        let (_, mut alice) = insert_and_get(&db, alice()).await;
        let (_, _) = insert_and_get(&db, bob()).await;
        let (_, _) = insert_and_get(&db, carol()).await;
        let (_, _) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "$derive" : {
                    "upper_last_name" : {"@last_name" : "$upper" },
                    "upper_email" : {"@email" : "$upper" }
                },
                "@upper_email" : {"$contains": "@upper_last_name" }
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([alice.x_merge(
                json!({"upper_last_name": "WALKER", "upper_email": "AWALKER@GMAIL.COM"})
            )])
        );
    }

    #[tokio::test]
    async fn get_all_users_over_30() {
        let db = setup();
        let (_, _) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "@age": {"$gt": 30}
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(res, json!([carol, dan]));
    }

    #[tokio::test]
    async fn get_all_card_numbers() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "$select" : [
                    {"": "@payment_cards/*/number"}
                ]
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([
                "1234 5678 9011 3456",
                "9999 5678 9012 3456",
                "1234 5678 9013 3456",
                "9999 5678 9014 3456",
                "1234 5678 9015 3456",
                "9999 5678 9016 3456",
                "1234 5678 9017 3456",
                "9999 5678 9018 3456"
            ])
        );
    }

    #[tokio::test]
    async fn get_all_card_numbers_non_flatten() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "$select" : [
                    {"": "@payment_cards/*/number"}
                ],
                "$flatten": false
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([
                ["1234 5678 9011 3456", "9999 5678 9012 3456"],
                ["1234 5678 9013 3456", "9999 5678 9014 3456"],
                ["1234 5678 9015 3456", "9999 5678 9016 3456"],
                ["1234 5678 9017 3456", "9999 5678 9018 3456"]
            ])
        );
    }

    #[tokio::test]
    async fn get_all_visa_card_numbers() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "$derive":{
                    "cards" : {
                        "@payment_cards": {
                            "$filter": { "@isssuer": "Visa" } 
                        }
                    }
                },
                "$select" : [
                    {"":"@cards/*/number"}
                ]
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([
                "1234 5678 9011 3456",
                "1234 5678 9015 3456",
                "1234 5678 9017 3456",
            ])
        );
    }

    #[tokio::test]
    async fn get_as_new_struct() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = de_select_query(
            r#"{
                "@name": "Alice",
                "$select" : [
                    {"user/name":"@name"},
                    {"user/last_name":"@last_name"},
                    {"user/age":"@age"},
                    {"user/email":"@email"},
                    {"payment_cards_numbers":"@payment_cards/*/number"}
                ]
            }"#,
        );

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([{
                "payment_cards_numbers": [
                    "1234 5678 9011 3456",
                    "9999 5678 9012 3456"
                ],
                "user": {
                    "age": 30,
                    "email": "awalker@gmail.com",
                    "last_name": "Walker",
                    "name": "Alice"
                }
            }])
        );
    }
}
