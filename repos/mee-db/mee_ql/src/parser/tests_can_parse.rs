//While ASR is not stable just check that source code is parsed
#[cfg(test)]
mod tests {
    use crate::{ast::*, parser::ASTParserImpl};

    #[test]
    fn test_greedy_and_grouping() {
        let source = "[for user in users if true and false and user.path]";
        let mut parser = ASTParserImpl::new(source.to_string());

        parser.parse().unwrap();
    }

    #[test]
    fn test_greedy_or_grouping() {
        let source = "[for user in users if true or false or user.path]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_not_operation() {
        let source = "[for user in users if not true]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_and_operation() {
        let source = "[for user in users if true and false]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_or_operation() {
        let source = "[for user in users if true or false]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_grouped_expression() {
        let source = "[for user in users if true and (false or true)]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_operation_priorities() {
        let source = "[for user in users if true and not true or false and true]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_complicated_expression() {
        let source = "[for user in users if not user.is_admin or user.check1 and user.check2 and (user.check4 or not user.check5 or not (user.check6 and user.check7))]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    //TODO: fix escaping
    #[test]
    fn test_with_comparator() {
        let source = r#"[for user in users
        if true and user.last_name exists or user.age > 18 and user.phone matches "+1\\d{10}"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_json_object() {
        let source = r#"[{"key1": "value1", "key2": 123, "key3": true} for user in users]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_json_array() {
        let source = "[[1, 2, 3, \"four\", false] for user in users]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_string() {
        let source = r#"["four" for user in users]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_number() {
        let source = "[1 for user in users]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_boolean_expression() {
        let source = "[true for user in users]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_embedded_path() {
        let source =
            r#"({"age": user.age, "names": [user.name, user.last_name]} for user in users)"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_equal() {
        let source = r#"[user.id for user in users if user.name == "Ivan"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_not_equal() {
        let source = r#"[user.id for user in users if user.name != "Ivan"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_greater_than() {
        let source = r#"[user.id for user in users if user.age > 30]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_less_than() {
        let source = r#"[user.id for user in users if user.age < 30]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_greater_than_or_equal() {
        let source = r#"[user.id for user in users if user.age >= 30]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_less_than_or_equal() {
        let source = r#"[user.id for user in users if user.age <= 30]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_matches() {
        let source = r#"[user.id for user in users if user.name matches "I.*"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_exists() {
        let source = r#"[user.id for user in users if user.email exists]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_json_object_assignment() {
        let source = r#"[res for user in users res = {"name": user.name}]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_path_assignment() {
        let source = "[res for user in users res = user.name]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_string_assignment() {
        let source = r#"[res for user in users res = "=name"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_logical_expression_assignment() {
        let source = "[res for user in users res = not user.is_admin or true]";
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_find_by_id() {
        let source = r#"[user for user in users() if user.id == "534622344"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_find_last_name_by_email_and_name() {
        let source = r#"[user.last_name for user in users() if user.email == "some@gmail.com" and user.name == "Denis"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_find_by_country_code_or_country() {
        let source = r#"[{"name" : user.name, "phone" : user.phone} for user in users() if user.phone matches "+1[0-9]{11}" or user.country == "USA"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    //TODO add date type
    #[ignore]
    #[test]
    fn test_select_users_who_made_a_purchase_after_a_date() {
        let source = r#"[user.id for user in users() for order in user.orders if order.date >= "2023-09-24"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_select_10_by_age_gender_and_country() {
        let source = r#"[user for user in users() if (user.age >= 18 or user.age <= 25) and user.gender == "Male" and user.country == "USA" limit 10]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_select_users_for_refund_for_a_canceled_flight() {
        let source = r#"[
        {
            "name": user.name,
            "family_name": user.last_name,
            "card_number": number
        }
        for user in users()
        flight = (1 for flight in user.flights if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00")
        number = (card.number for card in user.payment_cards limit 1)
        if flight exists and number exists]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_update_flight_departure_time() {
        let source = r#"[user.passport for user in users() for flight in user.flights if flight.number == "AS702" and flight.dt == "2024.11.11T11:00:00" set flight.dt = "2024.11.11T12:00:00"]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    #[test]
    fn test_add_a_payment_card() {
        let source = r#"[for user in users() if user.id == "4435" set user.payment_cards = [{"number":"1234 1234 1234 1234", "expires": "08/30", "cvv" : "111"}, {"number":"5555 1234 1234 1234", "expires": "08/30", "cvv" : "222"}]]"#;
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse().unwrap();
    }

    fn parse(source: &str) -> Result<MeeNode<Query>, String> {
        let mut parser = ASTParserImpl::new(source.to_string());
        parser.parse()
    }

    #[test]
    fn test_incompatible_types_comparison() {
        assert!(parse(r#"[for user in users() if 12 > true]"#).is_err());
        assert!(parse(r#"[for user in users() if true > 12]"#).is_err());
        assert!(parse(r#"[for user in users() if 11 > 12]"#).is_ok());
    }

    #[test]
    fn test_incompatible_types_comparison_lt() {
        assert!(parse(r#"[for user in users() if 12 < true]"#).is_err());
        assert!(parse(r#"[for user in users() if true < 12]"#).is_err());
        assert!(parse(r#"[for user in users() if 11 < 12]"#).is_ok());
    }

    #[test]
    fn test_incompatible_types_comparison_le() {
        assert!(parse(r#"[for user in users() if 12 <= true]"#).is_err());
        assert!(parse(r#"[for user in users() if true <= 12]"#).is_err());
        assert!(parse(r#"[for user in users() if 11 <= 12]"#).is_ok());
    }

    #[test]
    fn test_incompatible_types_comparison_ge() {
        assert!(parse(r#"[for user in users() if 12 >= true]"#).is_err());
        assert!(parse(r#"[for user in users() if true >= 12]"#).is_err());
        assert!(parse(r#"[for user in users() if 11 >= 12]"#).is_ok());
    }

    #[test]
    fn test_incompatible_types_comparison_matches() {
        assert!(parse(r#"[for user in users() if 12 matches "pattern"]"#).is_err());
        assert!(parse(r#"[for user in users() if user.name matches 12]"#).is_err());
        assert!(parse(r#"[for user in users() if user.name matches ".*"]"#).is_ok());
    }
}
