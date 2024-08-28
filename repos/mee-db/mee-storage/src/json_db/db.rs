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
use futures::stream::{Skip, StreamExt};
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

    async fn stream(&self, key: &str, query: SelectQuery) -> Result<JsonStream> {
        let field_filter = query.get_field_filter()?;
        let stream = self.db.range(key.to_string(), field_filter).await?;
        let SelectQuery {
            select_clause,
            where_clause,
            limit,
            offset,
        }: SelectQuery = query;

        let mut stream = stream
            .filter_map(move |v| {
                let where_clause = where_clause.clone();
                let select_clause = select_clause.clone();
                async move {
                    if where_clause.filter(&v) {
                        Some(select_clause.get_value(v))
                    } else {
                        None::<Value>
                    }
                }
            })
            .skip(offset.unwrap_or(0))
            .take(limit.unwrap_or(usize::MAX));

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
        query_el::{
            CheckOperator::*, Expr::*, Operation::*, SelectClauseBuilder, SelectQueryBuilder,
            WhereClause::*,
        },
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
                "number": "1234 567 9012 3456",
                "expire": "2023-12-01",
                "cvv": "123",
                "isssuer": "Mastercard",
            },
            {
                "holder": "Bob Smith",
                "number": "9999 5678 9012 3456",
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
                    "number": "1234 5678 9012 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Carol Johnson",
                    "number": "9999 5678 9013 3456",
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
                    "number": "1234 5678 9015 3456",
                    "expire": "2023-12-01",
                    "cvv": "123",
                    "isssuer": "Visa",
                },
                {
                    "holder": "Dan Brown",
                    "number": "9999 5678 9014 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                }
                ]
        })
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

        let select = SelectQueryBuilder::select_all_fields().build().unwrap();
        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(res, json!([alice, bob, carol, dan]));
    }

    #[tokio::test]
    async fn select_by_property_eq() {
        let db = setup();
        let _ = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let _ = insert_and_get(&db, dan()).await;

        let bob_name = bob.get("name").unwrap();

        let first_payment_card_number =
            format!("payment_cards{PATH_SEPARATOR}0{PATH_SEPARATOR}number");
        let carol_payment_card_number = carol.x_get_property(&first_payment_card_number).unwrap();

        let select_by_name = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(
                Field("name".to_string()),
                Equal(Val(bob_name.clone())),
            ))
            .build()
            .unwrap();

        let select_by_payment_card_number = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(
                Field(first_payment_card_number.clone()),
                Equal(Val(carol_payment_card_number.clone())),
            ))
            .build()
            .unwrap();

        let by_name = db
            .stream("", select_by_name)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        let by_payment_card_number = db
            .stream("", select_by_payment_card_number)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(by_name, json!([bob]));
        assert_json_eq!(by_payment_card_number, json!([carol]));
    }

    #[tokio::test]
    async fn select_by_property_gt() {
        let db = setup();
        let (_, _) = insert_and_get(&db, alice()).await;
        let (_, _) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select_by_age = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(Field("age".to_string()), GreaterThan(Val(json!(30)))))
            .build()
            .unwrap();

        let res = db
            .stream("", select_by_age)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(res, json!([carol, dan]));
    }

    #[tokio::test]
    async fn select_by_property_lt() {
        let db = setup();
        let _ = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let _ = insert_and_get(&db, carol()).await;
        let _ = insert_and_get(&db, dan()).await;

        let select_by_age = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(Field("age".to_string()), LessThan(Val(json!(30)))))
            .build()
            .unwrap();

        let res = db
            .stream("", select_by_age)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        dbg!(&res);
        assert_json_eq!(res, json!([bob]));
    }

    #[tokio::test]
    async fn select_all_names() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select = SelectQueryBuilder::select(
            SelectClauseBuilder::new()
                .add_field_as(Field("name".to_string()), "".to_string())
                .build(),
        )
        .build()
        .unwrap();

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(
            res,
            json!([
                alice.get("name"),
                bob.get("name"),
                carol.get("name"),
                dan.get("name")
            ])
        );
    }

    #[tokio::test]
    async fn select_by_value_of_embedded_array() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;
        let (_, bob) = insert_and_get(&db, bob()).await;
        let (_, carol) = insert_and_get(&db, carol()).await;
        let (_, dan) = insert_and_get(&db, dan()).await;

        let select_visa = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(
                Field(format!(
                    "payment_cards{PATH_SEPARATOR}*{PATH_SEPARATOR}isssuer"
                )),
                Contains(Val(json!("Visa"))),
            ))
            .build()
            .unwrap();

        let select_not_visa = SelectQueryBuilder::select_all_fields()
            .where_clause(Check(
                Field(format!(
                    "payment_cards{PATH_SEPARATOR}*{PATH_SEPARATOR}isssuer"
                )),
                NotContains(Val(json!("Visa"))),
            ))
            .build()
            .unwrap();

        let res_visa = db
            .stream("", select_visa)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;
        let res_not_visa = db
            .stream("", select_not_visa)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        assert_json_eq!(res_visa, json!([alice, carol, dan]));
        assert_json_eq!(res_not_visa, json!([bob]));
    }

    #[tokio::test]
    async fn select_value_from_embedded_array() {
        let db = setup();
        let (_, alice) = insert_and_get(&db, alice()).await;

        let select_clause = SelectClauseBuilder::new()
            .add_field_as(
                Operation {
                    op: First,
                    ex: Box::new(Field(format!(
                        "payment_cards{PATH_SEPARATOR}*{PATH_SEPARATOR}number"
                    ))),
                },
                "card_number".to_string(),
            )
            .add_field(Field("name".to_string()))
            .add_field_as(
                Operation {
                    op: First,
                    ex: Box::new(Field(format!(
                        "payment_cards{PATH_SEPARATOR}*{PATH_SEPARATOR}isssuer"
                    ))),
                },
                "isssuer".to_string(),
            )
            .build()
            .pack();

        let select = SelectQueryBuilder::select(select_clause).build().unwrap();

        let res = db
            .stream("", select)
            .await
            .unwrap()
            .collect::<Vec<_>>()
            .await;

        println!("!!!! {}", serde_json::to_string_pretty(&res).unwrap());

        assert_json_eq!(
            res,
            json!([{
                "name": "Alice",
                "card_number": "1234 5678 9011 3456",
                "isssuer": "Visa"
            }])
        );
    }
}
