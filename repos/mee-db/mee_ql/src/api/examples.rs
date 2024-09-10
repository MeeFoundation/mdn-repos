use mee_storage::query_el::SelectQuery;
use serde_json::{json, Value};

/* #region -- mock user data */
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
                 "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "food",
                        "amount": 301.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "health",
                        "amount": 401.0
                    }
                ],
                "recharge": [
                    {
                        "date": "2021-02-12",
                        "amount": 501
                    },
                    {
                        "date": "2021-04-10",
                        "amount": 601.0
                    }
                ]
            },
            {
                "holder": "Alice Walker",
                "number": "9999 5678 9012 3456",
                "expire": "2028-12-01",
                "cvv": "321",
                "isssuer": "Mastercard",
                "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "food",
                        "amount": 302.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "health",
                        "amount": 402.0
                    }
                ],
                "recharge": [
                    {
                        "date": "2021-02-13",
                        "amount": 502.0
                    },
                    {
                        "date": "2021-04-11",
                        "amount": 602.0
                    }
                ]
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
            "consumption": [
                {
                    "date": "2021-02-12",
                    "caregory": "food",
                    "amount": 303.0
                },
                {
                    "date": "2021-04-10",
                    "caregory": "health",
                    "amount": 403.0
                }
            ],
            "recharge": [
                {
                    "date": "2021-02-12",
                    "amount": 503.0
                },
                {
                    "date": "2021-04-10",
                    "amount": 603.0
                }
            ]
        },
        {
            "holder": "Bob Smith",
            "number": "9999 5678 9014 3456",
            "expire": "2028-12-01",
            "cvv": "321",
            "isssuer": "Mastercard",
            "consumption": [
                {
                    "date": "2021-02-12",
                    "caregory": "food",
                    "amount": 304.0
                },
                {
                    "date": "2021-04-10",
                    "caregory": "health",
                    "amount": 404.0
                }
            ],
            "recharge": [
                {
                    "date": "2021-02-12",
                    "amount": 504.0
                },
                {
                    "date": "2021-04-10",
                    "amount": 604.0
                }
            ]
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
                "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "sport",
                        "amount": 305.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "transport",
                        "amount": 405.0
                    }
                ],
                "recharge": [
                    {
                        "date": "2021-02-12",
                        "amount": 505.0
                    },
                    {
                        "date": "2021-04-10",
                        "amount": 605.0
                    }
                ]
            },
            {
                "holder": "Carol Johnson",
                "number": "9999 5678 9016 3456",
                "expire": "2028-12-01",
                "cvv": "321",
                "isssuer": "Mastercard",
                "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "sport",
                        "amount": 306.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "clothes",
                        "amount": 406.0
                    }
                ],
                "recharge": [
                    {
                        "date": "2021-02-12",
                        "amount": 506.0
                    },
                    {
                        "date": "2021-04-10",
                        "amount": 606.0
                    }
                ]

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
                "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "health",
                        "amount": 307.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "clothes",
                        "amount": 407.0
                    }
                ],
                "recharge": [
                    {
                        "date": "2021-02-12",
                        "amount": 507.0
                    },
                    {
                        "date": "2021-04-10",
                        "amount": 607.0
                    }
                ]
            },
            {
                "holder": "Dan Brown",
                "number": "9999 5678 9018 3456",
                "expire": "2028-12-01",
                "cvv": "321",
                "isssuer": "Mastercard",
                "consumption": [
                    {
                        "date": "2021-02-12",
                        "caregory": "health",
                        "amount": 308.0
                    },
                    {
                        "date": "2021-04-10",
                        "caregory": "food",
                        "amount": 408.0
                    }
                ],
                "recarge": [
                    {
                        "date": "2021-02-12",
                        "amount": 508.0
                    },
                    {
                        "date": "2021-04-10",
                        "amount": 608.0
                    }
            ]
            }
            ]
    })
}

/* #endregion */

pub fn mock_user_data() -> Vec<Value> {
    vec![alice(), bob(), carol(), dan()]
}

fn de_select_query(serialized: &str) -> SelectQuery {
    serde_json::from_str(serialized).unwrap()
}

pub fn select_all() -> SelectQuery {
    de_select_query("{}")
}

pub fn get_all_payment_cards_of_user() -> SelectQuery {
    de_select_query(
        r#"{
                    "@name": "Alice",
                    "$select": [
                        { "my_name": "@name" },
                        { "my_upper_name": { "@name": "$upper" } },
                        "@payment_cards"
                    ]
                  }"#,
    )
}

pub fn get_alice_payment_card_by_number() -> SelectQuery {
    de_select_query(
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
    )
}

pub fn get_user_with_lastname_in_email() -> SelectQuery {
    de_select_query(
        r#"{
                "$derive" : {
                    "upper_last_name" : {"@last_name" : "$upper" },
                    "upper_email" : {"@email" : "$upper" }
                },
                "@upper_email" : {"$contains": "@upper_last_name" }
            }"#,
    )
}

pub fn get_all_users_over_30() -> SelectQuery {
    de_select_query(
        r#"{
                "@age": {"$gt": 30}
            }"#,
    )
}

pub fn get_all_card_numbers() -> SelectQuery {
    de_select_query(
        r#"{
                "$select" : [
                    {"": "@payment_cards/*/number"}
                ]
            }"#,
    )
}

pub fn get_all_card_numbers_non_flatten() -> SelectQuery {
    de_select_query(
        r#"{
                "$select" : [
                    {"": "@payment_cards/*/number"}
                ],
                "$flatten": false
            }"#,
    )
}

pub fn get_all_visa_card_numbers() -> SelectQuery {
    de_select_query(
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
    )
}

pub fn get_as_new_struct() -> SelectQuery {
    de_select_query(
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
    )
}
