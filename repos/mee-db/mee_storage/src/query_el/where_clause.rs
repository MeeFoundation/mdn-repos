use serde::{Deserialize, Serialize};
use serde_json::Value;

use super::expression::Expr;
use super::CheckOperator;
use super::ConstOrField;
use std::collections::HashMap;
use std::collections::HashSet;
use utoipa::ToSchema;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Default, ToSchema)]
pub enum WhereClause {
    #[serde(rename = "$true")]
    #[default]
    True,
    #[serde(rename = "$false")]
    False,
    #[serde(rename = "$or")]
    Or(Vec<WhereClause>),
    #[serde(rename = "$nor")]
    Nor(Vec<WhereClause>),
    #[serde(rename = "$not")]
    Not(Box<WhereClause>),
    #[serde(untagged)]
    And(Vec<WhereClause>),
    #[serde(untagged)]
    Checks(HashMap<ConstOrField, CheckOperator>),
}

impl WhereClause {
    pub fn filter(&self, value: &Value) -> bool {
        match self {
            Self::True => true,
            Self::False => false,
            Self::Or(clauses) => clauses.iter().any(|clause| clause.filter(value)),
            Self::Nor(clauses) => clauses.iter().filter(|clause| clause.filter(value)).count() == 1,
            Self::And(clauses) => clauses.iter().all(|clause| clause.filter(value)),
            Self::Not(clause) => !clause.filter(value),
            Self::Checks(items) => items
                .iter()
                .all(|(val, check)| check.apply_to(Some(value), &Expr::Val(val.clone()))),
        }
    }
    pub fn get_using_fields(&self) -> HashSet<String> {
        match self {
            Self::Checks(items) => items.iter().fold(HashSet::new(), |mut acc, (k, v)| {
                acc.extend(k.get_using_fields());
                acc.extend(v.get_using_fields());
                acc
            }),
            Self::Or(clauses) | Self::Nor(clauses) | Self::And(clauses) => clauses
                .iter()
                .flat_map(|clause| clause.get_using_fields())
                .collect(),
            Self::Not(clause) => clause.get_using_fields(),
            _ => HashSet::new(),
        }
    }
}

#[cfg(test)]
mod tests {
    use serde_json::json;

    use super::super::_test_support::*;
    use super::super::expression::*;
    use super::*;

    #[test]
    fn where_clause_true() {
        let val = json!({});
        assert!(WhereClause::True.filter(&val));
    }

    #[test]
    fn where_clause_false() {
        let val = json!({});
        assert!(!WhereClause::False.filter(&val));
    }

    #[test]
    fn where_clause_or() {
        let val = json!({});
        assert!(de_where_clause(r#"{"$or":["$true","$false"]}"#).filter(&val));
        assert!(de_where_clause(r#"{"$or":["$false","$true"]}"#).filter(&val));
        assert!(de_where_clause(r#"{"$or":["$true","$true"]}"#).filter(&val));
        assert!(!de_where_clause(r#"{"$or":["$false","$false"]}"#).filter(&val));
    }

    #[test]
    fn where_clause_and() {
        let val = json!({});
        assert!(!de_where_clause(r#"["$true","$false"]"#).filter(&val));
        assert!(!de_where_clause(r#"["$false","$true"]"#).filter(&val));
        let wc = de_where_clause(r#"["$true","$true"]"#);
        assert!(wc.filter(&val));
        assert!(!de_where_clause(r#"["$false","$false"]"#).filter(&val));
    }

    #[test]
    fn where_clause_not() {
        let val = json!({});
        assert!(!de_where_clause(r#"{"$not":"$true"}"#).filter(&val));
        assert!(de_where_clause(r#"{"$not":"$false"}"#).filter(&val));
    }

    #[test]
    fn where_clause_nor() {
        let val = json!({});
        assert!(de_where_clause(r#"{"$nor":["$true","$false"]}"#).filter(&val));
        assert!(de_where_clause(r#"{"$nor":["$false","$true"]}"#).filter(&val));
        assert!(!de_where_clause(r#"{"$nor":["$true","$true"]}"#).filter(&val));
        assert!(!de_where_clause(r#"{"$nor":["$false","$false"]}"#).filter(&val));
    }

    #[test]
    fn where_clause_item_named_select_item() {
        let wc_field_eq = de_where_clause(r#"{"@field1": "value1"}"#);
        let wc_field_ne = de_where_clause(r#"{"@field1": {"$ne": "value1"}}"#);
        let wc_mult_conditions =
            de_where_clause(r#"{"@field1": {"$gt": "value1"}, "VALUE1": {"value1" : "$upper"} }"#);
        let expected_wc_field_eq = WhereClause::Checks({
            let mut map = HashMap::new();
            map.insert(
                ConstOrField::Field("field1".to_string()),
                CheckOperator::Equal(Expr::Val(ConstOrField::Const(Value::String(
                    "value1".to_string(),
                )))),
            );
            map
        });

        let exprected_wc_field_ne = WhereClause::Checks({
            let mut map = HashMap::new();
            map.insert(
                ConstOrField::Field("field1".to_string()),
                CheckOperator::NotEqual(Expr::Val(ConstOrField::Const(Value::String(
                    "value1".to_string(),
                )))),
            );
            map
        });

        let expected_wc_mult_conditions = WhereClause::Checks({
            let mut map = HashMap::new();
            map.insert(
                ConstOrField::Field("field1".to_string()),
                CheckOperator::GreaterThan(Expr::Val(ConstOrField::Const(Value::String(
                    "value1".to_string(),
                )))),
            );
            map.insert(
                ConstOrField::Const(Value::String("VALUE1".to_string())),
                CheckOperator::Equal(Expr::Operation {
                    expr: Box::new(Expr::Val(ConstOrField::Const(Value::String(
                        "value1".to_string(),
                    )))),
                    op: Box::new(Operation::Upper),
                }),
            );
            map
        });

        assert_eq!(wc_field_eq, expected_wc_field_eq);
        assert_eq!(wc_field_ne, exprected_wc_field_ne);
        assert_eq!(wc_mult_conditions, expected_wc_mult_conditions);
    }
}
