use clap::builder::Str;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::collections::HashMap;
use utoipa::ToSchema;

// region: SelectQueryRequest
#[derive(Debug, Serialize, Deserialize, ToSchema)]
#[serde(untagged)]
pub enum SelectingField {
    OnlyName(FieldName),
    SpecifiedField {
        field: FieldName,
        #[serde(skip_serializing_if = "Option::is_none")]
        operations: Option<Vec<Operation>>,
        #[serde(skip_serializing_if = "Option::is_none")]
        aggregation: Option<Aggregation>,
        #[serde(skip_serializing_if = "Option::is_none")]
        alias: Option<String>,
    },
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct SelectQueryRequest {
    pub schema: SchemaName,
    pub select: Vec<SelectingField>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub filter: Option<Vec<WhereClause>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub limit: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub offset: Option<usize>,
    // having: Vec<WhereClause>,
    // order_by: Vec<Expr>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum Aggregation {
    Count,
    CountDistinct,
    Sum,
    Avg,
    Min,
    Max,
    MakeString {
        prefix: String,
        separator: String,
        suffix: String,
    },
    ToArray,
    GroupBy,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum Operation {
    Flatten,
    Upper,
    Lower,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct SelectQueryResponse {
    pub result: Vec<HashMap<String, Value>>,
    #[serde(skip_serializing_if = "HashMap::is_empty")]
    pub execution_stats: HashMap<String, Value>,
}
// endregion: SelectQueryRequest

// region: MergeQueryRequest
#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct MergeQueryRequest {
    pub schema: SchemaName,
    pub values: Vec<HashMap<String, Value>>,
    #[serde(default)]
    pub collection_strategy: MergeQueryCollectionStrategy,
    #[serde(default)]
    pub field_strategy: MergeQueryFieldStrategy,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum MergeQueryCollectionStrategy {
    Append,
    ReplaceAll,
    ReplaceIfMatchesOrAppend { matches_field_names: Vec<FieldName> },
    ReplaceIfMatchesOrIgnore { matches_field_names: Vec<FieldName> },
}

impl Default for MergeQueryCollectionStrategy {
    fn default() -> Self {
        MergeQueryCollectionStrategy::Append
    }
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum MergeQueryFieldStrategy {
    Replace,
    IgnoreExisting,
    ReplaceIfMatchesOrIgnore { matches_field_names: Vec<String> },
}

impl Default for MergeQueryFieldStrategy {
    fn default() -> Self {
        MergeQueryFieldStrategy::Replace
    }
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct MergeQueryResponse {
    pub result: Vec<String>,
    #[serde(skip_serializing_if = "HashMap::is_empty")]
    pub execution_stats: HashMap<String, String>,
}
// endregion: MergeQueryRequest

// region: DeleteQueryRequest
#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct DeleteQueryRequest {
    pub schema: String,      //query root
    pub remove: Vec<String>, //types to delete by path from root
    #[serde(skip_serializing_if = "Option::is_none")]
    pub where_clause: Option<Vec<WhereClause>>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct DeleteQueryResponse {
    pub result: Vec<String>,
    #[serde(skip_serializing_if = "HashMap::is_empty")]
    pub execution_stats: HashMap<String, Value>,
}
// endregion: DeleteQueryRequest

// region: UpdateQueryRequest
#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct UpdateQueryRequest {
    pub schema: String,
    pub select_clause: Option<Vec<SelectingField>>,
    pub update_clause: Vec<UpdateClause>,
    pub where_clause: Option<Vec<WhereClause>>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct UpdateQueryResponse {
    pub result: Option<Vec<HashMap<String, Value>>>,
    pub updated: usize,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub execution_stats: Option<HashMap<String, String>>,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct UpdateClause {
    pub field: String,
    pub value: Value,
}
// endregion: UpdateQueryRequest

// region: common types
#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct FieldName(pub String);

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct ObjectId(pub String);

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct SchemaName(pub String);

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum WhereClause {
    Or(Vec<WhereClause>),
    Not(Box<WhereClause>),
    #[serde(untagged)]
    Check(HashMap<String, CheckOperator>),
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub enum CheckOperator {
    #[serde(rename = "$ne")]
    Ne(Value),
    #[serde(rename = "$gt")]
    Gt(Value),
    #[serde(rename = "$ge")]
    Ge(Value),
    #[serde(rename = "$lt")]
    Lt(Value),
    #[serde(rename = "$le")]
    Le(Value),
    #[serde(rename = "$exists")]
    Exists,
    #[serde(rename = "$not_exists")]
    NotExists,
    #[serde(untagged)]
    Eq(Value),
}
// endregion: common types
