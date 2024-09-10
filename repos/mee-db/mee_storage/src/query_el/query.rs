use super::{FieldFilter, Result, SelectClause};

use crate::json_utils::JsonExt;

use super::derive_clause::DeriveClause;

use super::where_clause::WhereClause;

use serde::de::Deserializer;
use serde::ser::{SerializeMap, Serializer};
use serde::{Deserialize, Serialize};
use serde_json::Map;
use serde_json::Value;

use tracing::trace;

use utoipa::ToSchema;

#[derive(Debug, Clone, PartialEq, ToSchema)]
pub struct SelectQuery {
    pub derive_clause: DeriveClause,
    pub where_clause: WhereClause,
    pub limit: Option<usize>,
    pub offset: Option<usize>,
    pub select_clause: SelectClause,
    pub flatten: bool,
}

impl Serialize for SelectQuery {
    fn serialize<S>(&self, serializer: S) -> std::result::Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut map = serializer.serialize_map(None)?;
        if !self.derive_clause.is_empty() {
            map.serialize_entry("$derive", &self.derive_clause)?;
        }
        if let Some(limit) = self.limit {
            map.serialize_entry("$limit", &limit)?;
        }
        if let Some(offset) = self.offset {
            map.serialize_entry("$offset", &offset)?;
        }
        if !self.select_clause.is_all() {
            map.serialize_entry("$select", &self.select_clause)?;
        }
        if !self.flatten {
            map.serialize_entry("$flatten", &self.flatten)?;
        }
        if self.where_clause != WhereClause::True {
            let where_clause =
                serde_json::to_value(&self.where_clause).map_err(serde::ser::Error::custom)?;
            if let Value::Object(where_clause) = where_clause {
                for (k, v) in where_clause {
                    map.serialize_entry(&k, &v)?;
                }
            } else {
                map.serialize_entry("$where", &where_clause)?;
            }
        }
        map.end()
    }
}

impl<'a> Deserialize<'a> for SelectQuery {
    fn deserialize<D>(deserializer: D) -> std::result::Result<Self, D::Error>
    where
        D: Deserializer<'a>,
    {
        let mut map = Map::deserialize(deserializer)?;

        let derive_clause = map
            .remove("$derive")
            .map(|v| serde_json::from_value(v).map_err(serde::de::Error::custom))
            .transpose()?;
        let limit = map
            .remove("$limit")
            .map(|v| {
                serde_json::from_value(v)
                    .map_err(serde::de::Error::custom)
                    .and_then(|v: Value| {
                        v.as_u64().ok_or(serde::de::Error::custom(
                            "limit should be a positive integer",
                        ))
                    })
                    .map(|v| usize::try_from(v).unwrap())
            })
            .transpose()?;

        let offset = map
            .remove("$offset")
            .map(|v| {
                serde_json::from_value(v)
                    .map_err(serde::de::Error::custom)
                    .and_then(|v: Value| {
                        v.as_u64().ok_or(serde::de::Error::custom(
                            "limit should be a positive integer",
                        ))
                    })
                    .map(|v| usize::try_from(v).unwrap())
            })
            .transpose()?;

        let select_clause = map
            .remove("$select")
            .map(|v| serde_json::from_value(v).map_err(serde::de::Error::custom))
            .transpose()?;

        let flatten = map
            .remove("$flatten")
            .map(|v| {
                serde_json::from_value(v)
                    .map_err(serde::de::Error::custom)
                    .and_then(|v: Value| match v {
                        Value::Bool(b) => Ok(b),
                        _ => Err(serde::de::Error::custom(
                            "flatten should be true or false. default is true",
                        )),
                    })
            })
            .transpose()?
            .unwrap_or(true);

        let where_clause: Option<WhereClause> = if map.contains_key("$where") {
            map.remove("$where")
                .map(|v| serde_json::from_value(v).map_err(serde::de::Error::custom))
                .transpose()?
        } else if !map.is_empty() {
            Some(serde_json::from_value(Value::Object(map)).map_err(serde::de::Error::custom)?)
        } else {
            None
        };

        Ok(SelectQuery {
            derive_clause: derive_clause.unwrap_or_default(),
            where_clause: where_clause.unwrap_or(WhereClause::True),
            limit,
            offset,
            select_clause: select_clause.unwrap_or(SelectClause::All),
            flatten,
        })
    }
}

impl SelectQuery {
    pub fn pack_and_get_field_filter(&mut self) -> Result<FieldFilter> {
        let select_clause = self.select_clause.clone().pack();
        self.select_clause = select_clause;

        if self.select_clause == SelectClause::All {
            Ok(FieldFilter::All)
        } else {
            let mut field_names = self.select_clause.get_using_fields();
            field_names.extend(self.where_clause.get_using_fields());
            field_names.extend(self.derive_clause.get_using_fields());

            let field_names = field_names.into_iter().collect();

            FieldFilter::try_from_patterns(field_names)
        }
    }

    pub fn process(&self, mut value: Value) -> Option<Value> {
        let derived = self.derive_clause.get_value(&value);
        value.x_merge(derived);

        if self.where_clause.filter(&value) {
            trace!("Selected: {}", value.pretty());
            Some(self.select_clause.get_value(value))
        } else {
            trace!("Filtered: {}", value.pretty());
            None
        }
    }
}

#[cfg(test)]
mod test {

    use super::super::{select_clause::SelectClause, where_clause::WhereClause};
    use super::*;
    use crate::query_el::_test_support::de_select_query;
    use serde_json::json;

    #[test]
    fn serialize_default_select_query() {
        let query = de_select_query(r#"{}"#);
        let expected = SelectQuery {
            derive_clause: DeriveClause::default(),
            where_clause: WhereClause::True,
            limit: None,
            offset: None,
            select_clause: SelectClause::All,
            flatten: true,
        };
        assert_eq!(query, expected);
    }

    #[test]
    fn select_derived() {
        let query =
            de_select_query(r#"{"$derive":{"new_value":1, "upper_name": {"@name": "$upper"}}}"#);
        let value = json!({"name": "value"});
        let result = query.process(value.clone());
        assert_eq!(
            result,
            Some(json!({"name": "value","new_value": 1, "upper_name": "VALUE"}))
        );
    }

    #[test]
    fn select_derived_with_where() {
        let query = de_select_query(
            r#"{"$derive":{"new_value":1, "upper_name": {"@name": "$upper"}}, "@upper_name":"VALUE1" }"#,
        );
        let values = vec![json! ({"name": "value1"}), json!({"name": "value2"})];
        let result = values
            .into_iter()
            .filter_map(move |v| query.process(v))
            .collect::<Vec<_>>();
        assert_eq!(
            result,
            vec![json!({"name": "value1", "new_value": 1, "upper_name": "VALUE1"})]
        );
    }
}
