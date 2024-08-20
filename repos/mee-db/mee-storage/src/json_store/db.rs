use super::support::JsonExt;
use super::{JsonDB, JsonStore, ID_PROPERTY};
use crate::error::Result;
use crate::kv_store::PATH_SEPARATOR;
use serde_json::{Map, Value};
use std::sync::Arc;

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
    format!("{ID_PROPERTY}{id}")
}

fn property_key(object_key: &str, property: &str) -> String {
    format!("{object_key}{PATH_SEPARATOR}{property}")
}

#[async_trait::async_trait]
impl JsonDB for JsonDBImpl {
    async fn insert(&self, value: Value) -> Result<String> {
        let id = self.db.generate_id().await?;
        self.db.set(object_key(&id), value).await?;
        Ok(id)
    }

    async fn find_by_id(
        &self,
        id: String,
        selecting_properties: Vec<String>,
    ) -> Result<Option<Value>> {
        let key = object_key(&id);
        let mut existing_properties = Map::new();
        for prop in selecting_properties.into_iter() {
            if prop == ID_PROPERTY {
                existing_properties.insert(ID_PROPERTY.to_string(), Value::String(id.clone()));
                continue;
            }
            let key = property_key(&key, &prop);
            if let Some(value) = self.db.get(key).await? {
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
        match self.db.get(object_key(&id)).await? {
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

    // fn select(&self, query: super::query::SelectQuery) -> Result<Vec<Value>> {
    //     todo!()
    // }

    // async fn execute_update(&self, query: super::query::UpdateQuery) -> Result<u128> {
    //     todo!()
    // }

    // async fn execute_delete(&self, query: super::query::DeleteQuery) -> Result<u128> {
    //     todo!()
    // }
}

#[cfg(test)]
mod test {
    // use crate::json_store::storage::KVBasedJsonStoreImpl;
    use crate::{json_store::storage::KVBasedJsonStoreImpl, kv_store};
    use assert_json_diff::assert_json_eq;

    use super::*;
    use serde_json::json;
    fn setup() -> JsonDBImpl {
        let store = kv_store::new_btree_map_based();
        let json_store = Arc::new(KVBasedJsonStoreImpl::new(store));
        JsonDBImpl::new(json_store)
    }

    fn alice() -> Value {
        json!({
            "name": "Alice",
            "last_name": "Walker",
            "age": 30,
            "email": "awalker@gmail.com",
            "payment_cards": [
                {
                    "holder": "Alice Walker",
                    "number": "1234 5678 9012 3456",
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
        println!(
            "bob {}",
            bob_value
                .clone()
                .map(|v| serde_json::to_string_pretty(&v).unwrap())
                .unwrap_or_default()
        );
        assert_json_eq!(bob_value, Some(bob));
    }

    #[tokio::test]
    async fn select_object_by_property_value() {
        let db = setup();
        let (alice_id, _) = insert_and_get(&db, alice()).await;
        let (bob_id, bob) = insert_and_get(&db, bob()).await;
        db.delete(alice_id.clone()).await.unwrap();
        let alice_value = db.find_by_id_full(alice_id.clone()).await.unwrap();
        let bob_value = db.find_by_id_full(bob_id.clone()).await.unwrap();

        assert_eq!(alice_value, None);
        println!(
            "bob {}",
            bob_value
                .clone()
                .map(|v| serde_json::to_string_pretty(&v).unwrap())
                .unwrap_or_default()
        );
        assert_json_eq!(bob_value, Some(bob));
    }
}
