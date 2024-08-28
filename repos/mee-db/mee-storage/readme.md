# MeeDB scenarios

## DB conten for examples

(* @id can be diffrent)

```json
[
{
  "@id": "019179bd-d4c0-75a0-a667-6696ff07aaa3",
  "age": 30,
  "email": "awalker@gmail.com",
  "last_name": "Walker",
  "name": "Alice",
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
      "number": "9999 5678 9022 3456"
    }
  ]
}
{
  "@id": "019179bd-d4c1-7383-9042-568d94645d5c",
  "age": 25,
  "email": "sbob@gmail.com",
  "last_name": "Smith",
  "name": "Bob",
  "payment_cards": [
    {
      "cvv": "123",
      "expire": "2023-12-01",
      "holder": "Bob Smith",
      "isssuer": "Visa",
      "number": "1234 567 9012 3456"
    },
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Bob Smith",
      "isssuer": "Mastercard",
      "number": "9999 5678 9012 3456"
    }
  ]
}
{
  "@id": "019179bd-d4c1-7383-9042-56985b9c0880",
  "age": 35,
  "email": "jcarol@gmail.com",
  "last_name": "Johnson",
  "name": "Carol",
  "payment_cards": [
    {
      "cvv": "123",
      "expire": "2023-12-01",
      "holder": "Carol Johnson",
      "isssuer": "Visa",
      "number": "1234 5678 9012 3456"
    },
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Carol Johnson",
      "isssuer": "Mastercard",
      "number": "9999 5678 9013 3456"
    }
  ]
}
{
  "@id": "019179bd-d4c1-7383-9042-56ac0818b72e",
  "age": 40,
  "email": "bdan@yahoo.com",
  "last_name": "Brown",
  "name": "Dan",
  "payment_cards": [
    {
      "cvv": "123",
      "expire": "2023-12-01",
      "holder": "Dan Brown",
      "isssuer": "Visa",
      "number": "1234 5678 9015 3456"
    },
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Dan Brown",
      "isssuer": "Mastercard",
      "number": "9999 5678 9014 3456"
    }
  ]
}
]
```

## Read scenarious

### Get all payment cards of a specific user

now in DSL:

```rust
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
```

expected request in json:

```json
POST /db/docs/select
{
    "$select": [
        "name",
        "payment_cards"
    ],
    "$where": [
        {
            "name": "Alice"
        }
    ]
}
```

result:

```json
[
{
  "name": "Alice",
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
]
```

### Get a specific user’s payment card with a specific number

now in DSL:

```rust
async fn get_alice_payment_card_by_number(db: Arc<dyn JsonDB>) {
    let select = SelectQueryBuilder::select(
        SelectClauseBuilder::new()
            .add_field(Field("name".to_string()))
            .add_field_as(Field("payment_cards/1".to_string()), "my_card".to_string())
            .build(),
    )
    .where_clause(
        Check(
            Field("name".to_string()),
            Equal(Val(json!("Alice"))),
        )
        .and(Check(
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
```

expected request in json:
add mongo like filter

```json
POST /db/docs/select
{
    "$select": [
        "name",
        {
            "path": "payment_cards/*",
            "alias" : "my_card"
        }
    ],
    "$where": [
        {
            "name": "Alice",
            "payment_cards/*/number": "9999 5678 9022 3456"
        }
    ]
}
```

result:

```json
[
{
  "name": "Alice",
  "my_card": [
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Alice Walker",
      "isssuer": "Mastercard",
      "number": "9999 5678 9012 3456"
    }
  ]
}
]
```

### Get all users over 30

now in DSL:

```rust
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
```

expected request in json:

```json
POST /db/docs/select
{
    "$where": [
        {
            "age": {"@gt" : 30},
        }
    ]
}
```

result:

```json
[
{
  "@id": "01917a28-5c3f-71a1-bf6b-c6ac3157095a",
  "age": 35,
  "email": "jcarol@gmail.com",
  "last_name": "Johnson",
  "name": "Carol",
  "payment_cards": [
    {
      "cvv": "123",
      "expire": "2023-12-01",
      "holder": "Carol Johnson",
      "isssuer": "Visa",
      "number": "1234 5678 9012 3456"
    },
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Carol Johnson",
      "isssuer": "Mastercard",
      "number": "9999 5678 9013 3456"
    }
  ]
}
{
  "@id": "01917a28-5c3f-71a1-bf6b-c6ba214e387d",
  "age": 40,
  "email": "bdan@yahoo.com",
  "last_name": "Brown",
  "name": "Dan",
  "payment_cards": [
    {
      "cvv": "123",
      "expire": "2023-12-01",
      "holder": "Dan Brown",
      "isssuer": "Visa",
      "number": "1234 5678 9015 3456"
    },
    {
      "cvv": "321",
      "expire": "2028-12-01",
      "holder": "Dan Brown",
      "isssuer": "Mastercard",
      "number": "9999 5678 9014 3456"
    }
  ]
}
]
```
