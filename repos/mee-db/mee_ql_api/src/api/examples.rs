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

fn trim_start(s: &str) -> String {
    s.lines()
        .map(|line| line.trim_start())
        .collect::<Vec<_>>()
        .join("\n")
}

pub fn get_all_payment_cards_of_user() -> String {
    trim_start(
        r#"[
    card
    for user in users
    if user.name == "Alice"
    for card in user.payment_cards
    ]"#,
    )
}

pub fn get_alice_payment_card_by_number() -> String {
    trim_start(
        r#"(
    {"name" : user.name, "card" : card}
    for user in users
    if user.name == "Alice"
    for card in user.payment_cards
    if card.number == "9999 5678 9012 3456"
    )"#,
    )
}

pub fn get_all_users_over_30() -> String {
    trim_start(
        r#"[
            user.name
            for user in users if user.age > 30
        ]"#,
    )
}

pub fn get_users_over_25_offset_1_limit_1() -> String {
    trim_start(
        r#"[
            user.name
            for user in users if user.age > 25 offset 1 limit 1
        ]"#,
    )
}

pub fn get_visa_cards() -> String {
    trim_start(
        r#"[
            card.number
            for user in users
            for card in user.payment_cards
            if card.isssuer == "Visa"
        ]"#,
    )
}

pub fn get_users_who_is_older_then_current() -> String {
    trim_start(
        r#"[
            {"name": user.name, "age": user.age, "older": older }
            for user in users
            older = [ user1.name for user1 in users if user1.age > user.age ]
        ]"#,
    )
}

pub fn update_name_and_card_issuer() -> String {
    trim_start(
        r#"[
            user
            for user in users if user.name == "Bob"
            for card in user.payment_cards if card.number == "9999 5678 9014 3456"
            set user.name = "Updated Bob"
            set card.isssuer = "Updated Mastercard"
        ]"#,
    )
}

pub fn delete_card() -> String {
    trim_start(
        r#"[
            user for user in users if user.name == "Bob"
            for card in user.payment_cards if card.number == "9999 5678 9014 3456"
            delete card
        ]"#,
    )
}

pub fn delete_user() -> String {
    trim_start(
        r#"[
            user for user in users if user.name == "Bob"
            delete user
        ]"#,
    )
}
