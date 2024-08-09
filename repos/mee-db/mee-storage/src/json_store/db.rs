use super::support::JsonExt;
use super::{JsonDB, JsonStore, ID_PROPERTY};
use crate::error::Result;
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

fn object_key(schema: &str, id: &str) -> String {
    format!("{}/{}", schema, id)
}

fn property_key(object_key: &str, property: &str) -> String {
    format!("{}.{}", object_key, property)
}

impl JsonDB for JsonDBImpl {
    fn insert(&self, schema: String, value: Value) -> Result<String> {
        let id = self.db.generate_id()?;
        self.db.set(object_key(&schema, &id), value)?;
        Ok(id)
    }

    fn find_by_id(
        &self,
        schema: String,
        id: String,
        selecting_properties: Vec<String>,
    ) -> Result<Option<Value>> {
        let key = object_key(&schema, &id);
        let mut existing_properties = Map::new();
        for prop in selecting_properties.into_iter() {
            if prop == ID_PROPERTY {
                existing_properties.set_id(&id);
                continue;
            }
            let key = property_key(&key, &prop);
            if let Some(value) = self.db.get(key)? {
                existing_properties.insert(prop, value);
            }
        }

        if existing_properties.is_empty() {
            Ok(None)
        } else {
            Ok(Some(Value::Object(existing_properties)))
        }
    }

    fn find_by_id_full(&self, schema: String, id: String) -> Result<Option<Value>> {
        match self.db.get(object_key(&schema, &id))? {
            Some(mut value) if value.is_object() => {
                value.set_id(&id);
                Ok(Some(value))
            }
            _ => Ok(None),
        }
    }

    fn delete(&self, schema: String, id: String) -> Result<()> {
        self.db.delete(object_key(&schema, &id))
    }

    #[allow(unused)]
    fn find_by_properties_eq(
        &self,
        schema: String,
        filter: Value,
        selecting_properties: Vec<String>,
    ) -> Result<Vec<Value>> {
        todo!()
    }
}

#[cfg(test)]
mod test {
    // use crate::json_store::storage::KVBasedJsonStoreImpl;
    use crate::{json_store::storage::KVBasedJsonStoreImpl, kv_store};

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

    fn insert_and_get(db: &JsonDBImpl, value: Value) -> (String, Value) {
        let id = db.insert(SCHEMA_NAME.to_string(), value.clone()).unwrap();
        let mut new_value = value.clone();
        new_value.set_id(&id);
        (id, new_value)
    }

    const SCHEMA_NAME: &str = "users";

    #[test]
    fn insert_and_read_object_by_id() {
        let db = setup();
        let (alice_id, alice) = insert_and_get(&db, alice());
        let (bob_id, bob) = insert_and_get(&db, bob());

        let alice_value = db
            .find_by_id_full(SCHEMA_NAME.to_string(), alice_id.clone())
            .unwrap();
        let bob_value = db
            .find_by_id_full(SCHEMA_NAME.to_string(), bob_id.clone())
            .unwrap();
        assert_eq!(alice_value, Some(alice));
        assert_eq!(bob_value, Some(bob));
    }

    #[test]
    fn read_selected_properties_by_object_id() {
        let db = setup();
        let (alice_id, _) = insert_and_get(&db, alice());

        let alice_value = db
            .find_by_id(
                SCHEMA_NAME.to_string(),
                alice_id.clone(),
                vec!["name".to_string(), "email".to_string()],
            )
            .unwrap();

        assert_eq!(
            alice_value,
            Some(json!({
                "name": "Alice",
                 "email": "awalker@gmail.com",
            }))
        );
    }

    #[test]
    fn delete_object_by_id() {
        let db = setup();
        let (alice_id, _) = insert_and_get(&db, alice());
        let (bob_id, bob) = insert_and_get(&db, bob());
        db.delete(SCHEMA_NAME.to_string(), alice_id.clone())
            .unwrap();
        let alice_value = db
            .find_by_id_full(SCHEMA_NAME.to_string(), alice_id.clone())
            .unwrap();
        let bob_value = db
            .find_by_id_full(SCHEMA_NAME.to_string(), bob_id.clone())
            .unwrap();
        assert_eq!(alice_value, None);
        assert_eq!(bob_value, Some(bob));
    }
}
