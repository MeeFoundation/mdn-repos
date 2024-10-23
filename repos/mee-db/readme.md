# Python-like query Examples

1. Find by email

```python
{
  ..user
  for user in users() if user.email == "some@gmail.com"
}
```

2. Find by substring

```python
[
  user
  for user in users() if user.last_name.contains("some@gmail.com")
]
```

3. Find by ID

```python
{
  ..user
  for user in users() if user.id == "534622344"
}
```

4. Select by age, gender, and country

```python
[
  user
  for user in users() 
    if user.age.is_between(18, 25) 
      and user.gender == "Male"
      and user.country == "USA"
]
```

5. Select users for refund for a canceled flight

```python
[
  {
    user.name,
    "family_name": user.last_name,
    "card_number": number
  }

  for user in users()
  for flight in user.flights
    if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00"
  number = [card.number for card in user.payment_cards limit 1].first()
  if number exists
]
```

6. Select users who made a purchase after a date

```python  
[
  distinct(user.id)

  for user in users()
  for order in user.orders
    if order.date >= "2023-09-24"
]
```

7. Get user address as a string

```python  
{
  "city": address.city,
  "address": concat(address.postal_code, ", st. ", address.street, ", h. ",  apt) 

  for user in users() if user.id == "323432"
  address = user.address
  apt = if address.apartment.is_empty "" else concat(", apt. ", address.apartment)
}
```

8. Select 10 users with the most friends

```python  
[
  {
    "email": user.email,
    "friends_count": friends_count 
  }

  for user in users()
  friends_count = len(user.friends) 
  sort friends_count desc, user.email
  limit 10
]
```

9. Select single people (unique address) (intentionally ignoring the grouping by address to make a 'subselect')

```python  
[
  {
    "email": user.email,
    "address" : {
      "country" : address.country,
      "city" : address.city,
    }
  }

  for user in users()
  address = user.address
  if not [user.address for user1 in users() if user1.id != user1.id].contains(address)
]
```

10. Top 3 most frequently purchased items by a user

```python  
[
  {
    "position": item,
    "purchases" : times
  }

  for user in users() if user.id == "45344"
  for order in user.orders
  for item in order.items
  times = count_distinct(order)
]
```

11. Select users who made orders totaling more than $1000

```python
[
  {
    "email": user.email,
    "total_spent": total_spent
  }

  for user in users()
  total_spent = [sum(order.total) for order in user.orders][0]
  if total_spent > 1000
]
```

12. Update flight departure time

```python
{
  "count": rows

  for user in users()
  for flight in user.flights
    if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00"
  set flight.dt = "2024.11.11T12:00:00"
  rows = count(1)
}
```

13. Add a payment card

```python
{
  "ok"

  for user in users() if user.id == "4435"
  payment_cards = coalesce(user.payment_cards, []).push({"number":"1234 1234 1234 1234", "expires": "08/30", "cvv" : "111"})
  set user.payment_cards = payment_cards
}
```

14. Add loyalty points

```python
{
  "new_value": user.loyalty_points,
  "old_valye": before

  for user in users() if user.id == "4435"
  before = user.loyalty_points
  set user.loyalty_points = before + 100
}
```

15. Delete expired payment cards and get data to notify users

```python
{
  "email": user.email,
  "deleted_card_numbers": numbers

  for user in users()
  numbers = [card.number for card in user.payment_cards if card.expires < "2024.09.01"]
  set user.payment_cards = [card for card in user.payment_cards if not numbers.contains[card.number]]
}
```

16. Select users who made more than 5 product returns, mark as suspicious, and send them a warning

```python
[
  {
    "email": user.email,
    "returns_count": returns_count

    for user in users()
    returns_count = len(user.returns)
    if returns_count > 5
    set user.status = "suspicious"
  }
]
```

17. Delete inactive user devices

```python
{
    for user in users()
    set user.active_devices = [device for device in user.active_devices if device.last_active < "2023-08-01"]
}
```

18. Replace missing items when assembling an order in the supermarket

```python
{
  "removed_items": removed_items,
  "added_items": added_items,
  "old_total": old_total,
  "new_total" : order.total
  
  for user in users() if user.id == "4435"
  for order in user.orders if order.number == "314"
  old_total = order.total
  removed_items = [item for item in order.items if ["id1". "id2"].contains(item.id)]
  added_items = [{"id": "id3", "price": "32", "count": "2" }, {"id": "id4", "price": "312", "count": "1" }]
  total_dif = [sum(item.price * item.count) for item in added_items][0] - [sum(item.price * item.count) for item in removed_items][0]
  set order.total = old_total + total_dif
  set order.items = [item for item in order if !["id1". "id2"].contains(item.id)] + added_items
}
```

19. Update subscription status to "active" for all users who have paid for the subscription

```python
[
  distinct(user.id)
  
  for user in users()
  for subscription in user.subscriptions
    if subscription.status == "pending" and subscription.payment_status == "paid"
  set subscription.status = "active"
]
```

20. Top up user balance

```python
[
  user.my_site_store.money
  
  for user in users() if user.id == "543534"
  set user.my_site_store.money = coalesce(user.my_site_store.money, 0) + 100
]
```
