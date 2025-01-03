use super::support::{
    apply_property, delete_property, get_property, get_property_pattern, inner_set, merge_json,
};
use super::ID_PROPERTY;
#[allow(unused_imports)]
use crate::mock_binary_kv_store::PATH_SEPARATOR;
use serde::Serialize;
use serde_json::Value;
use std::collections::BTreeMap;
pub trait JsonExt: Serialize {
    fn x_set_id(&mut self, id: &str) -> &mut Self;

    #[allow(unused)]
    fn x_get_id(&self) -> Option<&str>;

    fn x_set_property(&mut self, key: &str, value: Value) -> &mut Self;

    fn x_delete_property(&mut self, key: &str) -> &mut Self;

    fn x_get_property<'a>(&'a self, key: &'a str) -> Option<&'a Value>;

    fn x_get_property_pattern(&self, pattern: &str) -> Option<Value>;

    fn x_merge(&mut self, other: Value) -> &mut Self;

    fn x_to_flatten_map(self, prefix: String) -> BTreeMap<String, Value>;

    fn pretty(&self) -> String {
        serde_json::to_string_pretty(&self).unwrap()
    }
}

impl JsonExt for Value {
    fn x_set_id(&mut self, id: &str) -> &mut Self {
        apply_property(self, ID_PROPERTY, Value::String(id.to_string()));
        self
    }

    fn x_get_id(&self) -> Option<&str> {
        self.get(ID_PROPERTY).and_then(|id| id.as_str())
    }

    fn x_set_property(&mut self, key: &str, value: Value) -> &mut Self {
        apply_property(self, key, value);
        self
    }

    fn x_delete_property(&mut self, key: &str) -> &mut Self {
        delete_property(self, key);
        self
    }

    fn x_get_property<'a>(&'a self, key: &'a str) -> Option<&'a Value> {
        get_property(self, key)
    }

    fn x_merge(&mut self, other: Value) -> &mut Self {
        merge_json(self, other);
        self
    }

    fn x_to_flatten_map(self, prefix: String) -> BTreeMap<String, Value> {
        let mut map = BTreeMap::new();
        inner_set(&mut map, prefix, self);
        map
    }

    fn x_get_property_pattern(&self, pattern: &str) -> Option<Value> {
        get_property_pattern(self, pattern)
    }
}

#[cfg(test)]
mod test {

    use super::*;
    use assert_json_diff::assert_json_eq;
    use serde_json::json;

    #[test]
    fn merge_json_objects() {
        let mut first = json!(
            {
                "field1": "value1",
                "field2": "value2",
                "field3": {
                    "field4": "value4"
                }
            }
        );
        let second = json!(
            {
                "field1": "value6",
                "field3": {
                    "field5": "value5"
                }
            }
        );
        let expected = json!(
            {
                "field1": "value6",
                "field2": "value2",
                "field3": {
                    "field4": "value4",
                    "field5": "value5"
                }
            }
        );
        first.x_merge(second);
        assert_eq!(first, expected);
    }

    #[test]
    fn merge_json_arrays() {
        let mut first = json!([1, 2, 3]);
        let second = json!([4, 5, 6]);
        let expected = json!([1, 2, 3, 4, 5, 6]);
        first.x_merge(second);
        assert_eq!(first, expected);
    }

    #[test]
    fn merge_json_replace_incompatible() {
        let mut first = json!([1, 2, 3,]);
        let second = json!(
            {
                "field1": ["value6", "value7"],
            }
        );
        let expected = second.clone();
        first.x_merge(second);
        assert_eq!(first, expected);
    }

    #[test]
    fn set_id() {
        let mut obj = json!({});
        obj.x_set_id("id:132");
        assert_eq!(obj, json!({ID_PROPERTY: "id:132"}));
    }

    #[test]
    fn get_id() {
        let obj = json!({ID_PROPERTY: "id:123"});
        assert_eq!(obj.x_get_id(), Some("id:123"));
    }

    #[test]
    fn set_single_property() {
        let mut obj = json!({});
        obj.x_set_property("field1", json!("value1"));
        assert_eq!(obj, json!({"field1": "value1"}));
    }

    #[test]
    fn set_complex_property() {
        let mut obj = Value::Null;
        obj.x_set_property("field1", json!("value1"));
        obj.x_set_property(&format!("field2{PATH_SEPARATOR}field3"), json!("value3"));
        obj.x_set_property(
            &format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}0"),
            json!("value4"),
        );
        obj.x_set_property(
            &format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}1"),
            json!("value5"),
        );

        assert_eq!(
            obj,
            json!({
                "field1": "value1",
                "field2": {
                    "field3": "value3",
                    "field4": ["value4", "value5"]
                }
            })
        );
    }

    #[test]
    fn get_complex_property() {
        let obj = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": ["value4", "value5"]
            }
        });
        assert_eq!(obj.x_get_property("field1"), Some(&json!("value1")));
        assert_eq!(
            obj.x_get_property(&format!("field2{PATH_SEPARATOR}field3")),
            Some(&json!("value3"))
        );
        assert_eq!(
            obj.x_get_property(&format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}0")),
            Some(&json!("value4"))
        );
        assert_eq!(
            obj.x_get_property(&format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}1")),
            Some(&json!("value5"))
        );
    }

    #[test]
    fn get_missing_property() {
        let obj = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": ["value4", "value5"]
            }
        });
        assert_eq!(obj.x_get_property("field5"), None);
        assert_eq!(
            obj.x_get_property(&format!("field2{PATH_SEPARATOR}field6")),
            None
        );
        assert_eq!(
            obj.x_get_property(&format!("field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}2")),
            None
        );
    }

    #[test]
    fn get_complex_pattern_property() {
        let obj = json!({
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
                    "history": [
                        {
                            "date": "2021-01-01",
                            "amount": 100.0
                        },
                        {
                            "date": "2021-02-01",
                            "amount": 200.0
                        }
                    ]
                },
                {
                    "holder": "Dan Brown",
                    "number": "9999 5678 9014 3456",
                    "expire": "2028-12-01",
                    "cvv": "321",
                    "isssuer": "Mastercard",
                     "consumption": [
                        {
                            "date": "2021-02-12",
                            "amount": 300.0
                        },
                        {
                            "date": "2021-04-10",
                            "amount": 400.0
                        }
                    ],
                    "recharge": {
                        "first":{
                            "date": "2021-02-12",
                            "amount": 500.0
                        },
                        "second":{
                            "date": "2021-04-10",
                            "amount": 600.0
                        }
                    }

                }
                ]
        });

        assert_json_eq!(
            obj.x_get_property_pattern("payment_cards/*/number"),
            Some(&json!(["1234 5678 9015 3456", "9999 5678 9014 3456"]))
        );
        assert_json_eq!(
            obj.x_get_property_pattern("*/*/*/*/amount"),
            Some(&json!({
            "payment_cards": [
                {
                "history": [
                    100.0,
                    200.0
                ]
                },
                {
                "consumption": [
                    300.0,
                    400.0
                ],
                "recharge": {
                    "first": 500.0,
                    "second": 600.0
                }
                }
            ]
            }))
        );
    }

    #[test]
    fn to_map() {
        let obj = json!({
            "field1": "value1",
            "field2": {
                "field3": "value3",
                "field4": ["value4", "value5"]
            }
        });
        let map = obj.x_to_flatten_map("key".to_string());
        let mut expected = BTreeMap::new();
        expected.insert(format!("key{PATH_SEPARATOR}field1"), json!("value1"));
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field3"),
            json!("value3"),
        );
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}0"),
            json!("value4"),
        );
        expected.insert(
            format!("key{PATH_SEPARATOR}field2{PATH_SEPARATOR}field4{PATH_SEPARATOR}1"),
            json!("value5"),
        );

        assert_eq!(map, expected);
    }
}
