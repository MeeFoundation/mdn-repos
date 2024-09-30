use super::api_methods::*;
use mee_storage::query_el::{
    CheckOperator, ConstOrField, DeriveClause, Expr, NamedField, Operation, SelectClause,
    SelectClauseItem, SelectQuery, WhereClause,
};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
        select
      ),
      // security(
      //     ("authorization" = []),
      // ),
      components(
          schemas(
            SelectQuery,
            WhereClause,
            SelectClause,
            DeriveClause,
            CheckOperator,
            Operation,
            Expr,
            ConstOrField,
            SelectClauseItem,
            NamedField,
          ),
      ),
      // modifiers(&SecurityAddon),
      tags(
          (name = "Mee query language", description = "MeeQl REST API"),
      )
  )]
pub struct ApiDoc;

// pub const OPEN_API_PATH: &str = "/providers/mdn_license_applications/openapi.json";
