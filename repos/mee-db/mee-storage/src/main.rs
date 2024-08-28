// #![feature(return_position_impl_trait_in_trait)]
// #![feature(type_alias_impl_trait)]
#![allow(unused)]

mod binary_kv_store;
mod error;
mod json_db;
mod json_kv_store;
mod json_utils;
mod query_el;
// mod schema;

// use error::{Error, Result};
// use serde_json::Value;
// use storage::Storage;
// use storage::StorageBTreeMapImpl;

use crate::json_utils::JsonExt;
use futures::stream::StreamExt;
use json_db::JsonDB;
use query_el::{
    CheckOperator::{self, *},
    Expr::{self, *},
    Operation::*,
    SelectClause, SelectClauseBuilder, SelectQueryBuilder,
    WhereClause::*,
};
use serde_json::{json, Value};
use std::sync::Arc;
// use tokio_stream::StreamExt;

#[tokio::main]
async fn main() {
    let db = json_db::new_btree_map_based();
    // let db = db.as_ref();
    let (_, alice) = insert_and_get(db.clone(), alice()).await;
    let (_, bob) = insert_and_get(db.clone(), bob()).await;
    let (_, carol) = insert_and_get(db.clone(), carol()).await;
    let (_, dan) = insert_and_get(db.clone(), dan()).await;

    // select_all(db.clone()).await;
    // get_people_over_30(db.clone()).await;
    // get_alice_payment_cards(db.clone()).await;
    get_alice_payment_card_by_number(db.clone()).await;
    // select_names_and_age(db.clone()).await;
    // select_payment_card_numbers(db.clone()).await;
    // select_by_prop(db.clone()).await;
}

async fn get_people_over_30(db: Arc<dyn JsonDB>) {
    let select = SelectQueryBuilder::select_all_fields()
        .where_clause(Check(Field("age".to_string()), GreaterThan(Val(json!(30)))))
        .build()
        .unwrap();

    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
}

async fn get_alice_payment_card_by_number(db: Arc<dyn JsonDB>) {
    let select = SelectQueryBuilder::select(
        SelectClauseBuilder::new()
            .add_field_as(Field("name".to_string()), "ee/fdter/gf".to_string())
            .add_field_as(Field("payment_cards/1".to_string()), "my_card".to_string())
            .build(),
    )
    .where_clause(
        Check(Field("name".to_string()), Equal(Val(json!("Alice")))).and(Check(
            Field("payment_cards/1/number".to_string()),
            Equal(Val(json!("9999 5678 9012 3456"))),
        )),
    )
    .build()
    .unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
}

async fn get_alice_payment_cards(db: Arc<dyn JsonDB>) {
    let select = SelectQueryBuilder::select(
        SelectClauseBuilder::new()
            .add_field(Field("name".to_string()))
            .add_field(Field("payment_cards".to_string()))
            .build(),
    )
    .where_clause(Check(Field("name".to_string()), Equal(Val(json!("Alice")))))
    .build()
    .unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
}

async fn select_all(db: Arc<dyn JsonDB>) {
    println!("<<<Select all<<<");
    let select = SelectQueryBuilder::select_all_fields().build().unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
    println!(">>>Select all>>>");
}

async fn select_names_and_age(db: Arc<dyn JsonDB>) {
    println!("<<<Select names and age<<<");
    let fields = SelectClauseBuilder::new()
        .add_field(Expr::op((Lower), Field("name".to_string())))
        .add_field(Expr::op((Upper), Field("last_name".to_string())))
        .add_field_as(Field("age".to_string()), "years".to_string())
        .build();
    let select = SelectQueryBuilder::select(fields).build().unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
    println!(">>>Select names and age>>>");
}

async fn select_payment_card_numbers(db: Arc<dyn JsonDB>) {
    println!("<<<Select payment card numbers<<<");
    let fields = SelectClauseBuilder::new()
        .add_field(Field("name".to_string()))
        .add_field_as(
            Field("payment_cards/0/number".to_string()),
            "number".to_string(),
        )
        .add_field_as(
            Field("payment_cards/0/cvv".to_string()),
            "secret/cvv".to_string(),
        )
        .build();
    let select = SelectQueryBuilder::select(fields).build().unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
    println!(">>>Select payment card numbers>>>");
}

async fn select_by_prop(db: Arc<dyn JsonDB>) {
    println!("<<<select_by<<<");
    let select = SelectQueryBuilder::select_all_fields()
        .where_clause(
            Check(Field("age".to_string()), LessThan(Val(json!(30))))
                .and(Check(Field("name".to_string()), Equal(Val(json!("Alice"))))),
        )
        .build()
        .unwrap();
    let mut stream = db.stream("", select).await.unwrap();

    while let Some(value) = stream.next().await {
        println!("{}", serde_json::to_string_pretty(&value).unwrap());
    }
    println!(">>>select_by>>>");
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
            "isssuer": "Visa",
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

async fn insert_and_get(db: Arc<dyn JsonDB>, value: Value) -> (String, Value) {
    let id = db.insert(value.clone()).await.unwrap();
    let mut new_value = value.clone();
    new_value.x_set_id(&id);
    (id, new_value)
}
